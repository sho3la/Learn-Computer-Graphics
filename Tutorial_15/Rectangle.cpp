#include "Rectangle.h"

#include <glew.h>
#include <vector>
using namespace std;


Rectangle::Rectangle() : 
	position(glm::vec2(0)),
	scale(glm::vec2(1)),
	rotaion_angle(0.0f)
{
	glm::vec2 arr[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glm::vec4 colors[6] = {
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1)
	};

	glm::vec2 uv[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&CBO);
	glGenBuffers(1,&UVBO);



	glBindVertexArray(VAO);
	
	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &arr[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,CBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,4,GL_FLOAT,false,0,NULL);

	// for uv buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,UVBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,false,0,NULL);


	glBindBuffer(GL_ARRAY_BUFFER,0);

}

Rectangle::~Rectangle()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&CBO);
	glDeleteBuffers(1,&UVBO);

}

void Rectangle::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,6);
}

void Rectangle::Draw_Wireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,6);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

glm::mat4 Rectangle::GetTransformationMatrx()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f),glm::vec3(position,1.0f));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f),rotaion_angle,glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f),glm::vec3(scale,1.0f));

	return tarnslation * scal * Rotation ;
}

void Rectangle::setposition(glm::vec2 pos)
{
	position = pos;
}

void Rectangle::setscale(glm::vec2 scal)
{
	scale = scal;
}

void Rectangle::setrotation(float rotation)
{
	rotaion_angle = rotation;
}

glm::vec2 Rectangle::getposition()
{
	return position;
}

glm::vec2 Rectangle::getscale()
{
	return scale;
}

float Rectangle::getrotation()
{
	return rotaion_angle;
}

bool Rectangle::isCollided(Rectangle * other)
{

	if(//check x-axis
		position.x < other->position.x + other->scale.x &&
		position.x + scale.x > other->position.x &&

		//check y-axis
		position.y < other->position.y + other->scale.y &&
		position.y + scale.y > other->position.y)
	{
		return true;
	}


	return false;
}


//////////////////////////////////  SAT seperate axis theorm


vector<glm::vec2> get_vectors(Rectangle * rect)
{
	vector<glm::vec2> result;

	// screen origin
	glm::vec2 origin(0,0);

	glm::vec2 vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(0,0),0,1);
	vert = vert - origin;
	result.push_back(vert);

	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(0,1),0,1);
	vert = vert - origin;
	result.push_back(vert);


	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(1,1),0,1);
	vert = vert - origin;
	result.push_back(vert);

	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(1,0),0,1);
	vert = vert - origin;
	result.push_back(vert);

	return result;
}


vector<glm::vec2> get_corners(Rectangle * rect)
{
	vector<glm::vec2> result;

	glm::vec2 vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(0,0),0,1);
	result.push_back(vert);

	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(0,1),0,1);
	result.push_back(vert);


	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(1,1),0,1);
	result.push_back(vert);

	vert = rect->GetTransformationMatrx() * glm::vec4(glm::vec2(1,0),0,1);
	result.push_back(vert);

	return result;
}



vector<glm::vec2> get_prependicular_axes(vector<glm::vec2>& shap1, vector<glm::vec2>& shape2)
{
	vector<glm::vec2> result;

	glm::vec2 edge;

	for(size_t i =0 ; i < shap1.size(); ++i)
	{
		edge = shap1[(i+1) % shap1.size()] - shap1[i];

		edge = glm::normalize(edge);

		// get prep vector
		result.push_back(glm::vec2(-edge.y , edge.x));
	}


	for(size_t i =0 ; i < shape2.size(); ++i)
	{
		edge = shape2[(i+1) % shape2.size()] - shape2[i];

		edge = glm::normalize(edge);

		// get prep vector
		result.push_back(glm::vec2(-edge.y , edge.x));
	}

	return result;
}


// return range from min val to max val
glm::vec2 project_on_axis(vector<glm::vec2> shape,glm::vec2 axis)
{
	float min = FLT_MAX;
	float max = FLT_MIN;


	for(auto& vertx : shape)
	{
		float proj = glm::dot(vertx,axis);
		if(proj < min) min = proj;
		if(proj > max) max = proj;
	}

	return glm::vec2(min,max);
}

bool are_overlapping(glm::vec2 range_a, glm::vec2 range_b)
{
	return range_a.x <= range_b.y && range_a.y >= range_b.x;
}



bool Rectangle::isCollided_SAT(Rectangle * other)
{

	auto shape1 = get_vectors(this);
	auto shape2 = get_vectors(other);

	auto axes = get_prependicular_axes(shape1,shape2);

	for(auto& axis : axes)
	{
		glm::vec2 proj1 = project_on_axis(shape1,axis);
		glm::vec2 proj2 = project_on_axis(shape2,axis);

		if(!are_overlapping(proj1,proj2)) return false;
	}

	return true;
}

bool Rectangle::isCollided_SAT2(Circle * other)
{

	auto corners = get_corners(this);

	glm::vec2 rect_centre = GetTransformationMatrx() * glm::vec4(0.5f,0.5f, 0, 1);
	glm::vec2 box2circle = other->position - rect_centre;
	glm::vec2 box2circle_normalized = glm::normalize(box2circle);

	float max_range = FLT_MIN;

	for(auto& vertx : corners)
	{
		glm::vec2 vec = vertx - rect_centre;
		float proj = glm::dot(vec, box2circle_normalized);
		if(max_range < proj) max_range = proj;
	}

	float len = glm::length(box2circle);

	if(len - max_range - other->radius > 0 && len > 0) return false;

	return true;
}
