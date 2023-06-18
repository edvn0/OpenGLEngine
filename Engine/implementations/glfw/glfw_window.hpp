#pragma once

#include "common/logger.hpp"
#include "graphics/window.hpp"

extern "C" {
using GLFWwindow = struct GLFWwindow;
}

namespace GLFW::Window {

	using namespace Engine;

	class Window : public Engine::Window::Window {
	public:
		explicit Window(Graphics::Context::Context& context, const std::filesystem::path& settings_file);
		~Window();

		bool should_close() const override;
		void update() override;
		void poll() override;

	private:
		GLFWwindow* handle;
		Logging::Logger logger { "GLFWWindow" };
	};
} // namespace GLFW::Window
