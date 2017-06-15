#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iterator>

namespace zeta {
	namespace util {

		static std::vector<std::string> split(const std::string& input) {
			std::istringstream buffer(input);
			std::vector<std::string> ret;

			std::copy(std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>(),
				std::back_inserter(ret));
			return ret;
		}

		static bool isTruthy(const std::string& input) {
			return (
				input == "1" ||
				input == "t" || input == "T" ||
				input == "y" || input == "Y" ||
				input == "true" || input == "True" || input == "TRUE" ||
				input == "yes" || input == "Yes" || input == "YES"
				);
		}

		static bool isFalsey(const std::string& input) {
			return (
				input == "0" ||
				input == "f" || input == "F" ||
				input == "n" || input == "N" ||
				input == "false" || input == "False" || input == "FALSE" ||
				input == "no" || input == "No" || input == "NO"
				);
		}
	}
}