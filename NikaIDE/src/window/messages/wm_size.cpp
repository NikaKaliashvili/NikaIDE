#include "../../../include/window/wmCommands.h"

LRESULT HandleSize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	GetClientRect(hwnd, &windowSize);
	InvalidateRect(hwnd, nullptr, TRUE);
	return 0;
}