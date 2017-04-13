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

eyesore::Model::Model(const string &path)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(extractMesh(scene->mMeshes[i]));

	Shader vert("../shaders/vert.glsl", GL_VERTEX_SHADER);
	Shader frag("../shaders/frag.glsl", GL_FRAGMENT_SHADER);
	ShaderProgram shader;

	shader.attach(vert);
	shader.attach(frag);

	for (Mesh &mesh : meshes)
		mesh.setShader(shader);
}

void eyesore::Model::render() const
{
	for (const Mesh &mesh : meshes)
		mesh.render();
}

eyesore::Mesh eyesore::Model::extractMesh(const aiMesh *mesh)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;

	for (int i = 0; i < mesh->mNumVertices; i++) {	
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D uv = mesh->mTextureCoords[0][i];

		if (mesh->HasNormals()) {
			aiVector3D norm = mesh->mNormals[i];
			vertices.push_back(Vertex(vec3(pos.x, pos.y, pos.z),
						vec3(norm.x, norm.y, norm.z),
						vec2(uv.x, uv.y)));
		} else {
			vertices.push_back(Vertex(vec3(pos.x, pos.y, pos.z), vec2(uv.x, uv.y)));
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

