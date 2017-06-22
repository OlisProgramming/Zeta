#include "save.h"

namespace zeta {
	namespace game {
		
		SaveFile* SaveFile::inst;
		
		SaveFile::SaveFile(const std::string& fname) :
			m_ini(fname, true) {
			inst = this;
		}
	}
}