#include "opengl/context.hpp"

#include "common/logger.hpp"

#include <GLFW/glfw3.h>

namespace OpenGL::Context {

	Context::Context()
		: Engine::Graphics::Context::Context() {
		}

	Context::~Context() {}

} // namespace OpenGL::Context