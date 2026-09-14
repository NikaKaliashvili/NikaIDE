#pragma once

#include "../nikaide.h"

class Editor {
public:

	Editor();

	std::vector<std::string> lines;

	size_t cursorLine, cursorColumn, scrollY;

	// Draws text to the screen
	void Draw(HDC hdc);

	void DrawLines(HDC hdc);

	void DrawPointer(HDC hdc);

	// Handles typing/enter/backspace and etc...
	void HandleInput(WPARAM wParam);

	// Handles typing
	void HandleCharacter(char character);
	
	// Handles when backspace is pressed
	void HandleBackspace();
	
	// Handles when enter is pressed
	void HandleEnter();

	// Scroll up
	void ScrollUp();

	// Scroll down
	void ScrollDown();

	// Moves cursor left
	void HandlePointer(char Dir);
};