#include "../../include/nikaide.h"

Editor::Editor() : cursorLine(0), cursorColumn(0) {
	lines.push_back("");
};

void Editor::Draw(HDC hdc) {
	HFONT codeFont = CreateFontW(24, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cascadia Code"));

    HFONT oldFont = (HFONT)SelectObject(hdc, codeFont);

	for (int i = 0; i < lines.size(); i++) {
		TextOutA(hdc, 36, 40 + i * 24, lines[i].c_str(), lines[i].length());
	}

	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
}

void Editor::HandleCharacter(char character)
{
	lines[cursorLine].insert(cursorColumn,1, character);
	std::cout << lines.size();
	cursorColumn++;
}

void Editor::HandleBackspace() {

	if (!lines[cursorLine].empty()) // if line is not empty
	{
		lines[cursorLine].erase(cursorColumn - 1, 1); // remove character

		cursorColumn--;
	}
	else {
		if (cursorLine > 0) { // if line is empty but there is other lines
			lines.erase(lines.begin() + cursorLine);
			cursorLine -= 1; // go to previous line
			cursorColumn = lines[cursorLine].length(); // set cursorColumn to at the end
		}
	}
	
}

void Editor::HandleEnter()
{
	std::string newLine = lines[cursorLine].substr(cursorColumn);

	lines[cursorLine].erase(cursorColumn);

	lines.insert(
		lines.begin() + cursorLine + 1,
		newLine
	);

	cursorLine++;
	cursorColumn = 0;
}

void Editor::HandleInput(WPARAM wParam) {
	switch (wParam) {
	case '\r':
		HandleEnter();
		break;

	case '\b':
		HandleBackspace();
		break;

	default:
		HandleCharacter(wParam);
		break;

	}
}