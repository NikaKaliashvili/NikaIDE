#include "../../../include/window/wmCommands.h"

LRESULT HandleChar(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	editor.HandleInput(wParam);
	InvalidateRect(hwnd, nullptr, TRUE);
	return 0;
}