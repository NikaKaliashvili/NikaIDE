#pragma once

#include "../nikaide.h"

// WM_CREATE
LRESULT HandleCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_PAINT
LRESULT HandlePaint(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_SIZE
LRESULT HandleSize(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_KEYDOWN
LRESULT HandleKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_CHAR
LRESULT HandleChar(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_MOUSEWHEEL
LRESULT HandleMouseWheel(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_COMMAND
LRESULT HandleCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);

// WM_DESTROY
LRESULT HandleDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);