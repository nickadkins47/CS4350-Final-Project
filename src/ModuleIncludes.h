
#pragma once

//Broke Down ModuleGLView into several smaller files
//This: All of the include statements thrown into a single file

#include "AftrGLRendererBase.h"
#include "AftrImGui_MenuBar.h"
#include "AftrImGui_WO_Editor.h"
#include "AftrImGuiIncludes.h"
#include "AftrTimer.h"
#include "AftrUtilities.h"
#include "Axes.h"
#include "Camera.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "CameraChaseActorSmooth.h"
#include "CameraStandard.h"
#include "GLView.h"
#include "IndexedGeometryQuad.h"
#include "IndexedGeometryRectangularPrism.h"
#include "IndexedGeometrySphereTriStrip.h"
#include "ManagerOpenGLState.h"
#include "MGLIndexedGeometry.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "PhysicsEngineODE.h"
#include "WO.h"
#include "WOAxesTubes.h"
#include "WOCar1970sBeater.h"
#include "WOHumanCal3DPaladin.h"
#include "WOHumanCyborg.h"
#include "WOImGui.h"
#include "WOLight.h"
#include "WONVDynSphere.h"
#include "WONVPhysX.h"
#include "WONVStaticPlane.h"
#include "WOQuad.h"
#include "WOSkyBox.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOWayPointSpherical.h"
#include "WorldList.h"

#include "ThirdParty/PerlinNoise.h"

#include "My/StdIncludes.h" //Files imported from standard library
#include "My/Keyboard.h" //My custom class for handling keyboard input
#include "My/Cam.h" //My custom header for camera controls
#include "My/GUIs.h" //My GUIs I made
#include "My/Audio.h" //Audio manager
#include "My/CubeIDs.h" //Described types of Cubes & how to get their textures
#include "My/Grid.h" //Grid of Cubes, handles rendering them (for now)
