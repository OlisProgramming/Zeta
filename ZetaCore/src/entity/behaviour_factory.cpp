#include "behaviour_factory.h"

#include "../util/strutils.h"

namespace zeta {
	namespace entity {

		BehaviourFactory* BehaviourFactory::inst;

		BehaviourFactory::BehaviourFactory() {
			inst = this;
		}

		void BehaviourFactory::add(const std::string& behaviourName, std::function<Behaviour*(Entity*, const std::vector<std::string>&)> generator) {
			m_generators.emplace(behaviourName, generator);
		}

		Behaviour* BehaviourFactory::generate(const std::string& behaviourName, Entity* parent, const std::string& params) {
			return m_generators[behaviourName](parent, util::split(params));
		}
	}
}