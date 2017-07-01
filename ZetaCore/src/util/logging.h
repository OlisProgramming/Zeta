#pragma once

#include <ctime>
#include <string>
#include <fstream>

#define ZLog(msg) Logger::inst->log((msg));

class Logger {

private:
	std::ofstream m_ofs;

public:
	static Logger* inst;
	Logger();
	~Logger();
	void log(std::string msg);
};