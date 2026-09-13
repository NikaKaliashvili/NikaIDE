#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

static Editor editor;
static std::string lineNumbers;

static void CreateChildren(HWND hwnd) {
	
	// lines
	HWND hLines = CreateWindowExA(0, "STATIC", 0, WS_VISIBLE | WS_CHILD, 5, 40, 30, 400, hwnd, (HMENU)EDITOR_LINES_ID, 0, 0); // editor lines
	HFONT codeFont = CreateFontW(24, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cascadia Code"));
	SendMessage(hLines, WM_SETFONT, (WPARAM)codeFont, TRUE);

	// Explorer
	//CreateWindowExA(0, "SysTreeView32", 0, WS_VISIBLE | WS_CHILD, 5, 50, 180, 400, hwnd, (HMENU)EXPLORER_ID, 0, 0);

}

void UpdateLines(HWND hwnd) {
	lineNumbers = "";

	for (int i = 0; i < editor.lines.size(); i++) {
		lineNumbers += std::to_string(i + 1);
		lineNumbers += "\n";
	}
	SendDlgItemMessageA(hwnd, EDITOR_LINES_ID, WM_SETTEXT, 0, (LPARAM)lineNumbers.c_str());
}



LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_CREATE: {
		CreateChildren(hwnd);
		AddMenu(hwnd);
		UpdateLines(hwnd);
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

	case WM_CHAR: {
		editor.HandleInput(wParam);
		
		UpdateLines(hwnd);
		InvalidateRect(hwnd,nullptr,TRUE);

		break;
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
