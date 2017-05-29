#pragma once

#include <Windows.h>

namespace zeta {
	namespace util {

		class Timer {

		private:
			LARGE_INTEGER m_start;
			LARGE_INTEGER m_frequency;

		public:
			Timer();
			void reset();
			float elapsed();
		};
	}
}