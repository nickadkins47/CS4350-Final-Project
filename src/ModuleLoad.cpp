
//Broke Down ModuleGLView into several smaller files
//This: loadMap()

#include "ModuleHdr.h"
using namespace Aftr;

void Module::loadMap() {
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   camera.camPtr = &cam;
   camera.kbdPtr = &keyboard;
   audioman.mycamPtr = &camera;
   MyCube::worldLst = &worldLst;

   ManagerOpenGLState::GL_CLIPPING_PLANE(1000.0);
   ManagerOpenGLState::GL_NEAR_PLANE(0.1f);
   ManagerOpenGLState::enableFrustumCulling(false);
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping(false); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition(0,0,20);

   setSkyBox(SMM("images/skyboxes/early_morning+6.jpg"));

   {
      //Create a light
      const float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }

   {
      Tex test1 = *ManagerTex::loadTexAsync(LMM("images/test/test1.png"));
      Tex test2 = *ManagerTex::loadTexAsync(LMM("images/test/test2.png"));
      Tex test3 = *ManagerTex::loadTexAsync(LMM("images/test/test3.png"));
      Tex test4 = *ManagerTex::loadTexAsync(LMM("images/test/test4.png"));
      Tex test5 = *ManagerTex::loadTexAsync(LMM("images/test/test5.png"));
      Tex test6 = *ManagerTex::loadTexAsync(LMM("images/test/test6.png"));

      MyCube test_block({test1, test2, test3, test4, test5, test6});

      test_block.create({0,0,0});

      Tex grass_bottom = *ManagerTex::loadTexAsync(LMM("images/grass_bottom.png"));
      Tex grass_side   = *ManagerTex::loadTexAsync(LMM("images/grass_side.png"));
      Tex grass_top    = *ManagerTex::loadTexAsync(LMM("images/grass_top.png"));

      MyCube grass_block({grass_side, grass_side, grass_side, grass_side, grass_bottom, grass_top});

      for (float i = -100; i < 100; i += 10) {
         for (float j = -100; j < 100; j += 10) {
            grass_block.create({i,j,-20});
         }
      }
   }
   
   // Let's make a GUI. We create a WOImGui instance, and then use the strategy pattern to
   // submit/subscribe lambdas/std::functions/callbacks (~same thing) to draw our desired widgets.
   // We nestle the callbacks inside a menu to keep everything organized. The menu uses an on/off
   // toggle -- when on, that menu item's corresponding callback will be invoked each frame, when
   // off that callback is not invoked and therefore the corresponding window is not drawn.

   {
      gui = WOImGui::New( nullptr );
      gui->setLabel( "My Gui" );
      //callbacks -- When the user toggles the checkbox from the menu, call these callbacks:
      
      //This callback shows the WOEditor window. It will be visible when the user
      //selected Menu -> Edit -> Show WO Editor (as linked up below).
      auto woEditFunc = [this]() { 
         this->wo_editor.draw( this->getLastSelectionQuery(), *this->getWorldContainer(), this->getCamera_functor() ); 
      };

      //We will put these demo items under the "Demo" menu
      auto showDemoWindow_ImGui     = [this]() { ImGui::ShowDemoWindow(); };
      auto showDemoWindow_AftrDemo  = [this]() { WOImGui::draw_AftrImGui_Demo(gui); };
      auto showDemoWindow_ImGuiPlot = [this]() { ImPlot::ShowDemoWindow(); };
      //auto show_moon_orbit_params   = [this]() { orbit_gui.draw(); };
      //auto show_My_ObjMovement      = [this]() { obj_move_gui.draw(); };

      gui->subscribe_drawImGuiWidget([=,this](){
         //We defined the callbacks above, now hook them into the menu labels
         menu.attach( "Edit", "Show WO Editor", woEditFunc );
         menu.attach( "Demos", "Show Default ImGui Demo", showDemoWindow_ImGui );
         menu.attach( "Demos", "Show Default ImPlot Demo", showDemoWindow_ImGuiPlot );
         menu.attach( "Demos", "Show Aftr ImGui w/ Markdown & File Dialogs", showDemoWindow_AftrDemo );
         //menu.attach( "Orbit Gui", "Show Orbit", show_moon_orbit_params );
         //menu.attach( "Move Object", "Show Object Mover", show_My_ObjMovement );
         menu.draw(); //The menu.draw() is the entry point for your gui. It is called once per frame to draw the GUI.
      });
      worldLst->push_back( gui );
   }
}
 