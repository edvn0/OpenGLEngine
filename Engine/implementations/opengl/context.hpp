#pragma once

#include "graphics/context.hpp"

namespace OpenGL::Context {
	class Context : public Engine::Graphics::Context::Context {
	public:
		Context();
		~Context() override;
	};
} // namespace OpenGL::Context
