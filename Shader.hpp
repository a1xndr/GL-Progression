/*
 * Shader.hpp
 *
 *  Created on: Jan 15, 2015
 *      Author: alxndr
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include <GL/glew.h>

class Shader
{
public:
	//Program ID
	GLuint Program;
	//Constructor reads and assembles vertex and fragment shader.
	//Use the compiled program



	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	void Use() { glUseProgram(this->Program); }
};
#endif /* SHADER_HPP_ */
