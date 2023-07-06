#pragma once

#include "core/event.hpp"
#include "core/mouse_code.hpp"

#include <sstream>

namespace Engine::Core::Event {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: mouse_x(x)
			, mouse_y(y)
		{
		}

		float get_x() const { return mouse_x; }
		float get_y() const { return mouse_y; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouse_x << ", " << mouse_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouse_x;
		float mouse_y;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y)
			: x_offset(x)
			, y_offset(y)
		{
		}

		float get_offset_x() const { return x_offset; }
		float get_offset_y() const { return y_offset; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_offset_x() << ", " << get_offset_y();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float x_offset, y_offset;
	};

	class MouseButtonEvent : public Event {
	public:
		Code::MouseCode get_mouse_button() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(Code::MouseCode in)
			: button(in)
		{
		}

		Code::MouseCode button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(Code::MouseCode button)
			: MouseButtonEvent(button)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(Code::MouseCode button)
			: MouseButtonEvent(button)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
} // namespace Engine::Core::Event
