#include "Circle.h"

#include <glew.h>

inline static void generate_circle(float rad, int segments, vector<glm::vec2>& out_verts,  vector<glm::vec4>& out_colors)
{
	// assume that circle position origin (0,0)

	for(int i =0 ; i < segments; ++i)
	{

		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = rad * cosf(theta);
		float y = rad * sinf(theta);

		out_verts.push_back(glm::vec2(x,y));
		out_colors.push_back(glm::vec4(1,1,1,1));
	}


	for(float i = 0; i < 360; ++i)
	{
		glm::vec2 vert(rad * cosf(i) , rad * sinf(i));
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1,1,1,1));

		i += 0.5f;
		vert = glm::vec2(rad * cosf(i) , rad * sinf(i));
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1,1,1,1));

		vert = glm::vec2(0,0);
		out_verts.push_back(vert);
		out_colors.push_back(glm::vec4(1,1,1,1));
	}
}


Circle::Circle(glm::vec3 circ)
{
	position = glm::vec2(circ.x,circ.y);
	radius = circ.z;

	vector<glm::vec2> verts;
	vector<glm::vec4> colors;

	generate_circle(1,100,verts,colors);

	num_verts = (int)verts.size();

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

void Circle::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, num_verts);
}

void Circle::draw_wireframe()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, num_verts);
}

glm::mat4 Circle::gettransform()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(radius,radius, 1.0f));

	return tarnslation * scal;
}

bool Circle::isCollided(Circle * other)
{
	float dist  = glm::distance(position, other->position);
	if(dist < radius + other->radius) return true;
	return false;
}
