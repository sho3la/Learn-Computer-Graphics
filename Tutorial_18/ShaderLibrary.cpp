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
				// current pixel
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
			in vec2 vertex_uv;

			void main()
			{
				finalcolor = vertex_color;
			};
)CODE";

	programs.insert(pair<string,ShaderProgram*>("Colored",new ShaderProgram(vs,fs)));

	//////////////////////////////////////// checkboard shader
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
			in vec2 vertex_uv;

			uniform vec2 resolution;

			float checkboard(vec2 uv)
			{
				if((uv.x <= 0.5 || uv.y >= 0.5) && (uv.x >= 0.5 || uv.y <= 0.5)) return 1;
				return 0.0f;
			}

			void main()
			{
				float aspectratio = resolution.x / resolution.y;
				float tiling = 15;

				// normalize current uv
				vec2 rawuv = gl_FragCoord.xy / resolution;
				rawuv.x *= aspectratio;
				rawuv = mod(rawuv , 1 / tiling) * tiling;

				finalcolor = mix(vec4(1,1,1,1) , vec4(0.5,0.5,0.5,1) , checkboard(rawuv));
			};
)CODE";

	programs.insert(pair<string,ShaderProgram*>("Checkboard",new ShaderProgram(vs,fs)));
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

ShaderProgram * ShaderLibrary::Checkboard_Shader()
{
	return programs["Checkboard"];
}
