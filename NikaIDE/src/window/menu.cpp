#include "../../include/nikaide.h"

std::wstring currentFile = L"";

void AddMenu(HWND hwnd) {
	// create main menu
	HMENU hMenu = CreateMenu();

	// create 'File' popup
	HMENU hFileMenu = CreatePopupMenu();

	// append 'Open' to 'File'
	AppendMenuA(hFileMenu, MF_STRING, MENU_OPEN_ID, "&Open");

	// append 'Save' to 'File'
	AppendMenuA(hFileMenu, MF_STRING, MENU_SAVE_ID, "&Save");

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
		
		// if file selected
		if (GetOpenFileName(&ofn) == TRUE) {
			currentFile = ofn.lpstrFile;
			std::wcout << currentFile;

			std::ifstream file;

			file.open(currentFile, std::ios::in | std::ios::binary);

			if (file.is_open()) {
				std::string buff;
				file >> buff;
				SendDlgItemMessageA(hwnd, EDITOR_ID, WM_SETTEXT, 0, (LPARAM)buff.c_str());
				file.close();
			}
		}

		return;
	}

	// 'Save' clicked
	if (LOWORD(wParam) == MENU_SAVE_ID) {

		// If file is not choosen
		if (currentFile.empty()) {
			OPENFILENAME ofn;
			wchar_t szFile[265] = { 0 };

			// Initialize ofn
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
			ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";

			if (GetSaveFileName(&ofn) == TRUE) {
				std::ofstream newFile(ofn.lpstrFile);
				
				if (newFile.is_open()) {

					int length = SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXTLENGTH, 0,0);

					char* buff = new char[length+1];

					SendDlgItemMessageA(hwnd, EDITOR_ID , WM_GETTEXT, length+1, (LPARAM)buff);

					newFile << buff;

					delete[] buff;

					newFile.close();

					currentFile = ofn.lpstrFile;

					LogInfo("File saved succesfully!");
					return;
				}
				else {
					LogInfo("Failed to save the file!");
					return;
				}
			}
		}
		else { // if file is chose
			std::ofstream newFile(currentFile.data());

			int length = SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXTLENGTH, 0, 0);

			char* buff = new char[length + 1];

			SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXT, length + 1, (LPARAM)buff);

			newFile << buff;

			delete[] buff;

			newFile.close();

			LogInfo("File saved succesfully!");
		}
	}
}