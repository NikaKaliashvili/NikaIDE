#include "../../include/nikaide.h"

void NikaIDE::Logger::Info(std::string message)
{ 
	std::cout << "\033[35m" << "[NikaIDE] " << "\033[0m"  << "\033[97m" << message.c_str() << "\033[0m" << std::endl;
}

void NikaIDE::Logger::Warning(std::string message)
{
	std::cout << "\033[35m" << "[NikaIDE] " << "\033[0m" << "\033[33m" << message.c_str() << "\033[0m" << std::endl;
}

void NikaIDE::Logger::Error(std::string message)
{
	std::cout << "\033[35m" << "[NikaIDE] " << "\033[0m" << "\033[31m" << message.c_str() << "\033[0m" << std::endl;
}
