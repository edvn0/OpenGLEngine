//
// Created by edwinc on 6/19/23.
//

#pragma once

#include "graphics/buffer_object.hpp"
#include "graphics/types.hpp"
#include "graphics/vertex_array.hpp"

namespace OpenGL::VertexArray {

	class VertexArray : public Engine::Graphics::VertexArray::VertexArray {
	public:
		VertexArray(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices, std::vector<std::uint32_t>&& indices);
		~VertexArray() override;

		void bind() override;
		void unbind() override;

		std::string_view get_identifier() override;

		std::size_t index_count() const override { return ibo->count(); };
		std::size_t vertex_count() const override { return vbo->count(); };

	private:
		GLuint vao { 0 };
		Engine::RefPtr<Engine::Graphics::BufferObject::VertexBuffer> vbo;
		Engine::RefPtr<Engine::Graphics::BufferObject::IndexBuffer> ibo;
	};

} // namespace OpenGL::VertexArray
