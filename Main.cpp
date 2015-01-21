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

#include <ft2build.h>
#include FT_FREETYPE_H

#include <math.h>
#include <iostream>
#include <string>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Text.hpp"
#include "Sprite.hpp"

#include "toolbox.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS_UPDATE_RATE 5

glm::vec3 pointLightPositions[] = {
    glm::vec3(-2.0f, 2.0f, 2.0f),
    glm::vec3(1.5f, -0.5f, 0.4f),
};


int main(int argc, char *argv[])
{

	//IMG_Init();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* window = SDL_CreateWindow("gl", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Event 	windowEvent;
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader objectShader("shaders/vertex.vs", "shaders/fragment.frag");
    Shader textShader("shaders/textVertex.vs", "shaders/textFragment.frag");

    Font Arial("fonts/arial.ttf");

    Sprite sprite("fonts/arial.ttf");


    //Load/Prepare Fonts.

    glm::mat4 textProjection = glm::ortho(0.0f, (float)WINDOW_WIDTH , 0.0f, (float)WINDOW_HEIGHT);

    Model ourModel("models/nanosuit.obj");


	//Create SDL Window

	//Mainloop
	bool continueLoop = true;
	GLfloat timeValue;
	objectShader.Use();


	Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	double previousTick=SDL_GetTicks();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int time;
	int framesSinceFpsUpdate = 0;
	int timeLastFpsUpdate=0;
	int framerate=0;
	while(continueLoop)
	{
		time = SDL_GetTicks();
		if( time - timeLastFpsUpdate >= 1000/FPS_UPDATE_RATE )
		{
			framerate = framesSinceFpsUpdate*1000/((time-timeLastFpsUpdate));
			timeLastFpsUpdate=SDL_GetTicks();
			framesSinceFpsUpdate=0;

		}
		framesSinceFpsUpdate++;


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
		if(state[SDL_SCANCODE_SPACE]){
			camera.ProcessKeyboard(UP, tickLength);
		}
		if(state[SDL_SCANCODE_LCTRL]){
			camera.ProcessKeyboard(DOWN, tickLength);
		}
		if(state[SDL_SCANCODE_ESCAPE]){
			continueLoop=false;
		}


		glClearColor(0.05f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		timeValue = ((SDL_GetTicks()/10)%360)*(M_PI/180);


	    glm::vec3 lightColor(0.8f,0.9f,1.0f);
	    glm::mat4 view = camera.GetViewMatrix();
	    glm::mat4 projection;
	    projection = glm::perspective((float)(60.0*(M_PI/180)), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 1000.0f);


		objectShader.Use();

	    projection = glm::perspective((float)(60.0*(M_PI/180)), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 1000.0f);
    	glUniformMatrix4fv(glGetUniformLocation(objectShader.Program, "projection"),
    														1, GL_FALSE, glm::value_ptr(projection));
    	glUniformMatrix4fv(glGetUniformLocation(objectShader.Program, "view"),
    														1, GL_FALSE, glm::value_ptr(view));


        // Set the lighting uniforms
        glUniform3f(glGetUniformLocation(objectShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        // Point light 1
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].diffuse"), 1.5f, 0.7f, 0.7f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].linear"), 0.009);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].quadratic"), 0.0032);
        // Point light 2
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].diffuse"), 1.0f, 1.5f, 3.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].specular"), 0.0f, 0.5f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].linear"), 0.009);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].quadratic"), 0.0032);



        /*for(int i=0; i<20; i++)
        {
            for(int j=0; j<1; j++)
            {
    		glm::mat4 model;
    		model = glm::translate(model,glm::vec3(pow(-1,i)*i*1.0f, -1.75f, pow(-1,j)*j*1.0f));
    		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    		glUniformMatrix4fv(glGetUniformLocation(objectShader.Program, "model"),
    	    														1, GL_FALSE, glm::value_ptr(model));
    		ourModel.Draw(objectShader);
            }
        }*/

        //model = glm::translate(model,glm::vec3(pow(-1,i)*i*1.0f, -1.75f, pow(-1,j)*j*1.0f));
        sprite.draw(objectShader);

        glDisable(GL_DEPTH_TEST);
		textShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(textShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(textProjection));
		Arial.drawString(textShader, tostr(framerate) + " fps" , 10, WINDOW_HEIGHT-(40*0.3f)-10, 0.3f, glm::vec3(1.0f,1.0f,1.0f));
        glEnable(GL_DEPTH_TEST);
		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}





