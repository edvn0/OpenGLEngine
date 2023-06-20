#include "graphics/buffer_object.hpp"

#include "opengl/buffer_object.hpp"

namespace Engine::Graphics::BufferObject {

	RefPtr<VertexBuffer> VertexBuffer::construct(std::vector<Engine::Graphics::Vertex::Vertex>&& vertices)
	{
		return construct_ref<OpenGL::BufferObject::VertexBuffer>(std::move(vertices));
	}

	RefPtr<IndexBuffer> IndexBuffer::construct(std::vector<std::uint32_t>&& indices)
	{
		return construct_ref<OpenGL::BufferObject::IndexBuffer>(std::move(indices));
	}

} // namespace Engine::Graphics::BufferObject