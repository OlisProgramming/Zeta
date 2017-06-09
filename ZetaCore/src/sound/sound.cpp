#include "sound.h"

#include "sound_manager.h"

namespace zeta {
	namespace sound {

		Sound::Sound(const std::string& fname) :
			m_fname(fname) {
			
			std::string qualifiedname = "../res/sounds/" + fname;
			m_gorillaSound = gau_load_sound_file(qualifiedname.c_str(), "ogg");
		}

		Sound::~Sound() {
			ga_sound_release(m_gorillaSound);
		}

		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context) {
			gc_int32* flag = (gc_int32*)in_context;
			*flag = 1;
			ga_handle_stop(in_handle);
		}

		SoundHandle* Sound::genHandle(bool loop) {

			SoundHandle* handle = new SoundHandle;
			handle->m_loop = loop;
			gau_SampleSourceLoop** pLoopSrc = &handle->m_loopsrc;
			if (!loop)
				pLoopSrc = 0;

			ga_Handle* gahandle = gau_create_handle_sound(SoundManager::inst->m_gorillaMixer, m_gorillaSound, &setFlagAndDestroyOnFinish, &handle->m_quit, pLoopSrc);

			handle->m_gorillaHandle = gahandle;
			return handle;
		}

		SoundHandle::SoundHandle() {
			m_quit = 0;
			m_loop = false;
			m_loopsrc = 0;
		}
	}
}