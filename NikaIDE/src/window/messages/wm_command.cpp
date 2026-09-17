#include "../../../include/window/wmCommands.h"

#include "../../../include/window/menu.h"

static void HandleButtons(HWND hwnd, WPARAM wParam) {
    // after selecting language box, focus on hwnd
    if (LOWORD(wParam) == LANGUAGES_ID && HIWORD(wParam) == CBN_SELCHANGE)
    {
        SetFocus(hwnd);
        InvalidateRect(hwnd, 0, TRUE);
        return;
    }

    // build and focus
    if (LOWORD(wParam) == BUILD_ID && HIWORD(wParam) == BN_CLICKED)
    {
        int index = SendMessageA(languageBox, CB_GETCURSEL, 0, 0);

        if (index == 1 && !currentFile.empty()) { // c++
            if (SaveFile(hwnd, MENU_SAVE_ID)) {
                std::string buffer = "g++ " + currentFile + " -o nika_program";

                system(buffer.c_str());
            }
        }

        SetFocus(hwnd);
        InvalidateRect(hwnd, 0, TRUE);
        return;
    }

    // build, run and focus
    if (LOWORD(wParam) == BUILD_RUN_ID && HIWORD(wParam) == BN_CLICKED)
    {
        int index = SendMessageA(languageBox, CB_GETCURSEL, 0, 0);

        if (index == 1 && !currentFile.empty()) { // c++

            if (index == 1 && !currentFile.empty()) { // c++
                if (SaveFile(hwnd, MENU_SAVE_ID)) {
                    std::string buffer = "g++ " + currentFile + " -o nika_program";

                    system(buffer.c_str());
                    std::string fileCommand = currentFile;
                    size_t pos = fileCommand.find_last_of('\\');

                    if (pos != std::string::npos) {
                        fileCommand.replace(pos + 1, std::string::npos, "nika_program");
                    }

                    system(fileCommand.c_str());
                }
            }

            
        }

        SetFocus(hwnd);
        InvalidateRect(hwnd, 0, TRUE);
        return;
    }
}

LRESULT HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	// handles menu buttons clicked in menu.cpp
	HandleMenu(wParam, hwnd);
    
    HandleButtons(hwnd,wParam);

    
	return 0;
}