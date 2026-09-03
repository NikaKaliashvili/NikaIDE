#pragma once

#define LogInfo(message) NikaIDE::Logger::Info(message)
#define LogWarning(message) NikaIDE::Logger::Warning(message)
#define LogError(message) NikaIDE::Logger::Error(message)

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "../include/window/window.h"
#include "../include/logger/logger.h"