#pragma once

#include "../entity/entity.h"

namespace zeta {
	namespace level {

		using namespace entity;

		class Level {

		private:
			std::vector<Entity*> m_entities;

		public:
			// TODO add constructor that takes a const std::string& pointing to a (.TMX) Tiled map file.
			Level();
			~Level();

			inline void addEntity(Entity* ent) { m_entities.push_back(ent); }

			inline void init() {
				for (Entity* ent : m_entities) ent->preInit();
				for (Entity* ent : m_entities) ent->init();
				for (Entity* ent : m_entities) ent->postInit();
			}

			inline void tick() {
				for (Entity* ent : m_entities) ent->preTick();
				for (Entity* ent : m_entities) ent->tick();
				for (Entity* ent : m_entities) ent->postTick();
			}
			
			inline void render(graphics::Renderer& renderer) {
				for (Entity* ent : m_entities) ent->preRender(renderer);
				for (Entity* ent : m_entities) ent->render(renderer);
				for (Entity* ent : m_entities) ent->postRender(renderer);
			}
		};
	}
}