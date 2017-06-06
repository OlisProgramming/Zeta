#pragma once

#include <chrono>

namespace zeta {
	namespace util {

		class Timer {

		private:
			typedef std::chrono::high_resolution_clock hrclock;
			std::chrono::time_point<hrclock> m_start;

		public:
			Timer();
			void reset();
			float elapsed();
		};
	}
}