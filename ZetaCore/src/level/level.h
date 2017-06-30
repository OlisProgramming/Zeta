#pragma once

#include <unordered_set>
#include "../entity/entity.h"
#include "../entity/behaviours_builtin.h"
#include "../graphics/renderable/sprite.h"
#include "../physics/aabb.h"

namespace zeta {
	namespace level {
		
		struct TilesetData {
			graphics::Texture* tex;
			unsigned int tileWidth;
			unsigned int tileHeight;
			unsigned int rows;
			unsigned int columns;
			unsigned int firstgid;
		};

		class Level {

		private:
			std::unordered_set<entity::Entity*> m_entities;
			std::vector<graphics::Sprite> m_tiles;
			std::vector<TilesetData> m_tilesets;
			std::vector<entity::Entity*> m_toDelete;

		public:
			Level(const std::string& tmxFileName);
			~Level();

			inline const std::unordered_set<entity::Entity*>& getAllEntities() { return m_entities; }
			inline void addEntity(entity::Entity* ent) { m_entities.emplace(ent); }
			inline void deleteEntity(entity::Entity* ent) { m_toDelete.push_back(ent); }
			inline bool collideAll(const physics::PhysObject* obj) {
				if (obj == nullptr) return false;
				using namespace physics;
				for (entity::Entity* other : m_entities) {
					if (other->getPhysObj() == nullptr) continue;
					if (other->getPhysObj() == obj) continue;
					if (other->getPhysObj()->collide(*obj))
						return true;
				}
				return false;
			}
			inline bool collideAll(entity::Entity* ent) { return collideAll(ent->getPhysObj()); }

			inline bool collideAllSolid(const physics::PhysObject* obj) {
				if (obj == nullptr) return false;
				using namespace physics;
				for (entity::Entity* other : m_entities) {
					if (other->getPhysObj() == nullptr) continue;
					if (other->getPhysObj() == obj) continue;
					if (!other->isSolid()) continue;
					if (other->getPhysObj()->collide(*obj))
						return true;
				}
				return false;
			}
			inline bool collideAllSolid(entity::Entity* ent) { return collideAllSolid(ent->getPhysObj()); }

			inline void init() {
				for (entity::Entity* ent : m_entities) ent->preInit();
				for (entity::Entity* ent : m_entities) ent->init();
				for (entity::Entity* ent : m_entities) ent->postInit();
			}

			inline void tick() {
				for (entity::Entity* ent : m_entities) ent->preTick();
				for (entity::Entity* ent : m_entities) ent->tick();
				for (entity::Entity* ent : m_entities) ent->postTick();

				for (entity::Entity* ent : m_toDelete) {
					m_entities.erase(ent);
					ent->preDestroy();
					ent->destroy();
					ent->postDestroy();
					delete ent;
				}
				m_toDelete.clear();
			}
			
			inline void render(graphics::Renderer& renderer) {
				
				for (graphics::Sprite spr : m_tiles) renderer.submit(&spr);
				//printf("%d tiles\n", m_tiles.size());

				for (entity::Entity* ent : m_entities) ent->preRender(renderer);
				for (entity::Entity* ent : m_entities) ent->render(renderer);
				for (entity::Entity* ent : m_entities) ent->postRender(renderer);
			}
		};
	}
}