#pragma once

#include <deque>
#include "timer.h"

namespace zeta {
	namespace util {

		class FPSClock {

		private:
			Timer m_timer;
			std::deque<float> m_lastTimes;

		public:
			FPSClock();
			void tick();
			float getFPS();
		};
	}
}