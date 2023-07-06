#include "scene/scene_camera.hpp"

#include "core/event.hpp"
#include "core/input.hpp"
#include "core/mouse_code.hpp"
#include "core/mouse_event.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp>

namespace Engine::Scene::SceneCamera {

	SceneCamera::SceneCamera(const float fov, const float width, const float height, const float near_p, const float far_p)
		: Camera::Camera(glm::perspectiveFov(glm::radians(fov), width, height, far_p, near_p),
			glm::perspectiveFov(glm::radians(fov), width, height, near_p, far_p))
		, field_of_view(glm::radians(fov))
		, near_clip(near_p)
		, far_clip(far_p)
		, focal_point(0.0f)
	{
		init();
	}

	void SceneCamera::init()
	{
		constexpr glm::vec3 p = { -5, 5, 5 };
		distance = glm::distance(p, focal_point);

		yaw = 3.0f * glm::pi<float>() / 4.0f;
		pitch = glm::pi<float>() / 4.0f;

		position = calculate_position();
		const glm::quat orientation = get_orientation();
		direction = glm::eulerAngles(orientation) * (180.0f / glm::pi<float>());
		view_matrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
		view_matrix = glm::inverse(view_matrix);
	}

	void SceneCamera::on_update(std::float_t ts)
	{
		const glm::vec2& mouse { Core::Input::mouse_x(), Core::Input::mouse_y() };
		const glm::vec2 delta = (mouse - initial_mouse_position) * 0.002f;

		if (Core::Input::all(Core::Code::MouseCode::MOUSE_BUTTON_1) && !Core::Input::all(Core::Code::KeyCode::KEY_LEFT_ALT)) {
			camera_mode = CameraMode::FLYCAM;
			disable_mouse();
			const float yaw_sign = get_up_direction().y < 0 ? -1.0f : 1.0f;

			const float speed = get_camera_speed();

			if (Core::Input::all(Core::Code::KeyCode::Q))
				position_delta -= ts * speed * glm::vec3 { 0.f, yaw_sign, 0.f };
			if (Core::Input::all(Core::Code::KeyCode::E))
				position_delta += ts * speed * glm::vec3 { 0.f, yaw_sign, 0.f };
			if (Core::Input::all(Core::Code::KeyCode::S))
				position_delta -= ts * speed * direction;
			if (Core::Input::all(Core::Code::KeyCode::W))
				position_delta += ts * speed * direction;
			if (Core::Input::all(Core::Code::KeyCode::A))
				position_delta -= ts * speed * right_direction;
			if (Core::Input::all(Core::Code::KeyCode::D))
				position_delta += ts * speed * right_direction;

			constexpr float max_rate { 0.12f };
			yaw_delta += glm::clamp(yaw_sign * delta.x * rotation_speed(), -max_rate, max_rate);
			pitch_delta += glm::clamp(delta.y * rotation_speed(), -max_rate, max_rate);

			right_direction = glm::cross(direction, glm::vec3 { 0.f, yaw_sign, 0.f });

			direction = glm::rotate(glm::normalize(glm::cross(
										glm::angleAxis(-pitch_delta, right_direction), glm::angleAxis(-yaw_delta, glm::vec3 { 0.f, yaw_sign, 0.f }))),
				direction);

			const float current_distance = glm::distance(focal_point, position);
			focal_point = position + get_forward_direction() * current_distance;
			distance = current_distance;
		} else if (Core::Input::all(Core::Code::KeyCode::KEY_LEFT_ALT)) {
			camera_mode = CameraMode::ARCBALL;

			if (Core::Input::all(Core::Code::MouseCode::Middle)) {
				mouse_pan(delta);
			} else if (Core::Input::all(Core::Code::MouseCode::Left)) {
				mouse_rotate(delta);
			} else if (Core::Input::all(Core::Code::MouseCode::Right)) {
				mouse_zoom(delta.x + delta.y);
			}
		}

		initial_mouse_position = mouse;
		position += position_delta;
		yaw += yaw_delta;
		pitch += pitch_delta;

		if (camera_mode == CameraMode::ARCBALL)
			position = calculate_position();

		update_view();
	}

	float SceneCamera::get_camera_speed() const
	{
		float speed = normal_speed;
		if (Core::Input::all(Core::Code::KeyCode::KEY_LEFT_CONTROL))
			speed /= 2 - glm::log(normal_speed);
		if (Core::Input::all(Core::Code::KeyCode::KEY_LEFT_SHIFT))
			speed *= 2 - glm::log(normal_speed);

		return glm::clamp(speed, min_speed, max_speed);
	}

	void SceneCamera::update_view()
	{
		const float yaw_sign = get_up_direction().y < 0 ? -1.0f : 1.0f;

		// Extra step to handle the problem when the camera direction is the same as the up vector
		const float cos_angle = glm::dot(get_forward_direction(), get_up_direction());
		if (cos_angle * yaw_sign > 0.99f)
			pitch_delta = 0.f;

		const glm::vec3 look_at = position + get_forward_direction();
		direction = glm::normalize(look_at - position);
		distance = glm::distance(position, focal_point);
		view_matrix = glm::lookAt(position, look_at, glm::vec3 { 0.f, yaw_sign, 0.f });

		// damping for smooth camera
		yaw_delta *= 0.6f;
		pitch_delta *= 0.6f;
		position_delta *= 0.8f;
	}

	void SceneCamera::focus(const glm::vec3& focus_point)
	{
		focal_point = focus_point;
		camera_mode = CameraMode::FLYCAM;
		if (distance > min_focus_distance) {
			distance -= distance - min_focus_distance;
			position = focal_point - get_forward_direction() * distance;
		}
		position = focal_point - get_forward_direction() * distance;
		update_view();
	}

	std::pair<float, float> SceneCamera::pan_speed() const
	{
		const float x = glm::min(float(viewport_width) / 1000.0f, 2.4f); // max = 2.4f
		const float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		const float y = glm::min(float(viewport_height) / 1000.0f, 2.4f); // max = 2.4f
		const float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float SceneCamera::rotation_speed() const { return 0.3f; }

	float SceneCamera::zoom_speed() const
	{
		float distance = distance * 0.2f;
		distance = glm::max(distance, 0.0f);
		float speed = distance * distance;
		speed = glm::min(speed, 50.0f); // max speed = 50
		return speed;
	}

	void SceneCamera::on_event(Engine::Core::Event::Event& event)
	{
		Engine::Core::Event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<Engine::Core::Event::MouseScrolledEvent>([this](auto& e) { return on_mouse_scroll(e); });
	}

	bool SceneCamera::on_mouse_scroll(Engine::Core::Event::MouseScrolledEvent& e)
	{
		if (Core::Input::mouse_pressed(Core::Code::MouseCode::KEY_RIGHT)) {
			normal_speed += e.get_offset_y() * 0.3f * normal_speed;
			normal_speed = std::clamp(normal_speed, min_speed, max_speed);
		} else {
			mouse_zoom(e.get_offset_y() * 0.1f);
			update_view();
		}

		return true;
	}

	void SceneCamera::mouse_pan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = pan_speed();
		focal_point -= get_right_direction() * delta.x * xSpeed * distance;
		focal_point += get_up_direction() * delta.y * ySpeed * distance;
	}

	void SceneCamera::mouse_rotate(const glm::vec2& delta)
	{
		const float yaw_sign = get_up_direction().y < 0.0f ? -1.0f : 1.0f;
		yaw_delta += yaw_sign * delta.x * rotation_speed();
		pitch_delta += delta.y * rotation_speed();
	}

	void SceneCamera::mouse_zoom(float delta)
	{
		distance -= delta * zoom_speed();
		const glm::vec3 forward_direction = get_forward_direction();
		position = focal_point - forward_direction * distance;
		if (distance < 1.0f) {
			focal_point += forward_direction * distance;
			distance = 1.0f;
		}
		position_delta += delta * zoom_speed() * forward_direction;
	}

	glm::vec3 SceneCamera::get_up_direction() const { return glm::rotate(get_orientation(), glm::vec3(0.0f, 1.0f, 0.0f)); }

	glm::vec3 SceneCamera::get_right_direction() const { return glm::rotate(get_orientation(), glm::vec3(1.f, 0.f, 0.f)); }

	glm::vec3 SceneCamera::get_forward_direction() const { return glm::rotate(get_orientation(), glm::vec3(0.0f, 0.0f, -1.0f)); }

	glm::vec3 SceneCamera::calculate_position() const { return focal_point - get_forward_direction() * distance + position_delta; }

	glm::quat SceneCamera::get_orientation() const { return glm::quat(glm::vec3(-pitch - pitch_delta, -yaw - yaw_delta, 0.0f)); }

} // namespace Engine::Scene::SceneCamera