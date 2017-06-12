#pragma once

#include <string>
#include <gorilla\ga.h>
#include <gorilla\gau.h>

namespace zeta {
	namespace sound {

		class SoundManager;
		class SoundHandle;

		class Sound {
			friend class SoundManager;

		private:
			std::string m_fname;
			ga_Sound* m_gorillaSound;

		public:
			Sound(const std::string& fname);
			~Sound();
			inline const std::string& getFname() const { return m_fname; }

			SoundHandle* genHandle(bool loop = false);
		};

		class SoundHandle {
			friend class Sound;

		private:
			gc_int32 m_quit;
			bool m_loop;
			gau_SampleSourceLoop* m_loopsrc;
			ga_Handle* m_gorillaHandle;

			SoundHandle();

		public:
			inline void play() { ga_handle_play(m_gorillaHandle); }
			inline void stop() {
				if (m_gorillaHandle != nullptr) {
					if (!ga_handle_stopped(m_gorillaHandle)) {
						ga_handle_stop(m_gorillaHandle);
						ga_handle_destroy(m_gorillaHandle);
						m_gorillaHandle = nullptr;
					}
				}
			}
			inline bool stopped() { return (m_gorillaHandle == nullptr) || (ga_handle_finished(m_gorillaHandle)); }
			inline ~SoundHandle() {
				if (m_gorillaHandle != nullptr)
					ga_handle_destroy(m_gorillaHandle);
			}

			// Handle now automatically destroys itself on sound finish.
			// Do not destroy this handle manually after calling forget()!
			void forget();

			inline void playAndForget() {
				play();
				forget();
			}
		};
	}
}