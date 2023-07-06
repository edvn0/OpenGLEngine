#pragma once

#include "core/event.hpp"
#include "core/mouse_event.hpp"
#include "scene/camera.hpp"

#include <glm/glm.hpp>

namespace Engine::Scene::SceneCamera {

	enum class CameraMode { NONE, FLYCAM, ARCBALL };

	class SceneCamera : public Camera::Camera {
	public:
		SceneCamera() = default;
		SceneCamera(const float fov, const float width, const float height, const float near_clip, const float far_clip);

		void on_update(std::float_t ts);
		void on_event(Engine::Core::Event::Event& e);

		float get_distance() const { return distance; }
		void set_distance(float distance) { pitch = distance; }
		void set_viewport_size(float width, float height)
		{
			viewport_width = width;
			viewport_height = height;
			update_projection();
		}

		void focus(const glm::vec3&);

		const glm::mat4& get_view_matrix() const { return view_matrix; }
		glm::mat4 get_view_projection() const { return projection * view_matrix; }

		glm::vec3 get_up_direction() const;
		glm::vec3 get_right_direction() const;
		glm::vec3 get_forward_direction() const;
		const glm::vec3& get_position() const { return position; }
		glm::quat get_orientation() const;

		float get_pitch() const { return pitch; }
		float get_yaw() const { return yaw; }

	private:
		void update_projection();
		void update_view();

		bool on_mouse_scroll(Engine::Core::Event::MouseScrolledEvent& e);

		void mouse_pan(const glm::vec2& delta);
		void mouse_rotate(const glm::vec2& delta);
		void mouse_zoom(float delta);

		void init();

		glm::vec3 calculate_position() const;

		std::pair<float, float> pan_speed() const;
		float rotation_speed() const;
		float zoom_speed() const;

		float get_camera_speed() const;

	private:
		float field_of_view = 45.0f;
		float aspect_ratio = 1.778f;
		float near_clip = 0.1f;
		float far_clip = 1000.0f;

		glm::mat4 view_matrix {};
		glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 focal_point = { 0.0f, 0.0f, 0.0f };

		glm::vec2 initial_mouse_position = { 0.0f, 0.0f };

		float normal_speed { 0.002f };

		float distance = 10.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;

		float viewport_width = 1280;
		float viewport_height = 720;

		float pitch_delta {};
		float yaw_delta {};
		glm::vec3 position_delta {};
		glm::vec3 right_direction {};

		CameraMode camera_mode { CameraMode::ARCBALL };

		float min_focus_distance { 100.0f };

		constexpr static float min_speed { 0.0005f }, max_speed { 2.0f };
	};

} // namespace Engine::Scene::SceneCamera