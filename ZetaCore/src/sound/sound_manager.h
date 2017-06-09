#pragma once

#include <vector>
#include "sound.h"

namespace zeta {
	namespace sound {

		class SoundManager {
			friend class Sound;

		private:
			std::vector<Sound*> m_sounds;
			gau_Manager* m_gorillaManager;
			ga_Mixer* m_gorillaMixer;
		public:
			static SoundManager* inst;

		public:
			SoundManager();
			inline void add(const std::string& fname) { add(new Sound(fname)); }
			void add(Sound* sound);
			Sound* get(const std::string& fname);
			void update();
			void cleanup();
		};
	}
}