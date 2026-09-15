#include "../../../include/window/wmCommands.h"

LRESULT HandleMouseWheel(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	int delta = GET_WHEEL_DELTA_WPARAM(wParam);

	if (delta < 0)
	{
		editor.ScrollDown();
	}
	else if (delta > 0)
	{
		editor.ScrollUp();
	}

	InvalidateRect(hwnd, nullptr, TRUE);

	return 0;
}