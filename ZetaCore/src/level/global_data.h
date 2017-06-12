#pragma once

namespace zeta {
	namespace level {

		struct GlobalData {

			static GlobalData* inst;

			// The total number of ticks since the game started.
			// Use in tick events, not render events.
			unsigned long totalTicks;
			// The total number of ticks since the level was instantiated.
			// Use in tick events, not render events.
			unsigned long levelTicks;

			// The total number of seconds since the game started.
			// Use in render events, not tick events.
			float totalTime;
			// The total number of seconds since the level was instantiated.
			// Use in render events, not tick events.
			float levelTime;
			// The total number of seconds between this frame and the last.
			// Use in render events, not tick events.
			float deltaTime;
		};
	}
}