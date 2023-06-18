#include "graphics/window.hpp"

#include "common/logger.hpp"
#include "common/types.hpp"
#include "common/verify.hpp"
#include "glfw/glfw_window.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Engine::Window {

	static constexpr auto set_setting_value = [](auto& setting_object, const std::string& key, const std::string& value) {
		if (key == "width")
			setting_object.width = static_cast<std::uint16_t>(std::stoul(value));
		else if (key == "height")
			setting_object.height = static_cast<std::uint16_t>(std::stoul(value));
		else if (key == "title")
			setting_object.title = value;
		else
			Verify::that(false);
	};

	RefPtr<Window> Window::construct(Context::Context& context, const std::filesystem::path& settings_file)
	{
		return construct_ref<GLFW::Window::Window>(context, settings_file);
	}

	Window::Window(Context::Context& graphics_context, const std::filesystem::path& window_settings)
		: context(graphics_context)
	{
		deserialise_window_settings(window_settings);
	}

	void Window::deserialise_window_settings(const std::filesystem::path& settings_file)
	{
		Logging::Logger logger { "Window::WindowSettings" };
		std::ifstream input_stream { settings_file, std::ios::ate | std::ios::in };
		if (!input_stream) {
			logger.error("Could not open path {}", settings_file.string());
			return;
		}
		const std::size_t size = static_cast<std::size_t>(input_stream.tellg());
		input_stream.seekg(0);

		std::string buffer { "", size };
		input_stream.read(buffer.data(), size);

		std::istringstream is_file(buffer);
		std::string line;
		while (std::getline(is_file, line)) {
			std::istringstream is_line(line);
			std::string key;
			if (std::getline(is_line, key, '=')) {
				std::string value;
				if (std::getline(is_line, value)) {
					set_setting_value(settings, key, value);
				}
			}
		}

		logger.info("Finished deserialisation.");
		logger.info("Window width: {}, Window height: {}", settings.width, settings.height);
	}

	void Window::serialise_window_settings(const std::filesystem::path& output_path)
	{
		Logging::Logger logger { "Window::WindowSettings" };
		std::ofstream output_stream { output_path };
		if (!output_stream) {
			logger.error("Could not open path {}", output_path.string());
			return;
		}

		const auto& [w, h, title] = settings;
		output_stream << "width=" << std::to_string(w) << "\n";
		output_stream << "height=" << std::to_string(h) << "\n";
		output_stream << "title=" << title << "\n";
	}

} // namespace Engine::Window
