
#pragma once

#include "AftrConfig.h"
#ifdef  AFTR_CONFIG_USE_IMGUI

#include "Vector.h"
#include "Mat4.h"
#include <functional>
#include <chrono>

namespace Aftr
{

   class WO;

class OrbitGui
{
public:
   //main draw method called from GLView
   void draw();
   //Given an origin, this returns a radial orbit in the XY plan specified by the
   //origin orientation and position. Each revolution takes the specified time.
   Mat4 compute_pose( Mat4 const& origin_pose );
private:
   //draws the gui widgets that let the user manipulate orbit parameters
   void draw_orbit_controls();

   float radius_m = 100.0f;   //adjusted by gui slider
   bool isPaused = false;     //adjusted by gui button in draw_orbit_controls
   int orbitTime_msec = 5000; //adjusted by gui slider in draw_orbit_controls
   std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now(); //used by draw_orbit_controls
   std::chrono::system_clock::time_point pause_time; //used by draw_orbit_controls
   std::chrono::system_clock::time_point now_time;   //used by compute_pose()
};

}

#endif //  AFTR_CONFIG_USE_IMGUI
