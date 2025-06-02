#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include "Shader.h"

class ComputeShader : public Shader
{
public:
	ComputeShader(const char* computeFile);
};

#endif // !COMPUTE_SHADER_H
