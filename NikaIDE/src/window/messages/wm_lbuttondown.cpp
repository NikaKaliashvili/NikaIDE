#include "../../../include/window/wmCommands.h"

#include "../../../include/nikaide.h"

// WM_DESTROY
LRESULT HandleLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	//std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;

	if (mouseX > 50) {
		int currentLine = editor.scrollY + (mouseY - 40) / 24;
		int currentColumn = ((mouseX - 34) / 11) - 2;

		if (editor.lines.size() > currentLine) {
			editor.cursorLine = currentLine;

			if (currentColumn < editor.lines[currentLine].length()) {
				editor.cursorColumn = currentColumn;
			}
			else {
				editor.cursorColumn = editor.lines[currentLine].length();
			}

			InvalidateRect(hwnd,0,TRUE);
		}

	}

	return 0;
}