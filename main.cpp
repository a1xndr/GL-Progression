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

const GLchar* vertexShaderSource =
		"#version 330 core \n"

		"layout (location = 0) in vec2 position;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
		"}\0";

const GLchar* fragmentBlueShaderSource =
		"#version 330 core \n"

		"out vec4 color;\n"
		"void main()\n"
		"{\n"
			"color = vec4(0.3f, 0.5f, 0.8f, 1.0f);\n"
		"}\n\0";

const GLchar* fragmentRedShaderSource =
		"#version 330 core \n"

		"out vec4 color;\n"
		"void main()\n"
		"{\n"
			"color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";

const GLfloat shapeVertices[] = {
		0.5f, 	0.5f,
		0.5f,	-0.5f,
		-0.5f,	-0.5f,
		-0.5f,	0.5f
};

const GLuint vertexIndices[] = {
		0, 1, 3,
		1, 2, 3
};

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

	//Compile the Shaders
	GLint compilationSuccess;
	GLchar errorInfoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << errorInfoLog << std::endl;
	}

	GLuint fragmentBlueShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentBlueShader, 1, &fragmentBlueShaderSource, NULL);
	glCompileShader(fragmentBlueShader);
	glGetShaderiv(fragmentBlueShader, GL_COMPILE_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(fragmentBlueShader, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << errorInfoLog << std::endl;
	}

	GLuint fragmentRedShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentRedShader, 1, &fragmentRedShaderSource, NULL);
	glCompileShader(fragmentRedShader);
	glGetShaderiv(fragmentRedShader, GL_COMPILE_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(fragmentRedShader, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << errorInfoLog << std::endl;
	}

	GLuint shaderBlueProgram = glCreateProgram();
	glAttachShader(shaderBlueProgram, vertexShader);
	glAttachShader(shaderBlueProgram, fragmentBlueShader);
	glLinkProgram(shaderBlueProgram);
	glGetProgramiv(shaderBlueProgram, GL_LINK_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(shaderBlueProgram, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << errorInfoLog << std::endl;
	}

	GLuint shaderRedProgram = glCreateProgram();
	glAttachShader(shaderRedProgram, vertexShader);
	glAttachShader(shaderRedProgram, fragmentRedShader);
	glLinkProgram(shaderRedProgram);
	glGetProgramiv(shaderRedProgram, GL_LINK_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(shaderBlueProgram, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << errorInfoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentBlueShader);
	glDeleteShader(fragmentRedShader);

	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapeVertices), shapeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//Create SDL Window

	//Mainloop
	bool continueLoop = true;
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
        glUseProgram(shaderRedProgram);
        glBindVertexArray(VAO);

        /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);/**/
        glDrawElements(GL_TRIANGLES, sizeof(vertexIndices) , GL_UNSIGNED_INT, 0);
        /*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);/**/

        glBindVertexArray(0);
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}




