/*
 * Texture.cpp

 *
 *  Created on: Jan 17, 2015
 *      Author: alxndr
 */

#pragma once

#include "Texture.hpp"

using namespace std;

Texture::Texture(const GLchar* vertexSourcePath)
{
	SDL_Surface* surface = IMG_Load(vertexSourcePath);

	if(surface == NULL){
		std::cout << "ERROR::SURFACE::TEXTURE::LOADING_FAILED\n" << SDL_GetError() << std::endl;
		return;
	}
	GLuint mode = GL_RGB;
	if(surface->format->BytesPerPixel==4){
		mode = GL_RGBA;
	}
	this->w = surface->w;
	this->h = surface->h;
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(surface);
	glBindTexture(GL_TEXTURE_2D, 0);

}


