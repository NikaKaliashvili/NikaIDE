#pragma once

#define LogInfo(message) NikaIDE::Logger::Info(message)
#define LogWarning(message) NikaIDE::Logger::Warning(message)
#define LogError(message) NikaIDE::Logger::Error(message)

#include <Windows.h>
#include <iostream>
#include <string>

#include "../include/window/window.h"
#include "../include/logger/logger.h"