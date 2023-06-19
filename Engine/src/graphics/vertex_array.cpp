//
// Created by edwin on 6/18/23.
//

#include "graphics/vertex_array.hpp"

#include "opengl/vertex_array.hpp"

namespace Engine::Graphics::VertexArray {

	RefPtr<VertexArray> VertexArray::construct() { return construct_ref<OpenGL::VertexArray::VertexArray>(); }

}