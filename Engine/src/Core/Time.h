#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Cobalt
{
	class Time
	{
	public:
		static float deltaTime;

		static float currentFrameRate;
		static float intervalFrameRate;

		static void SetTimeBetweenInterval(float time);

	private:
		static void Update();

	private:
		static float m_Time;
		static float m_LastFrameTime;

		static float m_IntervalCounter;
		static float m_TimeBetweenInterval;

		friend class Application;
	};
}