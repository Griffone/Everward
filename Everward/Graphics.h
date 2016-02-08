#pragma once
#include "Window.h"

// Sets up and initializes Direct3D
bool initD3D();

// Loads 3d models into graphics RAM
void load_geometry(void);

// Renders a single frame
void render_frame(void);

// Closes Direct3D and releases memory
void cleanD3D(void);

// The width of the scene view in units
extern float viewWidth;

struct CUSTOMVERTEX;