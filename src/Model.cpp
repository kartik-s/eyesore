#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Vertex.h"

using namespace eyesore;
using namespace glm;

using std::string;
using std::vector;

static Mesh extractMesh(const aiMesh *mesh)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;

	for (int i = 0; i < mesh->mNumVertices; i++) {	
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];
		aiVector3D uv = mesh->mTextureCoords[0][i];

		vertices.push_back(Vertex(vec3(pos.x, pos.y, pos.z),
					vec3(norm.x, norm.y, norm.z),
					vec2(uv.x, uv.y)));
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(vertices, indices);
}

eyesore::Model::Model(const string &path)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

	for (int i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(extractMesh(scene->mMeshes[i]));
}

void eyesore::Model::render() const
{
	for (const Mesh &mesh : meshes)
		mesh.render();
}

