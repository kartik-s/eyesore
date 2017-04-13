#include "Mesh.h"

using namespace eyesore;

using std::vector;

eyesore::Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices):
	vertices(vertices), indices(indices)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0],
			GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid *) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid *) offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid *) offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void eyesore::Mesh::setShader(ShaderProgram shader)
{
	this->shader = shader;
}

void eyesore::Mesh::render() const
{
	shader.use();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size() / 3, GL_UNSIGNED_INT, &indices[0]); 
	glBindVertexArray(0);
}

