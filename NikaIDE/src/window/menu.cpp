#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

std::string currentFile = "";

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
		
		OPENFILENAMEA ofn;
		char szFile[265] = { 0 };

		// Initialize ofn
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
		
		// if file selected
		if (GetOpenFileNameA(&ofn) == TRUE) {
			currentFile = ofn.lpstrFile;

			FILE* hFile = fopen(currentFile.c_str(), "rb");

			if (hFile != NULL) {
				// read file's size
				fseek(hFile, 0, SEEK_END);
				long fileSize = ftell(hFile);
				fseek(hFile, 0, SEEK_SET);

				std::string buffer(fileSize, '\0');

				fread(buffer.data(), 1, fileSize, hFile);


				SendDlgItemMessageA(hwnd, EDITOR_ID, WM_SETTEXT, 0, (LPARAM)buffer.c_str());
				UpdateLines(hwnd);
				fclose(hFile);
			}
		}

		return;
	}

	// 'Save' clicked
	if (LOWORD(wParam) == MENU_SAVE_ID) {

		// If file is not choosen
		if (currentFile.empty()) {
			OPENFILENAMEA ofn;
			char szFile[265] = { 0 };

			// Initialize ofn
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(OPENFILENAMEA);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";

			if (GetSaveFileNameA(&ofn) == TRUE) {

				FILE* hFile = fopen(ofn.lpstrFile, "w");
				
				if (hFile != NULL) {
					int length = SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXTLENGTH, 0,0);

					std::string buffer(length+1, '\n');

					SendDlgItemMessageA(hwnd, EDITOR_ID , WM_GETTEXT, length+1, (LPARAM)buffer.data());

					fwrite(buffer.data(), buffer.size(), 1, hFile);

					fclose(hFile);

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
		else { // if file is choosen
			FILE* hFile = fopen(currentFile.c_str(), "w");

			int length = SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXTLENGTH, 0, 0);

			std::string buffer(length + 1, '\n');

			SendDlgItemMessageA(hwnd, EDITOR_ID, WM_GETTEXT, length + 1, (LPARAM)buffer.data());

			fwrite(buffer.data(), buffer.size(), 1, hFile);

			fclose(hFile);

			LogInfo("File saved succesfully!");
		}
	}
}