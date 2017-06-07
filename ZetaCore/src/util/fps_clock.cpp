#include "fps_clock.h"

namespace zeta {
	namespace util {

#define LAST_FPS_COUNT 60

		FPSClock::FPSClock() {
			for (unsigned int i = 0; i < LAST_FPS_COUNT; ++i)
				m_lastTimes.push_back(1.0f / (float)LAST_FPS_COUNT);  // 'Default' FPS is 60, giving a 'default' frame time of 0.016s
		}

		void FPSClock::tick() {
			m_lastTimes.pop_front();
			m_lastTimes.push_back(m_timer.elapsed());
			m_timer.reset();
		}

		float FPSClock::getFPS() {
			float sum = 0.0f;
			for (unsigned int i = 0; i < LAST_FPS_COUNT; ++i)
				sum += m_lastTimes[i];
			return (float)LAST_FPS_COUNT / sum;
		}
	}
}