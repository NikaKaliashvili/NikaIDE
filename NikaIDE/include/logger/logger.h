#pragma once

#include "../nikaide.h"

namespace NikaIDE {
	namespace Logger {

		// Logs information with current timestamp and blue color
		void Info(std::string message);
		// Logs warning with current timestamp and yellow color
		void Warning(std::string message);
		// Logs error with current timestamp and red color
		void Error(std::string message);

	}
}