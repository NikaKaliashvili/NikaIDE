#pragma once

#include "../nikaide.h"

// main window proc
LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// updates lines
void UpdateLines(HWND hwnd);