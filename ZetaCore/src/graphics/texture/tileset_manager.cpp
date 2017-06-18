#include "tileset_manager.h"

namespace zeta {
	namespace graphics {

		TilesetManager* TilesetManager::inst;
		
		TilesetManager::TilesetManager() {
			inst = this;
		}

		TilesetManager::~TilesetManager() {
			for (auto& pair : m_tilesets)
				delete pair.second;
		}

		Texture* TilesetManager::get(const std::string& name) {
			auto it = m_tilesets.find(name);
			if (it == m_tilesets.end()) {
				Texture* t = new Texture(name);
				m_tilesets.emplace(name, t);
				return t;
			}
			return it->second;
		}
	}
}