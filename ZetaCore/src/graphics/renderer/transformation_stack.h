#pragma once

#include <vector>
#include <glm\glm.hpp>

namespace zeta {
	namespace graphics {

		class TransformationStack {

		private:
			std::vector<glm::mat4> m_stack;

		public:
			TransformationStack();
			void push(glm::mat4 mat, bool doOverride);
			void pop();
			glm::mat4& getMatrix() { return m_stack.back(); }
		};
	}
}