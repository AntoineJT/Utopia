#pragma once

#include "Cardia/Core/Event.hpp"
#include "Cardia/Core/Time.hpp"
#include "Cardia/Renderer/Camera.hpp"
#include "Cardia/ECS/Components.hpp"

#include <glm/gtc/quaternion.hpp>


namespace Cardia
{
	class EditorCamera
	{
	public:
		EditorCamera(float fov, float nearClip, float farClip);
		EditorCamera() = default;

		void OnUpdate();
		void OnEvent(Event& e);

		inline void SetViewportSize(float width, float height) { m_Camera.SetViewportSize(width, height); }

		glm::mat4 GetTransform() const
		{
			return m_Transform.getTransform();
		}

		SceneCamera& GetCamera()
		{
			return m_Camera;
		}
	private:

		void mousePan(const glm::vec2& delta);
		void mouseRotate(const glm::vec2& delta);
		float rotationSpeed() const;

	private:
		SceneCamera m_Camera;
		Component::Transform m_Transform;

		glm::vec2 m_InitialMousePosition { 0.0f, 0.0f };
		float m_MovementSpeed = 5;
		float m_BaseMovementSpeed = 5;
		float m_MaxMovementSpeed = 40;

	};
}