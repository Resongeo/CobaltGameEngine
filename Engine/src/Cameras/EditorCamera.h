#pragma once

#include "Cameras/Camera.h"
#include "Events/MouseEvent.h"

namespace Cobalt
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();

		void SetFOV(float fov) { m_FOV = fov; RecalculateViewMatrix(); }
		float GetFOV() const { return m_FOV; }

		void SetNearClip(float nearClip) { m_NearClip = nearClip; RecalculateViewMatrix(); }
		float GetNearClip() const { return m_NearClip; }
		
		void SetFarClip(float farClip) { m_FarClip = farClip; RecalculateViewMatrix(); }
		float GetFarClip() const { return m_FarClip; }
		
		void SetSize(float size) { m_Size = size; RecalculateViewMatrix(); }
		float GetSize() const { return m_Size; }

		float* GetPanSpeed() { return &m_PanSpeed; }

		void SetMouseOverViewport(bool value) { m_IsMouseOverViewport = value; }

		virtual void SetProjectionType(ProjectionType type) override;

		virtual void Update() override;
		virtual void SetViewportSize(float width, float height) override;

		void OnEvent(Event& event);

	private:
		virtual void RecalculateViewMatrix() override;
		virtual void RecalculateProjection() override;

		bool OnMouseScroll(MouseScrolledEvent e);

		std::pair<float, float> CalculatePanSpeed();
		float CalculateZoomSpeed();

	private:
		float m_FOV = 90.0f;
		float m_NearClip = 0.01f;
		float m_FarClip = 1000.0f;
		float m_Size = 2.0f;

		glm::vec3 m_Position { 0.0f, 0.0f, 1.0f };
		glm::vec2 m_PrevMousePos { 0.0f };

		float m_Rotation = 0.0f;
		float m_PanSpeed = 5.0f;
		float m_Distance = 1.0f;

		bool m_IsMouseOverViewport = false;
	};
}