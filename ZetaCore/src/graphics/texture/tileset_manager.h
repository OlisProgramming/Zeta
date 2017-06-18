#pragma once

#include <unordered_map>
#include "texture.h"

namespace zeta {
	namespace graphics {

		class TilesetManager {

		private:
			std::unordered_map<std::string, Texture*> m_tilesets;
			
		public:
			static TilesetManager* inst;

			TilesetManager();
			~TilesetManager();
			Texture* get(const std::string& name);
		};
	}
}