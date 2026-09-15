#include "../../../include/window/wmCommands.h"
#include "../../../include/window/menu.h"

LRESULT HandleCreate(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	AddMainMenu(hwnd);
	return 0;
}