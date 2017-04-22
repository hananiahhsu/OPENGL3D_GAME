#include "MyCamera.h"


//MyCamera::~MyCamera()
//{
//
//}


//duplicate with GetViewMatrix
glm::mat4 MyCamera::GetWorldToViewMatrix() const
{
	return glm::lookAt(this->Position,this->Position + this->ViewDirection, this->Up);
}


void MyCamera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - old_mouse_pos;
	//2017.4.21-control the length of mouse moving
	float tlen = glm::length(mouseDelta);
	float sp = ROTATIONAL_SPEED;
	if (glm::length(mouseDelta) > 10.0)
	{
		old_mouse_pos = newMousePosition;
		return;
	}
	//Horizontal rotation
	//here glm::mat3() cut off the extra row of glm::rotate(mouseDelta.x, Up)
	ViewDirection = glm::mat3(glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, Up)) * ViewDirection;

	//vertical rotation
	strafe_dir = glm::cross(ViewDirection,Up);
	ViewDirection = glm::mat3(glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, strafe_dir)) * ViewDirection;
	old_mouse_pos = newMousePosition;
}

void MyCamera::moveForward()
{
	Position += MovementSpeed * ViewDirection;
}
void MyCamera::moveBackward()
{
	Position += -MovementSpeed * ViewDirection;
}
void MyCamera::StrafeLeft()
{
	Position += -MovementSpeed * strafe_dir;
}
void MyCamera::StrafeRight()
{
	Position += MovementSpeed * strafe_dir;
}
void MyCamera::moveUp()
{
	Position += MovementSpeed * Up;
}
void MyCamera::moveDown()
{
	Position += -MovementSpeed * Up;
}



