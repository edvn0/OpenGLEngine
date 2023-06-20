//
// Created by edwinc on 6/19/23.
//

#include "opengl/vertex_array.hpp"

#include <glad/glad.h>

namespace OpenGL::VertexArray {

	VertexArray::VertexArray(std::vector<Engine::Graphics::Mesh::Vertex>&& vertices, std::vector<std::uint32_t>&& indices)
	{
		vertices_count = vertices.size();
		indices_count = indices.size();

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// VERTEX BUFFER
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		using V = Engine::Graphics::Mesh::Vertex;

		glBufferData(GL_ARRAY_BUFFER, sizeof(V) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(V), std::bit_cast<const void*>(nullptr));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(V), std::bit_cast<const void*>(offsetof(V, tex_coord)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(V), std::bit_cast<const void*>(offsetof(V, normal)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// INDEX BUFFER
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vao); }

} // namespace OpenGL::VertexArray