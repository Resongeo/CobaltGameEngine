#pragma once

#include "Cameras/Camera.h"

namespace Cobalt
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();

		void SetFOV(float fov) { m_FOV = fov; RecalculateProjection(); }
		float GetFOV() { return m_FOV; }

		void SetNearClip(float nearClip) { m_NearClip = nearClip; RecalculateProjection(); }
		float GetNearClip() { return m_NearClip; }
		
		void SetFarClip(float farClip) { m_FarClip = farClip; RecalculateProjection(); }
		float GetFarClip() { return m_FarClip; }
		
		void SetSize(float size) { m_Size = size; RecalculateProjection(); }
		float GetSize() { return m_Size; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const glm::vec3 GetPosition() const { return m_Position; }

		void SetRotaion(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		const float GetRotation() const { return m_Rotation; }

	private:
		virtual void RecalculateViewMatrix() override;
		virtual void RecalculateProjection() override;

	private:
		float m_FOV = 90.0f;
		float m_NearClip = 0.01f;
		float m_FarClip = 1000.0f;
		float m_Size = 2.0f;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
		float m_Rotation = 0.0f;
	};
}