#pragma once

#include "common/types.hpp"
#include "core/bindable.hpp"

#include <cstdint>

namespace Engine::Graphics::UniformBuffer {

	class UniformBuffer : public Engine::Core::Bindable::Bindable {
	public:
		virtual ~UniformBuffer() = default;

		virtual void set_data(const void* data, std::size_t size) = 0;

        static RefPtr<UniformBuffer> construct(std::size_t size);
	};

} // namespace Engine::Graphics::UniformBuffer
