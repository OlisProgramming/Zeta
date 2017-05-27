#include "fileutils.h"

namespace zeta {
	namespace util {
		
		std::string readFileText(const char* path) {
			FILE* file = fopen(path, "rt");  // faster than fstream
			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			char* data = new char[size + 1];
			memset(data, 0, size + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, size, file);
			fclose(file);

			std::string output(data);
			delete[] data;
			return output;
		}
	}
}
