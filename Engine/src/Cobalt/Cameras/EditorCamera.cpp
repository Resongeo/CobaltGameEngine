#include "cbpch.h"

#include "Cobalt/Cameras/EditorCamera.h"
#include "Cobalt/Core/Core.h"
#include "Cobalt/Logger/Log.h"
#include "Cobalt/Input/Input.h"
#include "Cobalt/Input/KeyCodes.h"

namespace Cobalt
{
	EditorCamera::EditorCamera()
	{
		UpdateView();
	}

	void EditorCamera::SetProjectionType(ProjectionType type)
	{
		m_ProjectionType = type;
		UpdateView();
	}

	void EditorCamera::Update()
	{
		if (!m_IsMouseOverViewport) return;

		Vec2 mousePos = Input::GetMousePos();
		Vec2 delta = (mousePos - m_PrevMousePos) * 0.003f;
		m_PrevMousePos = mousePos;

		if (Input::GetMouseButtonDown(2))
		{
			auto [xSpeed, ySpeed] = CalculatePanSpeed();
			m_Position -= Vec3(1, 0, 0) * delta.x * xSpeed;
			m_Position += Vec3(0, 1, 0) * delta.y * ySpeed;
		}

		RecalculateViewMatrix();
	}

	void EditorCamera::SetViewportSize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& event)
	{
		if (!m_IsMouseOverViewport) return;

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent e)
	{
		float delta = e.GetYOffset() * 0.2f;

		m_Distance -= delta * CalculateZoomSpeed();;

		if (m_ProjectionType == ProjectionType::Orthographic)
		{
			m_Size -= delta;
			m_Size = std::max(m_Size, 0.01f);
		}
		else
		{
			m_Position.z = m_Distance;
		}

		UpdateView();
		return false;
	}

	/* Thank you The Cherno for the code :D */
	std::pair<float, float> EditorCamera::CalculatePanSpeed()
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f);
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor * m_PanSpeed, yFactor * m_PanSpeed };
	}

	float EditorCamera::CalculateZoomSpeed()
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);

		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		
		return speed;
	}

	void EditorCamera::RecalculateViewMatrix()
	{
		RecalculateProjection();

		Mat4 transform = Mat4(1.0f);
		transform = glm::translate(transform, m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), Vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::RecalculateProjection()
	{
		switch (m_ProjectionType)
		{
			case Cobalt::ProjectionType::Perspective:
			{
				m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
				break;
			}
			case Cobalt::ProjectionType::Orthographic:
			{
				float left = -(m_AspectRatio / 2.0f) * m_Size;
				float right = (m_AspectRatio / 2.0f) * m_Size;
				float bottom = -m_Size / 2.0f;
				float top = m_Size / 2.0f;
				m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1000.0f);
				break;
			}
		}
	}
}