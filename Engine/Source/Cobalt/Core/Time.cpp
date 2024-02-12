#include "cbpch.h"

#include "Cobalt/Core/Time.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	float Time::deltaTime = 0.0f;
	float Time::time = 0.0f;

	float Time::currentFrameRate = 0.0f;
	float Time::intervalFrameRate = 0.0f;

	float Time::m_Time = 0.0f;
	float Time::m_LastFrameTime = 0.0f;
	
	float Time::m_IntervalCounter = 0.0f;
	float Time::m_TimeBetweenInterval = 0.4f;


	void Time::Update()
	{
		m_Time = (float)glfwGetTime(); // TODO: Get this from PlatformUtils
		deltaTime = m_Time - m_LastFrameTime;
		m_LastFrameTime = m_Time;

		currentFrameRate = 1.0f / deltaTime;

		if (m_IntervalCounter < 0.0f)
		{
			intervalFrameRate = currentFrameRate;
			m_IntervalCounter = m_TimeBetweenInterval;
		}
		else
		{
			m_IntervalCounter -= deltaTime;
		}

		time = m_Time;
	}

	void Time::SetTimeBetweenInterval(float time)
	{
		m_TimeBetweenInterval = time;
	}
}