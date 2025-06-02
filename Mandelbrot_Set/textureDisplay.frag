#version 430 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D mandelbrotTex;

void main() {
    FragColor = texture(mandelbrotTex, texCoord);
}