#pragma once

#include "common/logger.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <type_traits>

namespace Engine::Scene::Camera {

	class Camera {
	public:
		Camera() = default;
		
		template <typename T>
			requires std::is_same_v<T, glm::mat4>
		Camera(T&& proj, T&& unrev)
			: projection(std::forward<T>(proj))
			, unreversed_projection(std::forward<T>(unrev))
		{
		}

		Camera(const float deg_fov, const float width, const float height, const float near_p, const float far_p)
			: projection(glm::perspectiveFov(glm::radians(deg_fov), width, height, far_p, near_p))
			, unreversed_projection(glm::perspectiveFov(glm::radians(deg_fov), width, height, near_p, far_p))
		{
		}

		virtual ~Camera() = default;

		const glm::mat4& get_projection() const { return projection; }
		const glm::mat4& get_unreversed_projection() const { return unreversed_projection; }

		template <typename T>
			requires std::is_same_v<T, glm::mat4>
		void set_projection(T&& proj, T&& unrev)
		{
			projection = std::forward<T>(proj);
			unreversed_projection = std::forward<T>(unrev);
		}

		void set_perspective_projection(const float rad_fov, const float width, const float height, const float near_p, const float far_p)
		{
			projection = glm::perspectiveFov(rad_fov, width, height, far_p, near_p);
			unreversed_projection = glm::perspectiveFov(rad_fov, width, height, near_p, far_p);
		}

		void set_orthographic_projection(const float width, const float height, const float near_p, const float far_p)
		{
			projection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f, far_p, near_p);
			unreversed_projection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f, near_p, far_p);
		}

		float get_exposure() const { return m_Exposure; }
		float& get_exposure() { return m_Exposure; }

	protected:
		float m_Exposure = 0.8f;

		glm::mat4 projection = glm::mat4(1.0f);
		// Currently only needed for shadow maps and ImGuizmo
		glm::mat4 unreversed_projection = glm::mat4(1.0f);
	};

} // namespace Engine::Scene::Camera