#include "../../../include/window/wmCommands.h"

LRESULT HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	// handles menu buttons clicked in menu.cpp
	HandleMenu(wParam, hwnd);
	return 0;
}