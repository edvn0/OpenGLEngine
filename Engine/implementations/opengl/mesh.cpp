//
// Created by edwin on 6/18/23.
//

#include "graphics/mesh.hpp"

#include "common/fs.hpp"
#include "common/verify.hpp"
#include "opengl/mesh.hpp"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include <tinyobjloader/tiny_obj_loader.h>

namespace OpenGL::Mesh {

	Mesh::Mesh(const void* , std::size_t){ }

	Mesh::Mesh(const std::filesystem::path& path)  {
		Engine::Logging::Logger logger {"OpenGL::Mesh"};
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

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();
		auto& materials = reader.GetMaterials();
		(void)materials;

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
					tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
					tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
					(void)vx;
					(void)vy;
					(void)vz;

					// Check if `normal_index` is zero or positive. negative = no normal data
					if (idx.normal_index >= 0) {
						tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
						tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
						tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
						(void)nx;
						(void)ny;
						(void)nz;

					}

					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
					if (idx.texcoord_index >= 0) {
						tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
						tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
						(void)tx;
						(void)ty;
					}

					// Optional: vertex colors
					// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
					// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
					// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}

		Engine::Verify::that(shapes.size() > 0, "Shapes is empty");
	}

}