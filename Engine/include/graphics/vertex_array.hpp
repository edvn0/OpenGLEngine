//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/identifiable.hpp"
#include "common/types.hpp"
#include "core/bindable.hpp"

#include <cstdint>
#include <filesystem>

namespace Engine::Graphics::VertexArray {

	class VertexArray : public Engine::Core::Bindable::Bindable, Engine::Common::Identifiable::Identifiable {
	public:
		virtual ~VertexArray() = default;

		static RefPtr<VertexArray> construct();
	};

}
