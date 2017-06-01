#pragma once

#include <vector>
#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		class Group2D : public Renderable2D {

		private:
			std::vector<Renderable2D*> m_renderables;
			glm::mat4 m_transformation;

		public:
			Group2D(glm::mat4 transformation);
			inline RenderableType getType() const override { return RenderableType::GROUP; }
			void submit(Renderable2D* renderable);
			inline std::vector<Renderable2D*>& getChildren() { return m_renderables; }
			inline glm::mat4& getMatrix() { return m_transformation; }
		};
	}
}