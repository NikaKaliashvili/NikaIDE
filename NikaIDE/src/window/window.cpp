#include "../../include/nikaide.h"

// for main window proc
#include "../../include/window/wndProc.h"

// Registers main window class and initializes it
void NikaIDE::InitWindow(std::string windowTitle, int x, int y, int w, int h)
{
	// Register main class
	static WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpszClassName = "CLASS_NIKAIDE";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = CreateSolidBrush(RGB(47, 47, 47));
	if (RegisterClassExA(&wc) == NULL) {
		LogError("Class registration failed");
		return;
	}


	// Initialize window
	HWND hwnd = CreateWindowExA(0, "CLASS_NIKAIDE", windowTitle.c_str(), WS_VISIBLE | WS_OVERLAPPEDWINDOW, x, y, w, h, 0, 0, 0, 0);

	if (hwnd == 0) {
		LogError("Window creation failed");
		return;
	}

	// Initialize treeview
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TREEVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	// Initialize COM library
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// Build section

	languageBox = CreateWindowExA(0, "COMBOBOX", 0, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 8, 100, 75, hwnd, (HMENU)LANGUAGES_ID, 0, 0);
	CreateWindowExA(0, "Button", "Build", WS_CHILD | WS_VISIBLE | BS_FLAT, 255, 8, 50, 25, hwnd, (HMENU)BUILD_ID, 0, 0); // build
	CreateWindowExA(0, "Button", "Build + Run", WS_CHILD | WS_VISIBLE | BS_FLAT, 310, 8, 85, 25, hwnd, (HMENU)BUILD_RUN_ID, 0, 0); // build and run

	if (languageBox == 0) {
		LogError("Language creation failed");
		return;
	}
	else {
		SendMessageA(languageBox, CB_ADDSTRING, 0, (LPARAM)"Text");
		SendMessageA(languageBox, CB_ADDSTRING, 0, (LPARAM)"C++");
		SendMessageA(languageBox, CB_ADDSTRING, 0, (LPARAM)"C#");
		SendMessageA(languageBox, CB_SETCURSEL, 0, 0);
	}

	LogInfo("Window initialized!");
}

void NikaIDE::PollEvents()
{
	static MSG msg;
	while (GetMessageA(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}
