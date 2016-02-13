#pragma once
#include "Window.h"
#include "Vector2.h"

// Sets up and initializes Direct3D
bool initD3D();

// Loads 3d models into graphics RAM
void loadGeometry(void);

// Renders a single frame
void renderFrame(void);

// Closes Direct3D and releases memory
void cleanD3D(void);

// The width of the scene view in units
extern float viewWidth;

struct CUSTOMVERTEX;

// Translates given window coordinates into world coordinates
Vector2 worldCoord(int x, int y);