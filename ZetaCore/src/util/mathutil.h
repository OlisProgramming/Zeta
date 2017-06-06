#pragma once

#define pi_f 3.14159265358979f
#define pi_d 3.14159265358979
#define pi pi_f

namespace zeta {
	namespace util {

		template<typename T> inline static T clamp(T value, T minimum, T maximum) { return min(max(value, minimum), maximum); }
		template<typename T> inline static T clamp01(T value) { return min(max(value, 0), 1); }
	}
}