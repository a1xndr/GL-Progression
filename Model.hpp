/*
 * Model.hpp
 *
 *  Created on: Jan 19, 2015
 *      Author: alxndr
 */
#pragma once

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_image.h>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

GLint TextureFromFile(const char* path, string directory);

class Model
{
public:
	vector<Texture> textures_loaded;

	Model(GLchar* path);

	void Draw(Shader shader);

private:
	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif /* MODEL_HPP_ */
