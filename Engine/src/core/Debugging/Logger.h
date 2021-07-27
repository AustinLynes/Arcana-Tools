#pragma once

#include "pch.h"

namespace Arcana {

	class Logger
	{
	public:
		static void Log(const std::string& message);
	
		static void Flush();


	private:
		static std::queue<std::string> logs;

	};

	
}

