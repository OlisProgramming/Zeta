#include "fileutils.h"

#include <fstream>

namespace zeta {
	namespace util {
		
		std::string readFileText(const char* path) {
			std::ifstream in(path, std::ios::in);
			if (in)
			{
				return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
			}
			throw(errno);

			/*FILE* file = fopen(path, "rt");  // faster than fstream
			if (!file) return "FILE NOT FOUND";
			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			char* data = new char[size + 1];
			memset(data, 0, size + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, size, file);
			fclose(file);

			std::string output(data);
			delete[] data;
			return output;*/
		}

		bool fileExists(const std::string& path) {
			if (FILE *file = fopen(path.c_str(), "r")) {
				fclose(file);
				return true;
			}
			else {
				return false;
			}
		}
	}
}
