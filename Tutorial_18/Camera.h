#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <memory>
using namespace std;

class Camera
{
public:
	Camera(int window_width, int window_height);
	~Camera();

	glm::mat4 Get_Projection();

	void Update_Viewport(int new_width, int new_height);

private:
	glm::mat4 projection;
};

static unique_ptr<Camera> camera;