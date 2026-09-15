#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MENU_OPEN_ID 10
#define MENU_SAVE_ID 11

#define EDITOR_ID 100
#define EDITOR_LINES_ID 101
#define EXPLORER_ID 200

#define LogInfo(message) NikaIDE::Logger::Info(message)
#define LogWarning(message) NikaIDE::Logger::Warning(message)
#define LogError(message) NikaIDE::Logger::Error(message)

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "../include/window/window.h"
#include "../include/window/menu.h"
#include "../include/logger/logger.h"
#include "../include/editor/editor.h"

inline extern RECT windowSize = RECT{ 0 };
inline extern Editor editor = {};