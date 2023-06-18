#include "common/clock.hpp"

#include <GLFW/glfw3.h>

namespace GLFW::Clock {

	float time_ms() { return glfwGetTime() * 1000.f; }

	float time_ns() { return glfwGetTime() * 1'000'000.f; }

	float time() { return static_cast<float>(glfwGetTime()); }

} // namespace GLFW::Clock

namespace Engine::Clock {
	float Clock::time() { return GLFW::Clock::time(); }

	float Clock::time_ms() { return GLFW::Clock::time_ms(); }

	float Clock::time_ns() { return GLFW::Clock::time_ns(); }

} // namespace Engine::Clock
