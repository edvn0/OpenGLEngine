//
// Created by edwinc on 6/19/23.
//

#include "opengl/vertex_array.hpp"

#include <glad/glad.h>

namespace OpenGL::VertexArray {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &object);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(object);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &object);
	}

} // namespace OpenGL