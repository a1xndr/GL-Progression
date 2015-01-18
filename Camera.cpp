/*
 * Camera.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: alxndr
 */

#pragma once

#include "Camera.hpp"

Camera::Camera(	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat yaw = -90.0f, GLfloat pitch = 0.0f):
			Direction(glm::vec3(0.0f, 0.0f, -1.0f)),
			MovementSpeed(5.0f), MouseSensitivity(0.25f), Zoom(45.0f)
{
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

Camera::Camera(	GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw, GLfloat pitch):
		Direction(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(5.0f), MouseSensitivity(0.25f), Zoom(45.0f)
{
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->Position, this->Position + this->Direction, this->WorldUp);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if(direction == FORWARD)
        this->Position += this->Direction * velocity;
    if(direction == BACKWARD)
        this->Position -= this->Direction * velocity;
    if(direction == LEFT)
        this->Position -= this->Right * velocity;
    if(direction == RIGHT)
        this->Position += this->Right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw += xoffset;
    this->Pitch += yoffset;
    if(constrainPitch)
    {
        if(this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if(this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }
    this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if(this->Zoom >= 1.0f && this->Zoom <= 45.0f)
        this->Zoom -= yoffset;
    if(this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if(this->Zoom >= 45.0f)
        this->Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Direction = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Direction, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up = glm::normalize(glm::cross(this->Right, this->Direction));
}

