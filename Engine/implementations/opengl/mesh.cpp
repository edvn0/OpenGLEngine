//
// Created by edwin on 6/18/23.
//

#include "graphics/mesh.hpp"

#include "common/fs.hpp"
#include "common/verify.hpp"
#include "opengl/mesh.hpp"

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
		reader_config.mtl_search_path = path.parent_path().string(); // Path to material files

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

				if (unique_vertices.count(vertex) == 0) {
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

		glDeleteBuffers(1, &vertex_object);
		glDeleteBuffers(1, &index_object);
	}

	Mesh::Mesh(std::string_view name, const void*, std::size_t)
		: mesh_name(name)
	{
	}

	Mesh::Mesh(const std::filesystem::path& path)
		: mesh_name(path.filename().string())
	{
		auto&& [vertices, indices] = read_obj(path);

		vertex_count = vertices.size();
		index_count = indices.size();

		glGenBuffers(1, &vertex_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Engine::Graphics::Mesh::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), std::bit_cast<const void*>(4 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), std::bit_cast<const void*>(4 * sizeof(GLfloat) + 3 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenBuffers(1, &index_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Mesh::draw() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertex_object);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_object);

		glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} // namespace OpenGL::Mesh