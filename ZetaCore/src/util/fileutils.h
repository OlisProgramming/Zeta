#pragma once

#include <string>

namespace zeta {
	namespace util {

		std::string readFileText(const char* path);
		// TODO readFileBin?

		bool fileExists(const std::string& path);
	}
}