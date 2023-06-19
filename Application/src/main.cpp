#include "main.hpp"

#include "common/logger.hpp"
#include "common/logger_provider.hpp"
#include "graphics/graphics.hpp"
#include "my_layer.hpp"
#include "startup/startup.hpp"

#include <filesystem>

using ApplicationMain = Engine::Startup::Main<1>;

Application::Result<int> Application::engine_main()
{
	auto cwd = std::filesystem::current_path();
	Engine::Logging::LoggerProvider::initialise(cwd);

	ApplicationMain main(cwd);
	main.add_layer<MyLayer>(main);
	main.compile_and_run();
	return Application::Result<int>(0);
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
