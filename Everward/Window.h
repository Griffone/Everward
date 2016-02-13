#pragma once
#include <Windows.h>

#define WND_WIDTH 800
#define WND_HEIGHT 600

// Handle to the current window (requires createWindow to be called)
extern HWND hWnd;

// The size of the current window client area in pixels
extern int wndWidth, wndHeight;

// The size of the current screen in pixels
extern int screenWidth, screenHeight;

// The current mouse position
extern short mouseX, mouseY;

// Creates a new window
void createWindow(HINSTANCE hInstance, WNDPROC WindowProc, int nCmdShow);

// Calculates current window client area
bool calculateWindowSize(void);