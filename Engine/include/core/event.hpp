#pragma once

#include <bit>
#include <functional>
#include <string>
#include <string_view>

namespace Engine::Core::Event {

	static constexpr auto bit(auto x) { return 1 << x; }

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType : std::uint32_t {
		None = 0,
		WindowClose,
		WindowMinimize,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		WindowTitleBarHitTest,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
		ScenePreStart,
		ScenePostStart,
		ScenePreStop,
		ScenePostStop,
		EditorExitPlayMode,
		SelectionChanged
	};

	enum EventCategory : std::uint16_t {
		None = 0,
		EventCategoryApplication = bit(0),
		EventCategoryInput = bit(1),
		EventCategoryKeyboard = bit(2),
		EventCategoryMouse = bit(3),
		EventCategoryMouseButton = bit(4),
		EventCategoryScene = bit(5),
		EventCategoryEditor = bit(6)
	};

#define EVENT_CLASS_TYPE(type)                                                                                                                       \
	static EventType get_static_type() { return EventType::type; }                                                                                   \
	virtual EventType get_event_type() const override { return get_static_type(); }                                                                  \
	virtual std::string_view get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                                                                                               \
	virtual int get_category_flags() const override { return category; }

	class Event {
	public:
		bool has_been_handled = false;

		virtual ~Event() = default;
		virtual EventType get_event_type() const = 0;
		virtual std::string_view get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name().data(); }

		bool is_in_category(EventCategory category) { return get_category_flags() & category; }
	};

	class EventDispatcher {
		template <typename T> using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: current_event(event)
		{
		}

		template <typename T> bool dispatch(EventFn<T> func)
		{
			if (current_event.get_event_type() == T::get_static_type() && !current_event.has_been_handled) {
				T& as_t = *std::bit_cast<T*>(&current_event);
				current_event.has_been_handled = func(as_t);
				return true;
			}
			return false;
		}

	private:
		Event& current_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.to_string(); }
} // namespace Engine::Core::Event
