#include "Camera.h"

Camera::Camera() {}

glm::mat4 Camera::View()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::Gather()
{
    Previous = Projection;
    PV = Camera::View();
}
Camera::~Camera() {}