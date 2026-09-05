#include "../../include/nikaide.h"


void AddMenu(HWND hwnd) {
	// create main menu
	HMENU hMenu = CreateMenu();

	// create 'File' popup
	HMENU hFileMenu = CreatePopupMenu();

	// append 'Open' to 'File'
	AppendMenuA(hFileMenu, MF_STRING, MENU_OPEN_ID, "&Open");

	// append 'File' to main menu
	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "&File");

	// set hMenu as main menu
	SetMenu(hwnd, hMenu);
}

void HandleMenu(WPARAM wParam, HWND hwnd) {

	// 'Open' clicked
	if (LOWORD(wParam) == MENU_OPEN_ID) {
		
		OPENFILENAME ofn;
		wchar_t szFile[265] = { 0 };

		// Initialize ofn
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
		ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
		// if file selected
		if (GetOpenFileName(&ofn) == TRUE) {
			std::wstring filePath = ofn.lpstrFile;

			std::ifstream file(filePath, std::ios::in | std::ios::binary);

			if (file.is_open()) {
				std::ostringstream ss;
				ss << file.rdbuf();
				SendDlgItemMessageA(hwnd, EDITOR_ID, WM_SETTEXT, 0, (LPARAM)ss.str().c_str());
				file.close();
			}
		}

		return;
	}
}