#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include <GL/glew.h>

#include "Shader.hpp"

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	string vertexCode;
	string fragmentCode;
	try
	{
		ifstream vShaderFile(vertexSourcePath);
		ifstream fShaderFile(fragmentSourcePath);

		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(exception e)
	{
		cout << "ERROR:SHADER:FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint compilationSuccess;
	GLchar errorInfoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << errorInfoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(fragment, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << errorInfoLog << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &compilationSuccess);
	if(!compilationSuccess)
	{
		glGetShaderInfoLog(this->Program, 512, NULL, errorInfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << errorInfoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

