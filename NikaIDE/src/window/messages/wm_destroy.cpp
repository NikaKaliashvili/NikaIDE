#include "../../../include/window/wmCommands.h"

LRESULT HandleDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	PostQuitMessage(0);
	return 0;
}