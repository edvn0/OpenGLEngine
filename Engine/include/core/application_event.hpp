#pragma once

#include "core/event.hpp"

#include <sstream>

namespace Engine::Core::Event {

	// TODO: Should this store previous size?
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(const std::uint32_t w, const std::uint32_t h)
			: width(w)
			, height(h)
		{
		}

		std::uint32_t get_width() const { return width; }
		std::uint32_t get_height() const { return height; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		std::uint32_t width;
		std::uint32_t height;
	};

	class WindowMinimizeEvent : public Event {
	public:
		WindowMinimizeEvent(bool minimized)
			: is_minimised(minimized)
		{
		}

		bool window_is_minimised() const { return is_minimised; }

		EVENT_CLASS_TYPE(WindowMinimize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		bool is_minimised = false;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() { }

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowTitleBarHitTestEvent : public Event {
	public:
		WindowTitleBarHitTestEvent(int x, int y, int& hit)
			: x(x)
			, y(y)
			, hit_position(hit)
		{
		}

		int get_x() const { return x; }
		int get_y() const { return y; }
		void set_hit(bool hit) { hit_position = static_cast<int>(hit); }

		EVENT_CLASS_TYPE(WindowTitleBarHitTest)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		int x;
		int y;
		int& hit_position;
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent() { }

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() { }

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() { }

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
} // namespace Engine::Core::Event