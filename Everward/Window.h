#pragma once
#include <Windows.h>
#include "Vector2.h"

#define WND_WIDTH 800
#define WND_HEIGHT 600

// Handle to the current window (requires createWindow to be called)
extern HWND hWnd;

// The size of the current window client area in pixels
extern int wndWidth, wndHeight;

// The current mouse position
extern short mouseX, mouseY;

// Creates a new window
void createWindow(HINSTANCE hInstance, WNDPROC WindowProc, int nCmdShow);

// Calculates current window client area
bool calculateWindowSize(void);