// basic headers
#include "Graphics.h"
#include <windowsx.h>

// the WindowProc function declaration
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// set up and show a Window
	createWindow(hInstance, WindowProc, nCmdShow);

	// set up and initialize Direct3D
	initD3D();

	// loads graphics
	loadGeometry();

	// the main loop:
	MSG msg;

	while (TRUE) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		renderFrame();
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
	case WM_MOUSEMOVE: {
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
		return 0;
	} break;
	case WM_MOUSEWHEEL: {
		float newViewWidth = viewWidth - GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		if (newViewWidth < 0.5f) {
			viewWidth = 0.5f;
		}
		else if (newViewWidth > 15.0f) {
			viewWidth = 15.0f;
		} else {
			viewWidth = newViewWidth;
		}
	} break;
	case WM_SIZE: {
		cleanD3D();
		int oldWidth = wndWidth;
		calculateWindowSize();
		viewWidth *= (float)wndWidth / (float)oldWidth;
		initD3D();
		loadGeometry();
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}