// basic headers
#include "Graphics.h"

// the WindowProc function declaration
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// set up and show a Window
	createWindow(hInstance, WindowProc, nCmdShow);

	// set up and initialize Direct3D
	initD3D();

	// loads graphics
	load_geometry();

	// the main loop:
	MSG msg;

	while (TRUE) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		render_frame();
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}