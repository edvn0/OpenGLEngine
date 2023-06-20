#pragma once

#include <fmt/format.h>

template <> struct fmt::formatter<std::filesystem::path> {
	char presentation = 's';

	constexpr auto parse(format_parse_context& ctx)
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == '/' || *it == '.' || *it == 'c' || *it == 'f' || *it == 's' || *it == 'n' || *it == 'p' || *it == 'e'))
			presentation = *it++;

		if (it != end && *it != '}')
			throw format_error("invalid format");

		return it;
	}

	template <typename FormatContext> auto format(const std::filesystem::path& p, FormatContext& ctx)
	{
		switch (presentation) {
		case '/':
			return format_to(ctx.out(), "{}", p.has_root_path() ? p.root_path().string() : p.string());
		case '.':
			return format_to(ctx.out(), "{}", p.has_relative_path() ? p.relative_path().string() : p.string());
		case 's':
			return format_to(ctx.out(), "{}", p.string());
		case 'n':
			return format_to(ctx.out(), "{}", p.stem().string());
		case 'f':
			return format_to(ctx.out(), "{}", p.filename().string());
		case 'e':
			return format_to(ctx.out(), "{}", p.extension().string());
		case 'c':
			return format_to(ctx.out(), "{}", std::filesystem::weakly_canonical(p).string());
		default:
			return format_to(ctx.out(), "{}", p.string());
		}
	}
};
