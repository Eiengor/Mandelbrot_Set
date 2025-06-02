#include "ComputeShader.h"

ComputeShader::ComputeShader(const char* computeFile)
{
	string computeCode = get_file_contents(computeFile);

	const char* computeSource = computeCode.c_str();

	GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShader, 1, &computeSource, NULL);
	glCompileShader(computeShader);

	checkCompileErrors(computeShader, "COMPUTE_SHADER");

	ID = glCreateProgram();
	glAttachShader(ID, computeShader);
	glLinkProgram(ID);
	
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(computeShader);
}