#pragma once
#include <string>
#include <iostream>
using namespace std;


class ShaderProgram
{
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader);

	~ShaderProgram();

	void use();

private:
	void checkerorr(unsigned int shader_id, std::string type);
	unsigned int ID;
};