/*
 * Sprite.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: alxndr
 */

#include "Sprite.hpp"
#include <SDL2/SDL_image.h>

GLfloat vertices[] = {
      0.5f, 0.5f,	// Top Right
      0.5f, -0.5f,	// Bottom Right
      -0.5f, -0.5f,  // Bottom Left
      -0.5f, 0.5f	// Top Left
};
GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,	// First Triangle
        1, 2, 3		// Second Triangle
};

Sprite::Sprite(std::string path)
{
	loadSprite(path);
}

void Sprite::draw(Shader shader){
	glUseProgram(shader.Program);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite::loadSprite(std::string path){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
