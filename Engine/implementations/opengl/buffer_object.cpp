#include "opengl/buffer_object.hpp"

#include "buffer_object.hpp"
#include "common/logger.hpp"
#include "common/logger_provider_fs_path.inl"
#include "common/logger_provider_vertex.inl"

#include <glad/glad.h>

namespace OpenGL::BufferObject {

	VertexBuffer::VertexBuffer(std::vector<Engine::Graphics::Vertex::Vertex>&& input_vertices)
	{
		vertices = input_vertices.size();

		glGenBuffers(1, &object);
		glBindBuffer(GL_ARRAY_BUFFER, object);

		using V = Engine::Graphics::Vertex::Vertex;
		constexpr auto vertex_size = sizeof(V);

		glBufferData(GL_ARRAY_BUFFER, vertex_size * input_vertices.size(), input_vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(nullptr));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(offsetof(V, tex_coord)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(offsetof(V, normal)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::VertexBuffer(const void* data, std::size_t size)
	{

		glGenBuffers(1, &object);
		glBindBuffer(GL_ARRAY_BUFFER, object);

		using V = Engine::Graphics::Vertex::Vertex;
		constexpr auto vertex_size = sizeof(V);
		vertices = size / vertex_size;

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(nullptr));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(offsetof(V, tex_coord)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertex_size, std::bit_cast<const void*>(offsetof(V, normal)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, object); }

	void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	IndexBuffer::IndexBuffer(std::vector<std::uint32_t>&& input_indices)
	{
		indices = input_indices.size();
		glGenBuffers(1, &object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, input_indices.size() * sizeof(uint32_t), input_indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object); }

	void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	IndexBuffer::~IndexBuffer() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace OpenGL::BufferObject