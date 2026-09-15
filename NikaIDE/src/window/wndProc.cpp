#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

#include "../../include/window/wmCommands.h"

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_CREATE:
		return HandleCreate(hwnd, wParam, lParam);

	case WM_PAINT:
		return HandlePaint(hwnd, wParam, lParam);

	case WM_SIZE:
		return HandleSize(hwnd, wParam, lParam);

	case WM_KEYDOWN:
		return HandleKeyDown(hwnd, wParam, lParam);

	case WM_CHAR:
		return HandleChar(hwnd, wParam, lParam);

	case WM_MOUSEWHEEL:
		return HandleMouseWheel(hwnd, wParam, lParam);

	case WM_COMMAND:
		return HandleCommand(hwnd, wParam, lParam);

	case WM_DESTROY:
		return HandleDestroy(hwnd, wParam, lParam);

	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
