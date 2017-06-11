#pragma once

#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		class Label : public Renderable2D {

		private:
			std::string m_string;

		public:
			Label(std::string string, glm::vec3 pos, bool isTranslucent);
			inline virtual RenderableType getType() const { return RenderableType::LABEL; }
			inline const std::string& getString() const { return m_string; }
			inline void setString(const std::string& str) { m_string = str; }
		};
	}
}