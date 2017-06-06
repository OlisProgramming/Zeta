#include "timer.h"

namespace zeta {
	namespace util {

		Timer::Timer() {
			reset();
		}

		void Timer::reset() {
			m_start = hrclock::now();
		}

		float Timer::elapsed() {
			return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(hrclock::now() - m_start).count() / 1000.f;
		}
	}
}