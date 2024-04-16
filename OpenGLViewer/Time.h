#pragma once
#include <GLFW/glfw3.h>
struct STime
{
	static int Init();
	static float GetDeltaTime() { return m_deltaTime; };
	static void Update();
	
private:
	static int m_fpsCount;
	static float m_totalTime;
	static float m_deltaTime;
	static float m_fpsTime;
	static double m_lastTimestamp;
};

