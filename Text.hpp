/*
 * Text.hpp
 *
 *  Created on: Jan 20, 2015
 *      Author: alxndr
 */
#pragma once
#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <map>

#include "Shader.hpp"

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class Font{
public:
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;

	Font(std::string path);
	void drawString(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	void loadFont(std::string path);

};



#endif /* TEXT_HPP_ */
