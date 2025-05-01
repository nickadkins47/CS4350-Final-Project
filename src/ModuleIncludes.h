
#pragma once

//Broke Down ModuleGLView into several smaller files
//This: All of the include statements thrown into a single file

#include "AftrGLRendererBase.h"
#include "AftrImGui_MenuBar.h"
#include "AftrImGui_WO_Editor.h"
#include "AftrUtilities.h"
#include "Axes.h"
#include "WOImGui.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WorldList.h"

#include "My/StdIncludes.h" //Files imported from standard library
#include "My/Keyboard.h" //My custom class for handling keyboard input
#include "My/Cam.h" //My custom header for camera controls
//#include "My/GUIs.h" //My GUIs I made
//#include "My/Audio.h" //Audio manager
#include "My/CubeIDs.h" //Described types of Cubes & how to get their textures
#include "My/Chunk.h" //16x16x32 chunk of cubes
#include "My/Grid.h" //32x32 grid of chunks
