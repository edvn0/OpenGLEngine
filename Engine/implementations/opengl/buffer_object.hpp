#pragma once

#include "graphics/buffer_object.hpp"
#include "graphics/types.hpp"

namespace OpenGL::BufferObject {

	class VertexBuffer : public Engine::Graphics::BufferObject::VertexBuffer {
	public:
		~VertexBuffer() override;
		explicit VertexBuffer(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices);

		void bind() override;
		void unbind() override;
		std::string_view get_identifier() override { return "VertexBuffer"; };

		std::size_t count() const override { return vertices; };

	private:
		GLuint object { 0 };
		std::size_t vertices { 0 };
	};

	class IndexBuffer : public Engine::Graphics::BufferObject::IndexBuffer {
	public:
		~IndexBuffer() override;
		explicit IndexBuffer(std::vector<std::uint32_t>&& indices);

		void bind() override;
		void unbind() override;
		std::string_view get_identifier() override { return "IndexBuffer"; };

		std::size_t count() const override { return indices; };

	private:
		GLuint object { 0 };
		std::size_t indices { 0 };
	};

} // namespace OpenGL::BufferObject