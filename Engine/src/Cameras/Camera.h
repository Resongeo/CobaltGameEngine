#pragma once

#include "Core/Math.h"

namespace Cobalt
{
	enum class ProjectionType
	{
		Perspective,
		Orthographic
	};

	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix()		const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()			const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()	const { return m_ViewProjectionMatrix; }

		const ProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(ProjectionType type);

		virtual void Update() { }
		virtual void SetViewportSize(float width, float height) { }

	protected:
		virtual void RecalculateViewMatrix() = 0;
		virtual void RecalculateProjection() = 0;

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

		float m_AspectRatio = 0.0f;
		float m_ViewportWidth = 0.0f;
		float m_ViewportHeight = 0.0f;

		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
	};
}