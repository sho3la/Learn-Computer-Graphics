#pragma once
#include "ShaderProgram.h"
#include <map>
#include <memory>
using namespace std;


class ShaderLibrary
{
public:
	ShaderLibrary();

	~ShaderLibrary();

	ShaderProgram* Textured_Shader();

	ShaderProgram* Colored_Shader();

private:

	map<string,ShaderProgram*> programs;
};

static unique_ptr<ShaderLibrary> Shaders;