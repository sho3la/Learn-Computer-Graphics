#include "Animation2D.h"

#include <string>
#include <sstream>

#include <glew.h>

Animation2D::Animation2D(const char * filename)
	: anim_cursor(0),
	current_frame_indx(0),
	speed(0.05f)
{
	FILE* fp = nullptr;
	const int bufferlen = 255;
	char line[bufferlen];

	fopen_s(&fp, filename, "r");

	if(fp == nullptr)
	{
			printf("erorr in reading animation file \n");
	}
	else
	{
		while (fgets(line, bufferlen, fp))
		{
			vector<int> result;

			stringstream ss(line);
			string token;
			while (getline(ss,token,','))
			{
				result.push_back(stoi(token));
			}

			glm::vec4 frame = glm::vec4(result[0], result[1], result[2], result[3]);
			frames.push_back(frame);
		}
	}

	frames_count = (int)frames.size();

	fclose(fp);
}

Animation2D::~Animation2D()
{
}

void Animation2D::play(Texture & spritetexture, Rectangle & rectangle, double deltatime)
{
	anim_cursor += deltatime;

	if(anim_cursor > speed)
	{
		current_frame_indx = (current_frame_indx + 1) % frames_count;
		anim_cursor = 0;
	}

	glm::vec4 frame = frames[current_frame_indx];

	// normalization
	frame.x /= spritetexture.width;
	frame.y /= spritetexture.height;
	frame.z /= spritetexture.width;
	frame.w /= spritetexture.height;

	vector<glm::vec2> uv;

	uv = {
		glm::vec2(frame.x,frame.y),
		glm::vec2(frame.x, frame.y + frame.w),
		glm::vec2(frame.x + frame.z, frame.y),
		
		glm::vec2(frame.x + frame.z, frame.y),
		glm::vec2(frame.x, frame.y + frame.w),
		glm::vec2(frame.x + frame.z, frame.y + frame.w)
	};

	glBindVertexArray(rectangle.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, rectangle.UVBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, NULL);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Animation2D::set_animation_speed(float newspeed)
{
	speed = newspeed;
}
