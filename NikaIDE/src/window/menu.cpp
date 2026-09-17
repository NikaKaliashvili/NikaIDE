#include "../../include/nikaide.h"

#include "../../include/window/wndProc.h"

void AddMainMenu(HWND hwnd) {
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

static void OpenFile(HWND hwnd, WPARAM wParam) {
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

				// initialize new lines
				std::vector<std::string> newLines;
				newLines.push_back("");

				int currentLine = 0;
				int currentColumn = 0;

				for (char letter : buffer) {

					switch (letter) {

					case '\n':
						continue;

					case '\t': // temporary spaces for tabulation
						for (int i = 0; i < 4; i++)
						{
							newLines[currentLine].insert(currentColumn, 1, ' ');
							currentColumn++;
						}
						break;

					case '\r':
						currentLine++;
						currentColumn = 0;
						newLines.push_back("");
						break;

					default:
						newLines[currentLine].insert(currentColumn, 1, letter);
						currentColumn++;
						break;
					}
				}

				editor.lines = newLines;
				editor.cursorLine = currentLine;
				editor.cursorColumn = newLines[currentLine].size();
				InvalidateRect(hwnd, NULL, true);

				fclose(hFile);
			}
		}

		return;
	}
}

bool SaveFile(HWND hwnd, WPARAM wParam) {
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

					std::string buffer;

					for (int i = 0; i < editor.lines.size(); i++) {
						buffer += editor.lines[i].c_str();

						if (i+1 < editor.lines.size())
							buffer += '\r';
					}

					fwrite(buffer.c_str(), buffer.length(), 1, hFile);

					fclose(hFile);

					currentFile = ofn.lpstrFile;

					LogInfo("File saved succesfully!");
					return 0;
				}
				else {
					LogInfo("Failed to save the file!");
					return 0;
				}
			}
		}
		else { // if file is choosen
			FILE* hFile = fopen(currentFile.c_str(), "w");

			std::string buffer;

			for (int i = 0; i < editor.lines.size(); i++) {
				buffer += editor.lines[i].c_str();

				if (i + 1 < editor.lines.size())
					buffer += '\r';
			}

			fwrite(buffer.c_str(), buffer.length(), 1, hFile);

			fclose(hFile);

			LogInfo("File saved succesfully!");
			return 1;
		}
	}
}

void HandleMenu(WPARAM wParam, HWND hwnd) {

	// 'Open' clicked
	OpenFile(hwnd, wParam);

	// 'Save' clicked
	SaveFile(hwnd, wParam);
}