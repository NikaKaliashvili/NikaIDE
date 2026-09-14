#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

static Editor editor;

static void CreateChildren(HWND hwnd) {
	// Explorer
	//CreateWindowExA(0, "SysTreeView32", 0, WS_VISIBLE | WS_CHILD, 5, 50, 180, 400, hwnd, (HMENU)EXPLORER_ID, 0, 0);

}

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_CREATE: {
		//GetClientRect(hwnd,&windowSize);
		CreateChildren(hwnd);
		AddMenu(hwnd);
		break;
	}

	case WM_PAINT: {
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hwnd, &ps);

		editor.Draw(hdc);

		// paint

		EndPaint(hwnd, &ps);
		break;
	}

	case WM_SIZE: {
		GetClientRect(hwnd, &windowSize);
		InvalidateRect(hwnd,nullptr,TRUE);
		break;
	}

	case WM_KEYDOWN: {
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
		}

		return 0;
	}

	case WM_CHAR: {
		editor.HandleInput(wParam);
		InvalidateRect(hwnd,nullptr,TRUE);

		return 0;
	}

	case WM_MOUSEWHEEL: {
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

		std::cout << delta;
	}

	case WM_COMMAND: {
		// handles menu buttons clicked in menu.cpp
		HandleMenu(wParam, hwnd);
		break;
	}

	// exit properly
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
