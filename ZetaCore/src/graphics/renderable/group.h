#pragma once

#include <vector>
#include "renderable.h"

namespace zeta {
	namespace graphics {

		class Group : public Renderable {

		private:
			std::vector<Renderable*> m_renderables;
			glm::mat4 m_transformation;

		public:
			Group(glm::mat4 transformation);
			Group(glm::vec3 translation);
			~Group();
			inline RenderableType getType() const override { return RenderableType::GROUP; }
			void submit(Renderable* renderable);
			inline std::vector<Renderable*>& getChildren() { return m_renderables; }
			inline glm::mat4& getMatrix() { return m_transformation; }
		};
	}
}