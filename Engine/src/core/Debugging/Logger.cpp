#include "Logger.h"
#include <sstream>

namespace Arcana {

	std::queue<std::string> Logger::logs = {};

	void Logger::Log(const std::string& message)
	{
		std::stringstream __message;

		__message << "Log: " << std::endl
			<< ">>\t" << message << std::endl;

		logs.emplace(__message.str());
	}

	void Logger::Flush()
	{
		while (!logs.empty()) {
			auto log = logs.front();
			OutputDebugStringA(log.c_str());
			logs.pop();
		}
	}

}
