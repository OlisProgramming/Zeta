#pragma once

#include <vector>
#include "behaviour.h"

namespace zeta {
	namespace entity {

		class Entity {

		private:
			std::vector<Behaviour*> m_behaviours;

		public:
			Entity() {}
			inline void addBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
		};
	}
}