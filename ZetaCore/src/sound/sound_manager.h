#pragma once

#include <vector>
#include <unordered_set>
#include "sound.h"

namespace zeta {
	namespace sound {

		class SoundManager {
			friend class Sound;

		private:
			std::vector<Sound*> m_sounds;
			std::unordered_set<SoundHandle*> m_automaticallyDeletedHandles;
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

			// Automatically delete this sound handle when it is finished playing.
			// DO NOT delete a handle yourself after it has been given here!
			inline void autoDelete(SoundHandle* handle) { m_automaticallyDeletedHandles.emplace(handle); }
		};
	}
}