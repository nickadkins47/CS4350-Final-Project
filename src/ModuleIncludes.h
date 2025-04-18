
#pragma once

//Broke Down ModuleGLView into several smaller files
//This: All of the include statements thrown into a single file

#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"

//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"
#include "MGLIndexedGeometry.h"
#include "IndexedGeometrySphereTriStrip.h"
#include "WOAxesTubes.h"
#include "AftrTimer.h"
#include <chrono>

#include "GLView.h"
#include "AftrImGui_MenuBar.h"
#include "AftrImGui_WO_Editor.h"
#include "OrbitGui.h"

#include "AftrUtilities.h"
#include "NetMessengerClient.h"
#include "NetMessengerServer.h"

#include "MyKeyboard.h" //My custom class for handling keyboard input
#include "MyCam.h" //My custom header for camera controls
#include "MyGUIs.h" //My GUIs I made
#include "MyAudio.h" //Audio manager
#include "MyNetMsg_Pose.h" //Custom NetMsg for Sending Poses
#include "MyNetMsg_RVec.h" //Custom NetMsg for Sending Random Vectors

using std::string;
template<typename T> using svector = std::vector<T>;
template<typename T> using sptr = std::shared_ptr<T>;