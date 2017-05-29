#include "timer.h"

namespace zeta {
	namespace util {

		Timer::Timer() {
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_start);
		}

		void Timer::reset() {
			QueryPerformanceCounter(&m_start);
		}

		float Timer::elapsed() {
			LARGE_INTEGER end;
			QueryPerformanceCounter(&end);
			unsigned __int64 cycles = end.QuadPart - m_start.QuadPart;
			return (float)cycles / (float)m_frequency.QuadPart;
		}
	}
}