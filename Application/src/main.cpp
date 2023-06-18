#include "common/logger.hpp"
#include "common/logger_provider.hpp"
#include "graphics/graphics.hpp"
#include "main.hpp"
#include "startup/startup.hpp"
#include "my_layer.hpp"

#include <filesystem>

using ApplicationMain = Engine::Startup::Main<1>;

Application::Result<int> Application::engine_main()
{
	auto cwd = std::filesystem::current_path();
	Engine::Logging::LoggerProvider::initialise(cwd);

	ApplicationMain main(cwd);
	main.add_layer<MyLayer>(main);
	try {
		main.compile_and_run();
		return Application::Result<int>(0);
	} catch (const std::exception& exc) {
		return Application::Result<int>(exc);
	}
}

int main(int, char**)
{
	auto result = Application::engine_main();
	if (result) {
		return result.value();
	} else {
		return 1;
	}
}
