#include "transformation_stack.h"

namespace zeta {
	namespace graphics {

		TransformationStack::TransformationStack() {
			m_stack.push_back(glm::mat4());
		}

		void TransformationStack::push(glm::mat4 mat, bool doOverride) {
			if (doOverride)
				m_stack.push_back(mat);
			else
				m_stack.push_back(mat * m_stack.back());
		}

		void TransformationStack::pop() {
			if (m_stack.size() > 1)
				m_stack.pop_back();
		}
	}
}