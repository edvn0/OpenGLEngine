#pragma once

#include "common/types.hpp"
#include "graphics/window.hpp"
#include "layer/layer.hpp"

#include <array>
#include <filesystem>
#include <memory>

namespace Engine::Startup {

	template <std::size_t LayerCount> class Main final {
	public:
		explicit Main(std::filesystem::path path);
		~Main();

		void compile_and_run();

		template <typename L, typename... Args> void add_layer(Args&&... args)
		{
			layers[layers_index++].reset(new L { std::forward<Args>(args)... });
		}

	private:
		bool layers_are_valid() const
		{
			for (const auto& layer : layers) {
				if (!layer)
					return false;
			}
			return true;
		}

	private:
		std::array<Engine::ScopePtr<Engine::Layer::Layer>, LayerCount> layers { nullptr };
		std::size_t layers_index { 0 };
		RefPtr<Window::Window> window;
		std::filesystem::path cwd;
	};

} // namespace Engine::Startup
