#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

static int lines = 1;
static std::string lineNumbers;

static void CreateChildren(HWND hwnd) {
	// Editor
	HWND hEdit = CreateWindowExA(0, "EDIT", 0, WS_VISIBLE | WS_CHILD | ES_MULTILINE, 35,40,535,400,hwnd,(HMENU)EDITOR_ID,0,0);
	HFONT codeFont = CreateFontW(24, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cascadia Code"));
	SendMessage(hEdit, WM_SETFONT, (WPARAM)codeFont, TRUE);

	HWND hLines = CreateWindowExA(0, "STATIC", 0, WS_VISIBLE | WS_CHILD, 5, 40, 30, 400, hwnd, (HMENU)EDITOR_LINES_ID, 0, 0); // editor lines
	SendMessage(hLines, WM_SETFONT, (WPARAM)codeFont, TRUE);


	// Explorer
	//CreateWindowExA(0, "SysTreeView32", 0, WS_VISIBLE | WS_CHILD, 5, 50, 180, 400, hwnd, (HMENU)EXPLORER_ID, 0, 0);

}

void UpdateLines(HWND hwnd) {
	lines = SendDlgItemMessageA(hwnd, EDITOR_ID, EM_GETLINECOUNT, 0, 0);

	lineNumbers = "";

	for (int i = 0; i < lines; i++) {
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

	case WM_COMMAND: {
		if (HIWORD(wParam) == EN_CHANGE) { // updates editor lines when editor is changed
			WORD controlId = LOWORD(wParam);

			if (controlId == EDITOR_ID) {
				UpdateLines(hwnd);
				break;
			}
		}

		// handles menu buttons clicked in menu.cpp
		HandleMenu(wParam, hwnd);

	}

	case WM_CTLCOLOREDIT:
	{
		HDC hdcEdit = (HDC)wParam;
		HWND hEditCtrl = (HWND)lParam;

		int ctrlId = GetDlgCtrlID(hEditCtrl);

		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
