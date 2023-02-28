#include "cbpch.h"

#include "Cameras/Camera.h"

namespace Cobalt
{
	void Camera::SetProjectionType(ProjectionType type)
	{
		m_ProjectionType = type;
		RecalculateProjection();
	}
}