#include "graphics/context.hpp"

#include "opengl/context.hpp"

namespace Engine::Graphics::Context {
	RefPtr<Context> Context::construct() { return construct_ref<OpenGL::Context::Context>(); }

} // namespace Engine::Context
