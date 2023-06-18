#pragma once

namespace Engine::Clock {

	class Clock {
	public:
		static float time();
		static float time_ms();
		static float time_ns();
	};

} // namespace Engine::Clock