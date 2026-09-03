#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
