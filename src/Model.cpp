#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"
#include "ShaderProgram.h"

using namespace eyesore;
using namespace glm;

using std::string;
using std::vector;
using std::stringstream;

const string eyesore::Model::MODEL_PATH = "../models/";

eyesore::Model::Model(string description)
{
	stringstream s(description);
	string name, mat;

	s >> name;
	
	load(MODEL_PATH + name);

	if (s >> mat)
		material = new Material(mat);
}

void eyesore::Model::load(const string &path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(extract(scene->mMeshes[i]));
}

void eyesore::Model::render()
{
	for (Mesh &mesh : meshes)
		mesh.render();
}

void eyesore::Model::render(Camera &camera)
{
	for (Mesh &mesh : meshes)
		mesh.render(camera, *material);
}

eyesore::Mesh eyesore::Model::extract(const aiMesh *mesh)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;

	for (int i = 0; i < mesh->mNumVertices; i++) {	
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];

		if (mesh->HasTextureCoords(0)) {
			aiVector3D uv = mesh->mTextureCoords[0][i];

			vertices.push_back(Vertex(vec3(pos.x, pos.y, pos.z),
						vec3(norm.x, norm.y, norm.z),
						vec2(uv.x, uv.y)));
		} else {
			vertices.push_back(Vertex(vec3(pos.x, pos.y, pos.z), vec3(norm.x, norm.y, norm.z)));
		}
	}

	if (mesh->HasFaces())
		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

	return Mesh(vertices, indices);
}

