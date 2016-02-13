#include "Window.h"

bool created = false;

HWND hWnd;

int wndWidth = WND_WIDTH;
int wndHeight = WND_HEIGHT;

short mouseX = 0;
short mouseY = 0;

void createWindow(HINSTANCE hInstance, WNDPROC WindowProc, int nCmdShow) {
	if (!created) {
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "BasicWindow";

		RegisterClassEx(&wc);

		hWnd = CreateWindowEx(NULL,
			"BasicWindow",
			"Everward",
			WS_TILEDWINDOW,
			(GetSystemMetrics(SM_CXSCREEN) - wndWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - wndHeight) / 2,
			wndWidth, wndHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

		ShowWindow(hWnd, nCmdShow);

		calculateWindowSize();

		// clean up the class memory
		UnregisterClass("BasicWindow", hInstance);
		created = true;
	}
}

bool calculateWindowSize(void) {
	RECT rect;
	if (GetClientRect(hWnd, &rect)) {
		wndWidth = rect.right - rect.left;
		wndHeight = rect.bottom - rect.top;
		return true;
	} else {
		return false;
	}
}