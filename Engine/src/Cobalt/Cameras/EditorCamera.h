#pragma once

#include "Cobalt/Cameras/Camera.h"
#include "Cobalt/Events/MouseEvent.h"

namespace Cobalt
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();

		void SetFOV(float fov) { m_FOV = fov; UpdateView(); }
		float GetFOV() const { return m_FOV; }
		float& GetFovAdr() { return m_FOV; }

		void SetNearClip(float nearClip) { m_NearClip = nearClip; UpdateView(); }
		float GetNearClip() const { return m_NearClip; }
		
		void SetFarClip(float farClip) { m_FarClip = farClip; UpdateView(); }
		float GetFarClip() const { return m_FarClip; }
		
		void SetSize(float size) { m_Size = size; UpdateView(); }
		float GetSize() const { return m_Size; }
		float& GetSizeAdr() { return m_Size; }

		float* GetPanSpeed() { return &m_PanSpeed; }

		void SetMouseOverViewport(bool value) { m_IsMouseOverViewport = value; }

		virtual void SetProjectionType(ProjectionType type) override;

		virtual void Update() override;
		virtual void SetViewportSize(float width, float height) override;

		void OnEvent(Event& event);

		void UpdateView()
		{
			RecalculateProjection();
			RecalculateViewMatrix();
		}

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

		Vec3 m_Position { 0.0f, 0.0f, 1.0f };
		Vec2 m_PrevMousePos { 0.0f };

		float m_Rotation = 0.0f;
		float m_PanSpeed = 5.0f;
		float m_Distance = 1.0f;

		bool m_IsMouseOverViewport = false;
	};
}