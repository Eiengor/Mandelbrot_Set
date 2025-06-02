#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<glad/glad.h>
#include"Shader.h"

class Texture
{
public:
	GLuint ID;
	Texture(const unsigned int TEXTURE_WIDTH, const unsigned int TEXTURE_HEIGHT);
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
	void Activate();
};
#endif // TEXTURE_H