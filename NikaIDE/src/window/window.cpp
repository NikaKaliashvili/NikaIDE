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
	if (CreateWindowExA(0, "CLASS_NIKAIDE", windowTitle.c_str(), WS_VISIBLE | WS_OVERLAPPEDWINDOW, x, y, w, h, 0, 0, 0, 0) == 0) {
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
