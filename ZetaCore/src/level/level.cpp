#include "level.h"

namespace zeta {
	namespace level {

		Level::Level() {
		}

		Level::~Level() {
			for (Entity* ent : m_entities) {
				delete ent;
			}
		}
	}
}