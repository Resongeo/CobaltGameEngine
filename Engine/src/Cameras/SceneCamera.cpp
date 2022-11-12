#include "Cameras/SceneCamera.h"

namespace Cobalt
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
		RecalculateViewMatrix();
	}

	void SceneCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void SceneCamera::RecalculateProjection()
	{
		switch (m_ProjectionType)
		{
			case Cobalt::ProjectionType::Perspective:
			{
				m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
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