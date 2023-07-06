#include "opengl/uniform_buffer.hpp"

#include <glad/glad.h>

namespace OpenGL::UniformBuffer {

	UniformBuffer::UniformBuffer(std::size_t size)
		: max_size(size)
	{
		glCreateBuffers(1, &object);
		glNamedBufferData(object, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, object);
	}

	UniformBuffer::~UniformBuffer() { glDeleteBuffers(1, &object); }

	void UniformBuffer::set_data(const void* data, std::size_t size)
	{
		bind();
		glNamedBufferSubData(object, 0, size, data);
		unbind();
	}

	void UniformBuffer::bind() { glBindBuffer(GL_UNIFORM_BUFFER, object); }

	void UniformBuffer::unbind() { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

} // namespace OpenGL::UniformBuffer