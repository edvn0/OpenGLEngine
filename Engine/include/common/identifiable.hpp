//
// Created by edwinc on 6/19/23.
//

#pragma once

#include <string_view>

namespace Engine::Common::Identifiable {
	class Identifiable {
	public:
		virtual ~Identifiable() = default;

		virtual std::string_view get_identifier() = 0;
	};
}