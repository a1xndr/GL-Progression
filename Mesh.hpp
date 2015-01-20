/*
 * Mesh.hpp
 *
 *  Created on: Jan 19, 2015
 *      Author: alxndr
 */

#pragma once

#ifndef MESH_HPP_
#define MESH_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	float shininess=32.0f;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void Draw(Shader shader);

private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

#endif /* MESH_HPP_ */
