#include "glfw/glfw_window.hpp"

#include "common/logger.hpp"
#include "common/types.hpp"
#include "common/verify.hpp"
#include "errors/graphics_exception.hpp"
#include "processing/background_service.hpp"

// clang-format off
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
// clang-format on

#include <bit>
#include <iostream>
#include <vector>

namespace GLFW::Window {

	using Engine::Logging::Logger;

	static void on_key_event(GLFWwindow* window, int key, int, int, int)
	{
		if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			return;
		}

		if (key == GLFW_KEY_K) {
			int k = rand() % 3;
			Engine::Background::TaskPriority prio { k };
			Engine::Background::submit_work(
				[](auto id, auto& logger) mutable {
					int random_sleep = rand() % 75;
					random_sleep += 1;
					std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(random_sleep));
					logger.debug("Current-{}", id);
				},
				prio);
		}
	}

	static void on_framebuffer_size_changed(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }

	static void error_callback(int error, const char* description) { fprintf(stderr, "Error: %s, Code: %d\n", description, error); }

	Window::Window(Graphics::Context::Context& context, const std::filesystem::path& window_settings)
		: Engine::Window::Window(context, window_settings)
	{
		if (const auto status = glfwInit(); status == GLFW_FALSE) {
			throw Engine::Errors::Graphics::InitialisationException();
		}
		glfwSetErrorCallback(error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

		const auto& [w, h, name] = get_settings();
		handle = glfwCreateWindow(w, h, name.data(), nullptr, nullptr);
		if (!handle) {
			throw Engine::Errors::Graphics::InitialisationException();
		}

		glfwMakeContextCurrent(handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) {
			logger.error("Could not initialise glad.");
			throw Engine::Errors::Graphics::InitialisationException();
		}
		const auto vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		const auto renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		logger.info("OpenGL Vendor {}", vendor);
		logger.info("OpenGL Renderer {}", renderer);
		logger.info("OpenGL Version {}", version);

		glfwSetFramebufferSizeCallback(handle, on_framebuffer_size_changed);
		glViewport(0, 0, w, h);
		glfwSwapInterval(1);

		glfwSetKeyCallback(handle, on_key_event);
	}

	Window::~Window()
	{
		glfwDestroyWindow(handle);
		logger.debug("{}", "GLFWwindow was destructed!"sv);
		glfwTerminate();
		logger.debug("{}", "GLFW terminated!"sv);
	}

	bool Window::should_close() const { return glfwWindowShouldClose(handle); }

	void Window::update() { glfwSwapBuffers(handle); }
	
	void Window::poll() { glfwPollEvents(); }

} // namespace GLFW::Window
