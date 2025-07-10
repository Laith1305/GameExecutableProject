#include "eTime.h"



namespace viper {

	void viper::Time::Tick() {


		clock::time_point now = clock::now();
		m_time = std::chrono::duration<float>(now - m_StartTime).count();
		m_deltaTime = std::chrono::duration<float>(now - m_FrameTime).count();
		m_FrameTime = now;
	}
}