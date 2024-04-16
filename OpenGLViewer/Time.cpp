#include "Time.h"

float STime::m_deltaTime{};
float STime::m_totalTime{};
int STime::m_fpsCount{};
float STime::m_fpsTime{};
double STime::m_lastTimestamp{};

int STime::Init()
{
	STime::m_lastTimestamp = glfwGetTime();
	return 0;
}

void STime::Update()
{
	double now{ glfwGetTime() };
	double diff = now - m_lastTimestamp;
	m_deltaTime = diff;
	m_totalTime += m_deltaTime;
	m_lastTimestamp = now;

	m_fpsCount++;
	m_fpsTime += m_deltaTime;
}
