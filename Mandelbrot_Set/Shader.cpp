#include "Shader.h"
string Shader::get_file_contents(const char* filename)
{
	ifstream in(filename, ios::binary);
	if (in)
	{
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	string vertexCode = get_file_contents(vertexFile);
	string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	checkCompileErrors(vertexShader, "VERTEX_SHADER");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	checkCompileErrors(fragmentShader, "FRAGMENT_SHADER");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void const Shader::set_float(const string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void const Shader::set_vec4(const string& name, vec4 vec)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}
void const Shader::set_int(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::checkCompileErrors(unsigned int shader, string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
		}
	}
}