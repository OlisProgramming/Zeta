#pragma once

#include "../graphics/renderer/renderer.h"

// Convenience imports that custom behaviours will need (to save re-importing)
#include "../input/input_interface.h"
#include "../sound/sound_manager.h"

namespace zeta {
	namespace entity {

		class Behaviour {

		public:
			// Do minimal work in constructor, as it is not certain all level objects are there.
			Behaviour() {}

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
			virtual void  preRender(graphics::Renderer& renderer) {}
			virtual void     Render(graphics::Renderer& renderer) {}
			virtual void postRender(graphics::Renderer& renderer) {}
		};
	}
}