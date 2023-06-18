#include "common/clock.hpp"
#include "graphics/context.hpp"
#include "graphics/graphics.hpp"
#include "graphics/window.hpp"
#include "startup/startup.hpp"

namespace Engine::Startup {

	static constexpr std::string_view window_setting_file_name = "window_settings.conf";

	template <std::size_t T>
	Main<T>::Main(std::filesystem::path path)
		: cwd(std::move(path))
	{
	}

	template <std::size_t T> Main<T>::~Main()
	{
		window->serialise_window_settings(cwd / window_setting_file_name);
		for (auto& layer : layers) {
			layer->on_delete();
		}
	}

	template <std::size_t T> void Main<T>::compile_and_run()
	{
		// Create graphics context
		context = Graphics::Context::Context::construct();
		// Create window
		window = Window::Window::construct(*context, cwd / window_setting_file_name);

		// Construct and initialise layers
		for (auto& layer : layers) {
			layer->on_create();
		}

		std::float_t start { Clock::Clock::time_ms() };
		std::float_t ts { 10.f };
		while (!window->should_close()) {
			window->poll();

			// Construct and initialise layers
			for (auto& layer : layers) {
				layer->on_update(ts);
			}

			window->update();
			ts = Clock::Clock::time_ms() - start;
			start = Clock::Clock::time_ms();
		}
	}

	// Probably won't need to support more than 4 layers...
	template class Main<1>;
	template class Main<2>;
	template class Main<3>;
	template class Main<4>;

} // namespace Engine::Startup
