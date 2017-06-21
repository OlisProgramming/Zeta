#pragma once

#include "renderable.h"
#include "../font/font.h"

namespace zeta {
	namespace graphics {

		class Renderer;

		class Label : public Renderable {

		private:
			std::string m_string;
			std::string m_font;
			unsigned int m_fontSize;

		public:
			Label(std::string string, glm::vec3 pos, const std::string& font, unsigned int fontSize, bool isTranslucent);
			inline virtual RenderableType getType() const { return RenderableType::LABEL; }
			inline const std::string& getString() const { return m_string; }
			inline void setString(const std::string& str) { m_string = str; }
			
			// Centres the label horizontally by adjusting the pivot point.
			void centreHoriz(Font* fnt);

			// Centres the label horizontally by adjusting the pivot point.
			void centreHoriz(const std::string& fontFname, unsigned int size);
			
			// Centres the label horizontally by adjusting the pivot point. Uses Renderer's current font to determine width.
			void centreHoriz(Renderer& renderer);
		};
	}
}