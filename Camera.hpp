/*
 * Camera.hpp
 *
 *  Created on: Jan 17, 2015
 *      Author: alxndr
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
	//Camera Attributes
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	//Euler Angles
	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

    Camera(	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);

    Camera(	GLfloat posX, GLfloat posY, GLfloat posZ,
    		GLfloat upX, GLfloat upY, GLfloat upZ,
			GLfloat yaw, GLfloat pitch);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLfloat deltaTime, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

private:
    void updateCameraVectors();
};




#endif /* CAMERA_HPP_ */
