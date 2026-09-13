#pragma once

#include "../nikaide.h"

class Editor {
public:

	Editor();

	std::vector<std::string> lines;

	size_t cursorLine, cursorColumn;

	// Draws text to the screen
	void Draw(HDC hdc);

	// Handles typing/enter/backspace and etc...
	void HandleInput(WPARAM wParam);

	// Handles typing
	void HandleCharacter(char character);
	
	// Handles when backspace is pressed
	void HandleBackspace();
	
	// Handles when enter is pressed
	void HandleEnter();
};