#pragma once

#include <string>
#include <map>
#include <INI.h>

namespace zeta {
	namespace game {

		class SaveFile {

		public:
			static SaveFile* inst;
		private:
			INI<> m_ini;

		public:
			SaveFile(const std::string& fname);
			inline void save() { m_ini.save(); }
			inline void reload() { m_ini = INI<>(m_ini.filename, true); }

			inline std::string get(const std::string& section, const std::string& key, const std::string& defaultValue) { m_ini.select(section); return m_ini.get(key, defaultValue); }
			inline void set(const std::string& section, const std::string& key, const std::string& value) { m_ini.create(section); m_ini.set(key, value); }
			inline void reset() { m_ini.clear(); }
		};
	}
}