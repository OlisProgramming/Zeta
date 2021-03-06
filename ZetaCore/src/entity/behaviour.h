#pragma once

#include "../graphics/renderer/renderer.h"

// Convenience imports that custom behaviours will need (to save re-importing)
#include <vector>
#include "../input/input_interface.h"
#include "../sound/sound_manager.h"
#include "../util/strutils.h"

namespace zeta {
	namespace entity {

		class Entity;
		
		using namespace graphics;

		// All behaviours must create a static method called generate with the signature (Entity* parent, const std::vector<std::string>& params),
		// otherwise the BehaviourFactory will not recognise it.
		class Behaviour {

		protected:
			Entity* m_parent;

		public:
			// Do minimal work in constructor, as it is not certain all level objects are there.
			Behaviour(Entity* parent) : m_parent(parent) {}

			virtual ~Behaviour() {}

			// Automatically overriden by ZETA_BEHAVIOUR_CLASS_BODY.
			virtual std::string getClassName() = 0;

			// All initial level objects are defined to exist during these events.
			// Extra 'supplement' objects should be created during preInit,
			// so that every single object exists once init is called.
			virtual void  preInit() {}
			virtual void     init() {}
			virtual void postInit() {}

			// These functions are defined to be called at a rate of 60Hz.
			// ALL code (apart from draw calls) that needs to be repeated
			// every frame should be done here.
			virtual void  preTick() {}
			virtual void     tick() {}
			virtual void postTick() {}

			// These functions are defined to be called as fast as possible (could be above or below 60Hz).
			// ONLY DRAW code that needs to be repeated
			// every frame should be done here (the rest can go in tick())
			// The renderer is passed to these functions and is not stored globally
			// because otherwise init and tick could actually render things.
			virtual void  preRender(Renderer& renderer) {}
			virtual void     render(Renderer& renderer) {}
			virtual void postRender(Renderer& renderer) {}

			// Try to do as much game-editing work as possible here and not in destructor.
			// Put memory deallocation code in destructor.
			virtual void  preDestroy() {}
			virtual void     destroy() {}
			virtual void postDestroy() {}

			inline Entity* getParent() { return m_parent; }
		};

#define ZETA_BEHAVIOUR_CLASS_BODY(className) \
public: \
	static className* generate(zeta::entity::Entity* parent, const std::vector<std::string>& params); \
	inline std::string getClassName() override { return #className; }

	}
}