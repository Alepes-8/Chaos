#pragma once
#include <SDL.h>

namespace GameEngine
{
	class Timer {
	private:
		static Timer* m_Instance;

		unsigned int m_StartTicks;
		unsigned int m_ElipsedTime;

		float m_DelataTime;
		float m_TimeScale;

	public:

		void setTimeScale(float t);
		float getTimesScale();
		float getDeltaTime();

		static Timer* CreateInstance();
		static void Terminate();

		void Reset();
		void Update();

	private:
		Timer();
		~Timer();
	};
}