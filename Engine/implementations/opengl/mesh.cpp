//
// Created by edwin on 6/18/23.
//

#include "graphics/mesh.hpp"

#include "common/fs.hpp"
#include "common/verify.hpp"
#include "opengl/mesh.hpp"

#include <cstddef>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace OpenGL::Mesh {

	static std::tuple<std::vector<Engine::Graphics::Mesh::Vertex>, std::vector<std::uint32_t>> read_obj(const std::filesystem::path& path)
	{
		Engine::Logging::Logger logger { "OpenGL::Mesh" };
		std::string input_file = path.string();
		tinyobj::ObjReaderConfig reader_config;
		reader_config.mtl_search_path = path.parent_path().string();

		tinyobj::ObjReader reader;

		if (!reader.ParseFromFile(input_file, reader_config)) {
			if (!reader.Error().empty()) {
				logger.error("Error: {}", reader.Error());
			}

			throw Engine::Errors::Graphics::InitialisationException();
		}

		if (!reader.Warning().empty()) {
			logger.error("Error: {}", reader.Warning());
		}

		auto& attributes = reader.GetAttrib();
		auto& shapes = reader.GetShapes();
		auto& materials = reader.GetMaterials();
		(void)materials;

		std::vector<Engine::Graphics::Mesh::Vertex> vertices;
		std::unordered_map<Engine::Graphics::Mesh::Vertex, uint32_t> unique_vertices;
		std::vector<std::uint32_t> indices;

		// Loop over shapes
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				glm::vec4 position { attributes.vertices[3 * index.vertex_index + 0], attributes.vertices[3 * index.vertex_index + 1],
					attributes.vertices[3 * index.vertex_index + 2], 1.0f };

				glm::vec2 tex_coords { attributes.texcoords[3 * index.vertex_index + 0], attributes.texcoords[3 * index.vertex_index + 1] };

				glm::vec3 normals { attributes.normals[3 * index.vertex_index + 0], attributes.normals[3 * index.vertex_index + 1],
					attributes.normals[3 * index.vertex_index + 2] };

				Engine::Graphics::Mesh::Vertex vertex { position, tex_coords, normals };

				if (!unique_vertices.contains(vertex)) {
					unique_vertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(unique_vertices[vertex]);
			}
		}

		vertices.shrink_to_fit();
		indices.shrink_to_fit();

		Engine::Verify::that(shapes.size() > 0, "Shapes is empty");
		return std::make_tuple(vertices, indices);
	}

	Mesh::~Mesh()
	{
		auto logger = get_logger("OpenGL::Mesh");
		logger.debug("Destroying mesh with name {}!", mesh_name);
	}

	Mesh::Mesh(std::string_view name, const void*, std::size_t)
		: mesh_name(name)
	{
	}

	Mesh::Mesh(const std::filesystem::path& path)
		: mesh_name(path.filename().string())
	{
		auto&& [vertices, indices] = read_obj(path);
		vao = Engine::Graphics::VertexArray::VertexArray::construct(std::move(vertices), std::move(indices));
	}

	void Mesh::draw() const
	{
		vao->bind();
		glDrawElements(GL_TRIANGLES, vao->index_count(), GL_UNSIGNED_INT, nullptr);
		vao->unbind();
	}

} // namespace OpenGL::Mesh
