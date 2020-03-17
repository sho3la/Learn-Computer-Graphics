#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
{
	const char* vs = R"CODE(
			#version 330 core
			layout(location = 0) in vec2 point;
			layout(location = 1) in vec4 color;
			layout(location = 2) in vec2 uv;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;
			out vec2 vertex_uv;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, 0.0, 1.0);
				vertex_color = color;
				vertex_uv = uv;
			};
)CODE";
	
	const char* fs = R"CODE(

			#version 330 core
			out vec4 finalcolor;

			in vec4 vertex_color;
			in vec2 vertex_uv;

			uniform sampler2D sprite;

			void main()
			{
				finalcolor = vertex_color * texture(sprite,vertex_uv);
			};
)CODE";

	programs.insert(pair<string,ShaderProgram*>("Textured",new ShaderProgram(vs,fs)));


	//////////////////////////////////////// colored shader
	vs = R"CODE(
			#version 330 core
			layout(location = 0) in vec2 point;
			layout(location = 1) in vec4 color;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, 0.0, 1.0);
				vertex_color = color;
			};
)CODE";
	
	fs = R"CODE(

			#version 330 core
			out vec4 finalcolor;

			in vec4 vertex_color;

			uniform vec4 user_color;

			void main()
			{
				if(user_color == vec4(0,0,0,0)) finalcolor = vertex_color;
				else finalcolor = user_color;
			};
)CODE";

	programs.insert(pair<string,ShaderProgram*>("Colored",new ShaderProgram(vs,fs)));
}

ShaderLibrary::~ShaderLibrary()
{
}

ShaderProgram* ShaderLibrary::Textured_Shader()
{
	return programs["Textured"];
}

ShaderProgram * ShaderLibrary::Colored_Shader()
{
	return programs["Colored"];
}
