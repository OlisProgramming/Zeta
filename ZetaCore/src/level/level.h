#pragma once

#include <unordered_set>
#include "../entity/entity.h"
#include "../entity/behaviours_builtin.h"
#include "../graphics/renderable/sprite.h"
#include "../physics/aabb.h"

namespace zeta {
	namespace level {

		using namespace graphics;
		using namespace entity;
		
		struct TilesetData {
			Texture* tex;
			unsigned int tileWidth;
			unsigned int tileHeight;
			unsigned int rows;
			unsigned int columns;
			unsigned int firstgid;
		};

		class Level {

		private:
			std::unordered_set<Entity*> m_entities;
			std::vector<Sprite> m_tiles;
			std::vector<TilesetData> m_tilesets;

		public:
			Level(const std::string& tmxFileName);
			~Level();

			inline const std::unordered_set<Entity*>& getAllEntities() { return m_entities; }
			inline void addEntity(Entity* ent) { m_entities.emplace(ent); }
			inline void deleteEntity(Entity* ent) { m_entities.erase(ent); }
			inline bool collideAll(const physics::PhysObject* obj) {
				using namespace physics;
				for (Entity* other : m_entities) {
					if (other->getPhysObj() == nullptr) continue;
					if (other->getPhysObj() == obj) continue;
					if (other->getPhysObj()->collide(*obj))
						return true;
				}
				return false;
			}
			inline bool collideAll(Entity* ent) { return collideAll(ent->getPhysObj()); }

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
				
				for (Sprite spr : m_tiles) renderer.submit(&spr);
				//printf("%d tiles\n", m_tiles.size());

				for (Entity* ent : m_entities) ent->preRender(renderer);
				for (Entity* ent : m_entities) ent->render(renderer);
				for (Entity* ent : m_entities) ent->postRender(renderer);
			}
		};
	}
}