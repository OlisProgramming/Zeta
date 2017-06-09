#include "sound_manager.h"

namespace zeta {
	namespace sound {

		SoundManager* SoundManager::inst;

		SoundManager::SoundManager() {
			inst = this;

			gc_initialize(0);
			m_gorillaManager = gau_manager_create();
			m_gorillaMixer = gau_manager_mixer(m_gorillaManager);
		}

		void SoundManager::add(Sound* sound) {
			m_sounds.push_back(sound);
		}

		Sound* SoundManager::get(const std::string& fname) {
			Sound* sound = nullptr;
			for (Sound* guess : m_sounds) {
				if (guess->getFname() == fname) {
					sound = guess;
					break;
				}
			}

			return sound;
		}

		void SoundManager::update() {
			gau_manager_update(m_gorillaManager);
		}

		void SoundManager::cleanup() {
			for (Sound* sound : m_sounds) {
				delete sound;
			}
		}
	}
}