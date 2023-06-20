#pragma once

#include "graphics/buffer_object.hpp"

#include <fmt/format.h>

template <> struct fmt::formatter<Engine::Graphics::Vertex::Vertex> {
	char presentation = 's';

	constexpr auto parse(format_parse_context& ctx)
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'v'))
			presentation = *it++;

		if (it != end && *it != '}')
			throw format_error("invalid format");

		return it;
	}

	template <typename FormatContext> auto format(const Engine::Graphics::Vertex::Vertex& v, FormatContext& ctx)
	{
		return format_to(
			ctx.out(), "Vertex(Position:{},UVs:{},Normals:{})", glm::to_string(v.pos), glm::to_string(v.tex_coord), glm::to_string(v.normal));
	}
};