
//Broke Down ModuleGLView into several smaller files
//This: loadMap()

#include "ModuleHdr.h"
using namespace Aftr;

void Module::loadMap() {
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   //Set static pointers
   MyCam::camPtr = &cam;
   MyCam::kbdPtr = &keyboard;
   //MyAudioManager::mycamPtr = &camera;
   MyChunk::worldLst = &worldLst;

   //Load cube textures
   load_CubeID_TXTs();

   ManagerOpenGLState::GL_CLIPPING_PLANE(1500.0);
   ManagerOpenGLState::GL_NEAR_PLANE(0.1f);
   ManagerOpenGLState::enableFrustumCulling(true);
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping(false); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition(0,0,200);

   setSkyBox(SMM("images/skyboxes/early_morning+6.jpg"));

   {
      //Create a light
      const float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight(aftrColor4f(ga, ga, ga, 1.0f));
      WOLight* light = WOLight::New();
      light->isDirectionalLight(true);
      light->setPosition(Vector(0, 0, 100));
      light->getModel()->setDisplayMatrix(Mat4::rotateIdentityMat({0, 1, 0}, 90.0f * Aftr::DEGtoRAD));
      light->setLabel("Light");
      worldLst->push_back(light);
   }

   MyChunk::seed = ManagerRandomNumber::getRandomUnsignedInt(
      0U, std::numeric_limits<unsigned int>::max()
   );

   {
      for (int cx = -10; cx < 10; cx++) {
         for (int cy = -10; cy < 10; cy++) {
            grid.load(cx,cy);
         }
      }
   }

   {
      gui = WOImGui::New(nullptr);
      gui->setLabel("My Gui");
      
      auto woEditFunc = [this]() { 
         this->wo_editor.draw( this->getLastSelectionQuery(), *this->getWorldContainer(), this->getCamera_functor() ); 
      };

      /* auto showDemoWindow_ImGui     = [this]() { ImGui::ShowDemoWindow(); };
      auto showDemoWindow_AftrDemo  = [this]() { WOImGui::draw_AftrImGui_Demo(gui); };
      auto showDemoWindow_ImGuiPlot = [this]() { ImPlot::ShowDemoWindow(); }; */

      gui->subscribe_drawImGuiWidget([=,this](){
         menu.attach( "Edit", "Show WO Editor", woEditFunc );
         /* menu.attach( "Demos", "Show Default ImGui Demo", showDemoWindow_ImGui );
         menu.attach( "Demos", "Show Default ImPlot Demo", showDemoWindow_ImGuiPlot );
         menu.attach( "Demos", "Show Aftr ImGui w/ Markdown & File Dialogs", showDemoWindow_AftrDemo ); */
         menu.draw();
      });
      worldLst->push_back( gui );
   }
}
 