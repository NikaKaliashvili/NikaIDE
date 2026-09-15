#include "../../../include/window/wmCommands.h"

LRESULT HandlePaint(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hwnd, &ps);

	editor.Draw(hdc);

	// paint

	EndPaint(hwnd, &ps);
	return 0;
}