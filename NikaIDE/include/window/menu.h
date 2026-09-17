#pragma once

#include "../nikaide.h"

// saves file
bool SaveFile(HWND hwnd, WPARAM wParam);

// adds main menu
void AddMainMenu(HWND hwnd);

// handles menu buttons functionality
void HandleMenu(WPARAM wParam, HWND hwnd);