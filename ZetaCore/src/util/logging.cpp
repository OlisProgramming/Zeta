#include "logging.h"

#include <stdio.h>

Logger* Logger::inst;

Logger::Logger() {
	inst = this;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	m_ofs.open("log_" + std::to_string(now->tm_year + 1900) + "_" + std::to_string(now->tm_mon) + "_" + std::to_string(now->tm_mday) + "_" + std::to_string(now->tm_hour) + "_" + std::to_string(now->tm_min) + "_" + std::to_string(now->tm_sec) + ".txt");
}

Logger::~Logger() {
	m_ofs.close();
}

void Logger::log(std::string msg) {
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	char time_str[9];
	sprintf(time_str, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
	m_ofs << "[" << time_str << "] " << msg << std::endl;
	puts(msg.c_str());
}
