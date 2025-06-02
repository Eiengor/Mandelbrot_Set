#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;
using namespace glm;

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
	string get_file_contents(const char* filename);
	void const set_float(const string& name, float value);
	void const set_vec4(const string& name, vec4 vec);
	void const set_int(const string& name, int value);
	void checkCompileErrors(unsigned int shader, string type);
protected:
	Shader() = default;
};


#endif SHADER_H