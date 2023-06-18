#pragma once

#include "common/types.hpp"

#include <filesystem>
#include <string_view>

namespace Engine::Context {
	class Context;
}

namespace Engine::Window {

	struct WindowSettings {
		std::uint16_t width { 1280 };
		std::uint16_t height { 720 };
		std::string title { "Engine" };
	};

	class Window {
	public:
		virtual ~Window() = default;
		virtual bool should_close() const { return false; }
		virtual void update() { }
		virtual void poll() { }

		void serialise_window_settings(const std::filesystem::path&);

		const Context::Context& get_context() const { return context; }
		Context::Context& get_context() { return context; }

		const WindowSettings& get_settings() const { return settings; }

		static RefPtr<Window> construct(Context::Context&, const std::filesystem::path&);

	protected:
		explicit Window(Context::Context& graphics_context, const std::filesystem::path& window_settings);

	private:
		void deserialise_window_settings(const std::filesystem::path& settings_file);

		Context::Context& context;
		WindowSettings settings;
	};
} // namespace Engine::Window
