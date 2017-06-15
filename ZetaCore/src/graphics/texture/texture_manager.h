#pragma once

#include <unordered_map>
#include <glm\glm.hpp>
#include "texture.h"

namespace zeta {
	namespace graphics {

#ifndef ZETA_TEXTURE_MANAGER_SET_PIVOT_TO_ORIGIN
#define ZETA_TEXTURE_MANAGER_SET_PIVOT_TO_ORIGIN 1
#endif

		struct TextureData {
			unsigned int page;
			glm::vec2 uvStart;
			glm::vec2 uvEnd;
			glm::vec2 size;
			glm::vec2 pivot;
		};

		class TextureManager {

		private:
			std::vector<Texture*> m_pages;
			std::unordered_map<std::string, TextureData> m_textures;

		public:
			static TextureManager* inst;

		public:
			TextureManager();
			~TextureManager();
			inline const TextureData& getTextureData(const std::string& name) { return m_textures.at(name); }
			inline Texture* getPage(unsigned int page) const { return m_pages[page]; }
		private:
			void genPage(unsigned int page);
		};
	}
}