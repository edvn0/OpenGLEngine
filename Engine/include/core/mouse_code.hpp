#pragma once

#include <cstdint>
#include <string>

namespace Engine::Core::Code {

	enum class MouseCode : std::uint16_t {
		MOUSE_BUTTON_1 = 0,
		MOUSE_BUTTON_2 = 1,
		MOUSE_BUTTON_3 = 2,
		MOUSE_BUTTON_4 = 3,
		MOUSE_BUTTON_5 = 4,
		MOUSE_BUTTON_6 = 5,
		MOUSE_BUTTON_7 = 6,
		MOUSE_BUTTON_8 = 7,
		MOUSE_BUTTON_LAST = MOUSE_BUTTON_8,
		MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
		MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
		MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3,
		Left = MOUSE_BUTTON_1,
		Right = MOUSE_BUTTON_2,
		Middle = MOUSE_BUTTON_3,
	};

	inline std::ostream& operator<<(std::ostream& os, const MouseCode& code)
	{
		os << std::to_string(static_cast<int>(code));
		return os;
	}

} // namespace Engine::Core::Code
