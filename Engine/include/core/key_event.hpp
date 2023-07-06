#pragma once

#include "core/event.hpp"
#include "core/key_code.hpp"

#include <sstream>

namespace Engine::Core::Event {

	using namespace Engine::Core::Code;

	class KeyEvent : public Event {
	public:
		KeyCode get_key_code() const { return key_code; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode keycode)
			: key_code(keycode)
		{
		}

		KeyCode key_code;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode keycode, int repeat)
			: KeyEvent(keycode)
			, repeat_count(repeat)
		{
		}

		int get_repeat_count() const { return repeat_count; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code << " (" << repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeat_count;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
} // namespace Engine::Core::Event