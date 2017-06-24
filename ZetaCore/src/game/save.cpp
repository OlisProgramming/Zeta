#include "save.h"

namespace zeta {
	namespace game {

		SaveFile::SaveFile(const std::string& fname) :
			m_ini(fname, true) {
		}
	}
}