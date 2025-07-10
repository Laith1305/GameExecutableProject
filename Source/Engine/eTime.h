#pragma once
#include <chrono>



namespace viper {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			m_StartTime = clock::now();
			m_FrameTime = clock::now();

		}

		void Tick();
		void Reset() { m_StartTime = clock::now(); }

		float GetTime() const { return m_time; }
		float GetDeltaTime() const { return m_deltaTime; }

	private:
		float m_time = 0;
		float m_deltaTime = 0;


		clock::time_point m_StartTime;
		clock::time_point m_FrameTime;
	};
}