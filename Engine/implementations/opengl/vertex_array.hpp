//
// Created by edwinc on 6/19/23.
//

#pragma once

#include "graphics/vertex_array.hpp"

#include <glad/glad.h>

namespace OpenGL::VertexArray {

	class VertexArray : public Engine::Graphics::VertexArray::VertexArray {
	public:
		VertexArray(std::vector<Engine::Graphics::Mesh::Vertex>&& vertices, std::vector<std::uint32_t>&& indices);
		~VertexArray() override;

		void bind() override;
		void unbind() override;

		std::string_view get_identifier() override { return "VertexArray"; }

		std::size_t index_count() const override { return indices_count; }
		std::size_t vertex_count() const override { return vertices_count; }

	private:
		GLuint vao { 0 };
		GLuint vbo { 0 };
		GLuint ibo { 0 };

		std::size_t vertices_count { 0 };
		std::size_t indices_count { 0 };
	};

} // namespace OpenGL::VertexArray
