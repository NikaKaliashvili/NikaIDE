#pragma once

#include "../nikaide.h"

class Editor {
public:

	Editor();

	std::vector<std::string> lines;

	size_t cursorLine, cursorColumn, scrollY;
	int tabSize = 5;

	// Draws text to the screen
	void Draw(HDC hdc);

	// Draws lines
	void DrawLines(HDC hdc);

	// Draws cursor of the editor
	void DrawPointer(HDC hdc);

	// Handles typing/enter/backspace and etc...
	void HandleInput(WPARAM wParam);

	// Handles typing
	void HandleCharacter(char character);
	
	// Handles when backspace is pressed
	void HandleBackspace();

	// Handles when delete is pressed
	void HandleDelete();

	// Handles when tab is pressed
	void HandleTab();
	
	// Handles when enter is pressed
	void HandleEnter();

	// Scroll up
	void ScrollUp();

	// Scroll down
	void ScrollDown();

	// Moves cursor left
	void HandlePointer(char Dir);

	// Moves cursor at the end of the word
	void HandlePointerCtrl(char Dir);
};