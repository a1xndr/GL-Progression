/*
 * Texture.hpp
 *
 *  Created on: Jan 17, 2015
 *      Author: alxndr
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>


using namespace std;


class Texture
{
public:
	GLuint texture;
	//Texture width/height
	int w, h;
	//Constructor loads image into SDL surface and creates/sets a GL texture to it.
	Texture(const GLchar* vertexSourcePath);

};



#endif /* TEXTURE_HPP_ */
