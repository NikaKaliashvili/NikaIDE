#include "../../../include/window/wmCommands.h"

LRESULT HandleKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	switch (wParam) {
	case VK_LEFT:
		editor.HandlePointer('L');
		InvalidateRect(hwnd, nullptr, TRUE);
		break;

	case VK_RIGHT:
		editor.HandlePointer('R');
		InvalidateRect(hwnd, nullptr, TRUE);
		break;

	case VK_UP:
		editor.HandlePointer('U');
		InvalidateRect(hwnd, nullptr, TRUE);
		break;

	case VK_DOWN:
		editor.HandlePointer('D');
		InvalidateRect(hwnd, nullptr, TRUE);
		break;

	case VK_DELETE:
		editor.HandleDelete();
		InvalidateRect(hwnd, nullptr, TRUE);
		break;
	}

	return 0;
}