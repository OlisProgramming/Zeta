#include "sprite.h"

namespace zeta {
	namespace graphics {

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, bool isTranslucent) :
			Renderable(pos, size) {
			m_isTranslucent = isTranslucent;
		}

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, Texture* tex, glm::vec2 uvStart, glm::vec2 uvEnd, bool isTranslucent) :
			Renderable(pos, size) {
			m_tex = tex;
			m_uvStart = uvStart;
			m_uvEnd = uvEnd;
			m_isTranslucent = isTranslucent;
		}

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, const std::string& texture, bool isTranslucent) :
			Renderable(pos, size) {
			const TextureData& dat = TextureManager::inst->getTextureData(texture);
			m_tex = TextureManager::inst->getPage(dat.page);
			m_uvStart = dat.uvStart;
			m_uvEnd = dat.uvEnd;
			m_isTranslucent = isTranslucent;
		}
	}
}