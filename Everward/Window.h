#pragma once
#include <windows.h>

// Handle to the current window (requires createWindow to be called)
extern HWND hWnd;

// The size of the current window in pixels
extern int wndWidth, wndHeight;

// Creates a new window
void createWindow(HINSTANCE hInstance, WNDPROC WindowProc, int nCmdShow);