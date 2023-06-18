//
// Created by edwin on 6/18/23.
//

#pragma once

#include "common/logger.hpp"
#include "errors/graphics_exception.hpp"

#include <filesystem>

namespace Engine::FS {
	static auto read_file(const std::filesystem::path& path)->std::string {
		Logging::Logger logger { "Engine::FS" };
		std::ifstream input_stream(path.string(), std::ios::ate | std::ios::in);
		if (!input_stream) {
			logger.error("Could not open path {}.", path.string());
			throw Errors::Graphics::InitialisationException();
		}

		const std::size_t size = input_stream.tellg();
		input_stream.seekg(0);

		std::string buffer;
		buffer.resize(size);
		input_stream.read(buffer.data(), size);

		return buffer;
	}
}
