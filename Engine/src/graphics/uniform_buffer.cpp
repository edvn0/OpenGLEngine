#include "graphics/uniform_buffer.hpp"

#include "opengl/uniform_buffer.hpp"

namespace Engine::Graphics::UniformBuffer {

	RefPtr<UniformBuffer> UniformBuffer::construct(std::size_t size) { return construct_ref<OpenGL::UniformBuffer::UniformBuffer>(size); }

} // namespace Engine::Graphics::UniformBuffer
