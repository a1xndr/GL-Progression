/*
 * Sprite.hpp
 *
 *  Created on: Jan 20, 2015
 *      Author: alxndr
 */

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

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


class Sprite{
public:
	GLuint TextureID;
	glm::ivec2 Size;

	GLuint VAO, VBO, EBO;
	Sprite(std::string path);
	void draw(Shader shader);
private:
	void loadSprite(std::string path);
};




#endif /* SPRITE_HPP_ */
