#pragma once

#include "core/key_code.hpp"
#include "core/mouse_code.hpp"

#include <cstdint>
#include <type_traits>

extern "C" {
using GLFWwindow = struct GLFWwindow;
}

namespace Engine::Core::Input {

	void setup_window_pointer(GLFWwindow*);

	bool key_pressed(Code::KeyCode key);
	bool mouse_pressed(Code::MouseCode key);

	[[nodiscard]] float mouse_x();
	[[nodiscard]] float mouse_y();

	template <typename T>
	concept IsKey = std::is_same_v<T, Code::KeyCode> || std::is_same_v<T, Code::MouseCode>;

	template <IsKey... K> static bool any(K... key) { return (key_pressed(key) || ...); };
	template <IsKey... K> static bool all(K... key) { return (key_pressed(key) && ...); };

} // namespace Engine::Core::Input