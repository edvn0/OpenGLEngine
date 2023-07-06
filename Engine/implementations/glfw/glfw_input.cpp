#include "core/input.hpp"
#include "core/key_code.hpp"
#include "core/mouse_code.hpp"

#include <GLFW/glfw3.h>

namespace Engine::Core::Input {

	auto get_window(GLFWwindow* window = nullptr) -> GLFWwindow*
	{
		static GLFWwindow* found_window = nullptr;
		if (!found_window)
			found_window = window;
		return found_window;
	}

	void setup_window_pointer(GLFWwindow* ptr) { get_window(ptr); }

	[[nodiscard]] float mouse_x()
	{
		double mouse_x;
		glfwGetCursorPos(get_window(), &mouse_x, nullptr);
		return static_cast<float>(mouse_x);
	}

	[[nodiscard]] float mouse_y()
	{
		double mouse_y;
		glfwGetCursorPos(get_window(), nullptr, &mouse_y);
		return static_cast<float>(mouse_y);
	}

	bool key_pressed(Code::KeyCode key_code) { return glfwGetKey(get_window(), static_cast<int>(key_code)) == GLFW_PRESS; }
	bool mouse_pressed(Code::MouseCode mouse_code) { return glfwGetMouseButton(get_window(), static_cast<int>(mouse_code)) == GLFW_PRESS; }

} // namespace Engine::Core::Input