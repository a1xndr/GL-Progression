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
#include <iostream>

#include "Shader.hpp"

const GLfloat shapeVertices[] = {
//		x 		y			r		g		b
		0.5f, 	0.5f,		1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.0f,	1.0f,	0.0f,
		0.0f,	-0.5f,		0.0f,	0.0f,	1.0f
};


/*const GLuint vertexIndices[] = {
		0, 1, 3,
		1, 2, 3
};*/

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = SDL_CreateWindow("gl", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Event 	windowEvent;
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glViewport(0, 0, 800, 600);

    Shader shaderProgram("shaders/vertex.vs", "shaders/fragment.frag");

	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapeVertices), shapeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(2*(sizeof(GLfloat))));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//Create SDL Window

	//Mainloop
	bool continueLoop = true;
	GLfloat timeValue;
	GLint vertexColorLocation = glGetUniformLocation(shaderProgram.Program, "ourColor");
	while(continueLoop)
	{
		if(SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
			case SDL_QUIT:
				continueLoop=false;
				break;
			case SDL_KEYUP:
				switch(windowEvent.key.keysym.sym){
				case SDLK_ESCAPE:
					continueLoop=false;
					break;
				}
			}
		}
		glClearColor(0.2, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Use();

		timeValue = ((SDL_GetTicks()/10)%360)*0.0174532925;
		glUniform4f(vertexColorLocation,sin(timeValue)/2+0.5, 0.0f, 0.0, 1.0f);


        glBindVertexArray(VAO);

        /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);/**/
        glDrawArrays(GL_TRIANGLES, 0, 3 );
        /*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);/**/

        glBindVertexArray(0);
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}




