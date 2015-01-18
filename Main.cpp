/*
 * main.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: alxndr
 */

#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <iostream>


#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

const GLfloat shapeVertices[] = {
//		x 		y				s		t
	    -0.5f, 	-0.5f, 	-0.5f,  0.0f, 	0.0f,
	     0.5f, 	-0.5f, 	-0.5f,  1.0f, 	0.0f,
	     0.5f,  0.5f, 	-0.5f,  1.0f, 	1.0f,
	     0.5f,  0.5f, 	-0.5f,  1.0f, 	1.0f,
	    -0.5f,  0.5f, 	-0.5f,  0.0f, 	1.0f,
	    -0.5f, -0.5f, 	-0.5f,  0.0f, 	0.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3(2.0f, 5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f, 3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f, 2.0f, -2.5f),
  glm::vec3(1.5f, 0.2f, -1.5f),
  glm::vec3(-1.3f, 1.0f, -1.5f)
};


const GLuint vertexIndices[] = {
		0, 1, 3,
		1, 2, 3
};

int main(int argc, char *argv[])
{

	//IMG_Init();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* window = SDL_CreateWindow("gl", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Event 	windowEvent;
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
    glViewport(0, 0, 1024, 768);
	glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glEnable(GL_DEPTH_TEST);


	Texture cat("textures/cat.png");
	Texture rubicks("textures/rubicks.png");
    Shader shaderProgram("shaders/vertex.vs", "shaders/fragment.frag");


	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapeVertices), shapeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (GLvoid*)(2*(sizeof(GLfloat))));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*(sizeof(GLfloat))));
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	//Create SDL Window

	//Mainloop
	bool continueLoop = true;
	GLfloat timeValue;
	GLint vertexColorLoc = glGetUniformLocation(shaderProgram.Program, "ourColor");
	GLint transformLoc = glGetUniformLocation(shaderProgram.Program, "transform");
	GLint modelLoc = glGetUniformLocation(shaderProgram.Program, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram.Program, "view");
	GLint projectionLoc = glGetUniformLocation(shaderProgram.Program, "projection");
	shaderProgram.Use();


	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	double previousTick=SDL_GetTicks();
	while(continueLoop)
	{
		double tickLength=(SDL_GetTicks()-previousTick)/1000;
		previousTick=SDL_GetTicks();
		while(SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
			case SDL_QUIT:
				continueLoop=false;
				break;
			case SDL_MOUSEMOTION:
				camera.ProcessMouseMovement(windowEvent.motion.xrel,windowEvent.motion.yrel,tickLength);
				break;
			}
		}

		if(state[SDL_SCANCODE_W]){
			camera.ProcessKeyboard(FORWARD, tickLength);
		}
		if(state[SDL_SCANCODE_S]){
			camera.ProcessKeyboard(BACKWARD, tickLength);
		}
		if(state[SDL_SCANCODE_A]){
			camera.ProcessKeyboard(LEFT, tickLength);
		}
		if(state[SDL_SCANCODE_D]){
			camera.ProcessKeyboard(RIGHT, tickLength);
		}
		if(state[SDL_SCANCODE_ESCAPE]){
			continueLoop=false;
		}


		glClearColor(0.2, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Use();

		timeValue = ((SDL_GetTicks()/10)%360)*(M_PI/180);
	    //glm::mat4 transform;
	    glm::mat4 model;
	    glm::mat4 view = camera.GetViewMatrix();
	    glm::mat4 projection;


		//transform = glm::translate(transform, glm::vec3(0.0f,0.0f,2.0f));
	    //transform = glm::rotate(transform, timeValue, glm::vec3(0.0, 0.0, 1.0));
	    //transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
		//glUniform4f(vertexColorLoc,sin(timeValue)/2+0.5, 0.0f, 0.0, 1.0f);


	    projection = glm::perspective((float)(60.0*(M_PI/180)), (float)1024/(float)768, 0.1f, 1000.0f);


		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, rubicks.texture);
		glUniform1i(glGetUniformLocation(shaderProgram.Program, "ourTexture1"),0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, cat.texture);
		glUniform1i(glGetUniformLocation(shaderProgram.Program, "ourTexture2"),1);

        glBindVertexArray(VAO);

        for(GLuint i = 0; i < 10; i++)
        {
        	glm::mat4 model;
        	model = glm::translate(model,cubePositions[i]);
        	model = glm::rotate(model, (float)(20.0*i*(M_PI/180))+timeValue, glm::vec3(1.0f,0.3f,0.5f));
        	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36 );
        }




        glBindVertexArray(0);
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}




