#include "processing/background_service.hpp"

namespace Engine::Background {

	static BackgroundService& get_background_service()
	{
		static BackgroundService background_service;
		background_service.start_processing();
		return background_service;
	}

	static SomeOtherBackgroundService& get_other_background_service()
	{
		static SomeOtherBackgroundService background_service;
		background_service.start_processing();
		return background_service;
	}

	void submit_work(BackgroundFunction&& f, TaskPriority prio) { 
	get_background_service().submit(std::move(f), prio); }

		void submit_work(SomeOtherBackgroundFunction&& f, TaskPriority prio) { get_other_background_service().submit(std::move(f), prio); }

} // namespace Engine::Background
