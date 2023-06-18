#pragma once

#include <cmath>

namespace Engine::Layer {
	class Layer {
	public:
		virtual ~Layer() = default;
		virtual void on_create() = 0;
		virtual void on_update(std::float_t time_step) = 0;
		virtual void on_delete() = 0;
	};
} // namespace Engine::Layer
