#include "../../include/nikaide.h"

static std::string lineNumbers;

Editor::Editor() : cursorLine(0), cursorColumn(0), scrollY(0) {
	lines.push_back("");
};

void Editor::DrawPointer(HDC hdc)
{
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	int charWidth = tm.tmAveCharWidth;
	int lineHeight = tm.tmHeight;

	int x = 60 + cursorColumn * charWidth;
	int y = 40 + (cursorLine - scrollY) * lineHeight;

	MoveToEx(hdc, x, y, nullptr);
	LineTo(hdc, x, y + lineHeight);
}

void Editor::DrawLines(HDC hdc) {
	HFONT codeFont = CreateFontW(24, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cascadia Code"));
	HFONT oldFont = (HFONT)SelectObject(hdc, codeFont);

	for (int i = scrollY; i < lines.size(); i++) {
		lineNumbers += std::to_string(i + 1);
		lineNumbers += "\n";
		TextOutA(hdc, 5,40+(i-scrollY)*24,std::to_string(i+1).c_str(), 3);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(codeFont);
}

void Editor::Draw(HDC hdc) {

	// draw background frame
	Rectangle(hdc,3,38,windowSize.right-25,windowSize.bottom-25);

	// save current DC state
	int savedDC = SaveDC(hdc);

	// clip drawing to editor area
	IntersectClipRect(
		hdc,
		3,
		38,
		windowSize.right - 30,
		windowSize.bottom - 30
	);

	// draw text
	HFONT codeFont = CreateFontW(24, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Cascadia Code"));

    HFONT oldFont = (HFONT)SelectObject(hdc, codeFont);

	for (int i = scrollY; i < lines.size(); i++) {

		int screenY = 40 + (i - scrollY) * 24;

		TextOutA(hdc, 60, screenY, lines[i].c_str(), lines[i].length());
	}

	// draw cursor
	DrawPointer(hdc);

	// draw lines
	DrawLines(hdc);

	SelectObject(hdc, oldFont);
	DeleteObject(codeFont);


	// restore previous clipping state
	RestoreDC(hdc, savedDC);
}

void Editor::HandleCharacter(char character)
{
	lines[cursorLine].insert(cursorColumn,1, character);
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

void Editor::ScrollUp()
{
	if (scrollY > 0)
		scrollY -= 1;
}

void Editor::ScrollDown()
{
	if (scrollY < lines.size())
		scrollY += 1;
}

void Editor::HandlePointer(char Dir) {
	switch (Dir) {
	case 'L':
		if (cursorColumn > 0)
		{
			cursorColumn--;
		}
		else {
			if (cursorLine > 0) {
				cursorLine--;
				cursorColumn = lines[cursorLine].size();
			}
		}
		break;
	
	case 'R':
		if (cursorColumn < lines[cursorLine].size())
		{
			cursorColumn++;
		}
		else {
			if (cursorLine < lines.size()-1) {
				cursorLine++;
				cursorColumn = 0;
			}
		}
		break;

	case 'U':
		if (cursorLine > 0)
		{
			cursorLine--;
			if (lines[cursorLine].size() < cursorColumn) {
				cursorColumn = lines[cursorLine].size();
			}
		}
		break;

	case 'D':
		if (cursorLine < lines.size()-1)
		{
			cursorLine++;
			if (lines[cursorLine].size() < cursorColumn) {
				cursorColumn = lines[cursorLine].size();
			}
		}
		break;
	
	}
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