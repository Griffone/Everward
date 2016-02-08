#include "Window.h"

bool created = false;

HWND hWnd;

int wndWidth = 800;
int wndHeight = 600;

int mouseX = 0;
int mouseY = 0;

void createWindow(HINSTANCE hInstance, WNDPROC WindowProc, int nCmdShow) {
	if (!created) {
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "BasicWindow";

		RegisterClassEx(&wc);

		wndWidth = 800;
		wndHeight = 600;

		hWnd = CreateWindowEx(NULL,
			"BasicWindow",
			"Everward",
			WS_OVERLAPPEDWINDOW,
			300, 300,
			wndWidth, wndHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

		ShowWindow(hWnd, nCmdShow);

		// clean up the class memory
		UnregisterClass("BasicWindow", hInstance);
		created = true;
	}
}

float wndRatio(void) {
	return (float)wndHeight / (float)wndWidth;
}