//
// Created by edwinc on 6/20/23.
//

#include "opengl/vertex_array.hpp"

#include "vertex_array.hpp"

#include <glad/glad.h>

namespace OpenGL::VertexArray {

	VertexArray::VertexArray(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices, std::vector<std::uint32_t>&& indices)
	{
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vbo = Engine::Graphics::BufferObject::VertexBuffer::construct(std::move(vertices));
		ibo = Engine::Graphics::BufferObject::IndexBuffer::construct(std::move(indices));

		glBindVertexArray(0);
	}

	VertexArray::VertexArray(const void* data, std::size_t size)
	{
		vbo = Engine::Graphics::BufferObject::VertexBuffer::construct(data, size);
		ibo = nullptr;
	}

	void VertexArray::bind()
	{
		glBindVertexArray(vao);
		if (ibo)
			ibo->bind();
		vbo->bind();
	}

	void VertexArray::unbind()
	{
		if (ibo)
			ibo->unbind();
		vbo->unbind();
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vao); }

	std::string_view VertexArray::get_identifier() { return "VertexArray"; }

} // namespace OpenGL::VertexArray
