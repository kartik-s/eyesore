#include <cassert>

#include "Mesh.h"
#include "Material.h"

using namespace eyesore;

using std::vector;

eyesore::Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices):
	vertices(vertices), indices(indices)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	if (!indices.empty())
		glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
			GL_STATIC_DRAW);

	if (!indices.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0],
				GL_STATIC_DRAW);
	}

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

void eyesore::Mesh::render()
{
	glBindVertexArray(vao);

	if (!indices.empty())
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}

void eyesore::Mesh::render(Camera &camera, Material &material)
{
	camera.use();
	material.use();
	render();
}

