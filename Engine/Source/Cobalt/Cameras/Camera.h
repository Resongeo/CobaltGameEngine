#pragma once

#include "Cobalt/Core/Types/Math.h"

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

		const Mat4& GetProjectionMatrix()		const { return m_ProjectionMatrix; }
		const Mat4& GetViewMatrix()				const { return m_ViewMatrix; }
		const Mat4& GetViewProjectionMatrix()	const { return m_ViewProjectionMatrix; }

		const ProjectionType GetProjectionType() const { return m_ProjectionType; }
		virtual void SetProjectionType(ProjectionType type) = 0;

		virtual void Update() { }
		virtual void SetViewportSize(float width, float height) { }

	protected:
		virtual void RecalculateViewMatrix() = 0;
		virtual void RecalculateProjection() = 0;

	protected:
		Mat4 m_ProjectionMatrix = Mat4(1.0f);
		Mat4 m_ViewMatrix = Mat4(1.0f);
		Mat4 m_ViewProjectionMatrix = Mat4(1.0f);

		float m_AspectRatio = 0.0f;
		float m_ViewportWidth = 0.0f;
		float m_ViewportHeight = 0.0f;

		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
	};
}