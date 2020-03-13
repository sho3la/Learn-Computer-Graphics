#include "Circle.h"
#include <vector>
using namespace std;

#include <glew.h>

inline static void
generate(float r, int segments, vector<glm::vec2>& out_verts, vector<glm::vec4>& out_colors)
{
	// assume that circle origin 0,0
	for(int i = 0 ; i < segments; ++i)
	{
		
		//circle equation generation
		float theta = 2.0f *  3.1415926f  * float(i) / float(segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glm::vec2 vert (x,y);
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1));
	}


	for(float i = 0 ; i < 360; ++i)
	{
		glm::vec2 vert(r*cosf(i), r*sinf(i));
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1));

		i+= 0.5f;
		vert = glm::vec2(r*cosf(i), r*sinf(i));
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1));

		vert = glm::vec2(0,0);
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1));
	}

}

Circle::Circle(glm::vec3 circle)
{
	position = glm::vec2(circle.x, circle.y);
	radius = circle.z;

	vector<glm::vec2> verts;
	vector<glm::vec4> colors;
	generate(1, 100, verts, colors);

	num_verts = verts.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &CBO);

	glBindVertexArray(VAO);

	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec2), verts.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Circle::~Circle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &CBO);
}

void Circle::draw_outline()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, num_verts);
}

glm::mat4 Circle::GetTransformationMatrx()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(radius,radius, 1.0f));
	return tarnslation * scal;
}

bool Circle::Is_Collided(Circle * other)
{
	float dist = glm::distance(position, other->position);

	if(dist < radius + other->radius)
	{
		//colision detected
		return true;
	}

	return false;
}
