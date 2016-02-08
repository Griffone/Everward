#include "Graphics.h"

#include <d3d9.h>
#include <d3dx9.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d = NULL;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev = NULL;    // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 vb = NULL;	// the pointer to the vertex buffer
LPDIRECT3DTEXTURE9 tx = NULL;	// the pointer to the texture

struct CUSTOMVERTEX {
	FLOAT x, y, z;
	FLOAT tu, tv;
};

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_TEX1)

float viewWidth = 3.0f;

bool initD3D() {
	// creating the d3d interface
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D


								   // create a device class using this information and the info from the d3dpp stuct
	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev))) {
		return false;
	}

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // enable transparency

	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	return true;
}

void load_geometry(void) {
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] = {
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
	};

	// there is a D3DXCreateTextureFromFile() function that only needs 3 parameters, but it read the texture with wrong format
	D3DXCreateTextureFromFileEx(d3ddev, "..\\Sprites\\base.png", D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tx);

	// create a vertex buffer interface called vb
	d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);

	VOID* pVoid;    // a void pointer

					// lock v_buffer and load the vertices into it
	vb->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vb->Unlock();
}

void render_frame(void) {
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 162, 232), 1.0f, 0);	// use 0, 162, 232 for nice blue color

	d3ddev->BeginScene();    // begins the 3D scene

							 // select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	// SET UP THE PIPELINE

	D3DXMATRIX matRotateZ;    // a matrix to store the rotation information

							  // build a matrix to rotate the model based on the increasing float value
	D3DXMatrixRotationZ(&matRotateZ, 0);

	// tell Direct3D about our matrix
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateZ);

	D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtRH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 5.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixOrthoRH(&matProjection,
		viewWidth,	// the horizontal view volume
		viewWidth * (FLOAT)wndHeight / (FLOAT)wndWidth,	// the vertical view volume
		0.25f,    // the near view-plane
		15.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	d3ddev->SetTexture(0, tx);

	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, vb, 0, sizeof(CUSTOMVERTEX));

	// copy the vertex buffer to the back buffer
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

// this is the function that cleans up Direct3D and COM
void cleanD3D(void) {
	if (d3ddev != NULL) {
		d3ddev->Release();
	}
	if (d3ddev != NULL) {
		d3d->Release();
	}
}