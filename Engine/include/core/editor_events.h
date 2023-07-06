#pragma once

#include "core/event.hpp"

#include <sstream>

namespace Engine::Core::Event {

	class EditorExitPlayModeEvent : public Event {
	public:
		EditorExitPlayModeEvent() = default;

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "EditorExitPlayModeEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EditorExitPlayMode)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)
	};

} // namespace Engine::Core::Event
