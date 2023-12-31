//
// Created by edwin on 6/18/23.
//

#include "graphics/vertex_array.hpp"

#include "opengl/vertex_array.hpp"

namespace Engine::Graphics::VertexArray {

	RefPtr<VertexArray> VertexArray::construct(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices, std::vector<std::uint32_t>&& indices)
	{
		return construct_ref<OpenGL::VertexArray::VertexArray>(std::move(vertices), std::move(indices));
	}

	RefPtr<VertexArray> VertexArray::construct(const void* data, std::size_t size)
	{
		return construct_ref<OpenGL::VertexArray::VertexArray>(data, size);
	}

} // namespace Engine::Graphics::VertexArray
