#pragma once

#include "../nikaide.h"

namespace NikaIDE {
	// Initializes main window
	void InitWindow(std::string windowTitle, int x, int y, int w, int h);
	void PollEvents();
}