#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include "behaviour.h"

namespace zeta {
	namespace entity {

		class BehaviourFactory {

		public:
			static BehaviourFactory* inst;
		private:
			std::unordered_map<std::string, std::function<Behaviour*(Entity*, const std::vector<std::string>&)>> m_generators;

		public:
			BehaviourFactory();
			void add(const std::string& behaviourName, std::function<Behaviour*(Entity*, const std::vector<std::string>&)> generator);
			Behaviour* generate(const std::string& behaviourName, Entity* parent, const std::string& params);
		};

#define ZETA_BEHAVIOUR_REGISTER(className)	zeta::entity::BehaviourFactory::inst->add(#className, className::generate);
	}
}