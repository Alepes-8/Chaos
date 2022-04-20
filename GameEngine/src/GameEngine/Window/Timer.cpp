#include "Timer.h"

namespace GameEngine
{
	GameEngine::Timer* GameEngine::Timer::m_Instance = NULL;

	GameEngine::Timer::Timer() {
		Reset();
		m_TimeScale = 1.0f;
	}

	GameEngine::Timer::~Timer() {}
	void GameEngine::Timer::setTimeScale(float time) { m_TimeScale = time; }
	float GameEngine::Timer::getTimesScale() { return m_TimeScale; }
	float GameEngine::Timer::getDeltaTime() {return m_DelataTime;}


	GameEngine::Timer* GameEngine::Timer::CreateInstance()
	{
		if (m_Instance == NULL) {m_Instance = new Timer();}
		return m_Instance;
	}

	void GameEngine::Timer::Terminate()
	{
		delete m_Instance;
		m_Instance = NULL;
	}

	void GameEngine::Timer::Reset()
	{
		m_StartTicks = SDL_GetTicks();	//It return the milisecounds since the library was initialized.
		m_ElipsedTime = 0;
		m_DelataTime = 0.0f;
	}

	void GameEngine::Timer::Update() {
		m_ElipsedTime = SDL_GetTicks() - m_StartTicks;	//time between the last reset and time right now
		m_DelataTime = m_ElipsedTime * 0.001f;	//convert m_ElipsedTime to a float
	}
}