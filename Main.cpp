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
//		Position			  Normal				Texture
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)
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
	SDL_Window* window = SDL_CreateWindow("gl", 100, 100, 1920, 1080, SDL_WINDOW_OPENGL);
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Event 	windowEvent;
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
    glViewport(0, 0, 1920, 1080);
	glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glEnable(GL_DEPTH_TEST);

	Texture crate("textures/crate2.png");
	Texture crate_specular("textures/crate2_specular.png");
	Texture crate_normal("textures/crate2_normal.png");
    Shader objectShader("shaders/vertex.vs", "shaders/fragment.frag");
    Shader lightShader("shaders/lightVertex.vs", "shaders/lightFragment.frag");


	GLuint VBO, VAO, EBO, lightVAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapeVertices), shapeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*(sizeof(GLfloat))));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*(sizeof(GLfloat))));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);


	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//Create SDL Window

	//Mainloop
	bool continueLoop = true;
	GLfloat timeValue;
	GLint modelLoc = glGetUniformLocation(objectShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(objectShader.Program, "view");
	GLint projectionLoc = glGetUniformLocation(objectShader.Program, "projection");


	GLint viewPositionLoc = glGetUniformLocation(objectShader.Program, "viewPos");

	//Material Properties
	GLint matDiffuseTextureLoc = glGetUniformLocation(objectShader.Program, "material.diffuse");
	GLint matSpecularTextureLoc = glGetUniformLocation(objectShader.Program, "material.specular");
	GLint matNormalTextureLoc = glGetUniformLocation(objectShader.Program, "material.normal");
	GLint matReflectivityLoc = glGetUniformLocation(objectShader.Program, "material.reflectivity");
	GLint matShininessLoc = glGetUniformLocation(objectShader.Program, "material.shininess");

	//Light Properties
	GLint ltPositionLoc = glGetUniformLocation(objectShader.Program, "light.position");
	GLint ltDirectionLoc = glGetUniformLocation(objectShader.Program, "light.direction");
	GLint ltAmbientColorLoc = glGetUniformLocation(objectShader.Program, "light.ambient");
	GLint ltDiffuseColorLoc = glGetUniformLocation(objectShader.Program, "light.diffuse");
	GLint ltSpecularColorLoc = glGetUniformLocation(objectShader.Program, "light.specular");
	GLint ltAttenConst = glGetUniformLocation(objectShader.Program, "light.constant");
	GLint ltAttenLin = glGetUniformLocation(objectShader.Program, "light.linear");
	GLint ltAttenQuad = glGetUniformLocation(objectShader.Program, "light.quadratic");
	GLint ltSpotCutOffLoc = glGetUniformLocation(objectShader.Program, "light.spotCutOff");
	GLint ltSpotOuterCutOffLoc = glGetUniformLocation(objectShader.Program, "light.spotOuterCutOff");


	GLint lightColorLoc = glGetUniformLocation(lightShader.Program, "lightColor");
	GLint lightModelLoc = glGetUniformLocation(lightShader.Program, "model");
	GLint lightViewLoc = glGetUniformLocation(lightShader.Program, "view");
	GLint lightProjectionLoc = glGetUniformLocation(lightShader.Program, "projection");

	objectShader.Use();


	Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
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

	    glm::mat4 model;
	    glm::mat4 view = camera.GetViewMatrix();
	    glm::mat4 projection;


	    projection = glm::perspective((float)(60.0*(M_PI/180)), (float)1920/(float)1080, 0.1f, 1000.0f);

	    glm::vec3 lightColor(0.8f,0.9f,1.0f);

        lightShader.Use();
        glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
        glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    	//glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
        glBindVertexArray(lightVAO);
        for(GLuint i = 0; i < 4; i++)
        {
        	glm::mat4 lightModel;

			lightModel = glm::translate(lightModel,pointLightPositions[i]);
			lightModel = glm::scale(lightModel, glm::vec3(0.2f));
			glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
			glDrawArrays(GL_TRIANGLES, 0, 36 );
        }
        glBindVertexArray(0);


		objectShader.Use();
        glBindVertexArray(VAO);

        //Material properties
    	glUniform1i(matDiffuseTextureLoc,0);
    	glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, crate.texture);
    	glUniform1i(matSpecularTextureLoc,1);
    	glActiveTexture(GL_TEXTURE1);
    	glBindTexture(GL_TEXTURE_2D, crate_specular.texture);
    	glUniform1i(matNormalTextureLoc,2);
    	glActiveTexture(GL_TEXTURE2);
    	glBindTexture(GL_TEXTURE_2D, crate_normal.texture);

        glUniform1f(matShininessLoc, 16.0f);
        glUniform1f(matReflectivityLoc, 0.7f);

        //Light Properties
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.diffuse"), 0.0f, 0.0f, 0.2f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
        // Point light 1
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].diffuse"), 0.4f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].quadratic"), 0.032);
        // Point light 2
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.2f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].quadratic"), 0.032);
        // Point light 3
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].diffuse"), 0.0f, 0.8f, 0.4f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].quadratic"), 0.032);
        // Point light 4
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].diffuse"), 0.0f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].quadratic"), 0.032);
        // SpotLight
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.direction"), camera.Direction.x, camera.Direction.y, camera.Direction.z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.quadratic"), 0.032);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

        glUniform3f(viewPositionLoc, camera.Position.x, camera.Position.y, camera.Position.z);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for(GLuint i = 0; i < 10; i++)
        {
        	glm::mat4 model;
        	model = glm::translate(model,cubePositions[i]);
        	model = glm::rotate(model, (float)(i*(M_PI/180))+timeValue, glm::vec3(0.1f,0.1f,0.05f));
        	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36 );
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}




