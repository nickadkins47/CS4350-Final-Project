
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

   /* audioman.add2D("Duck", 
      LMM("sounds/DuckQuack.mp3"), 
      false, //playLooped
      true //startPaused
   ); */

   //Plan:
   //1: Instance A watches 12683 (after pressing Z)
   //2: Instance B watches 12684 (after pressing X)
   //3: Pressing 'C' on either will send gulfstream2's pose to the other instance
   //4: Pressing 'V' on either will spawn a Duck on the other instance

   //Set NetMsgClient to send on port 12683
   keyboard[SDLK_z].onKeyDown = [this](){
      if (client == nullptr) {
         client = NetMessengerClient::New("127.0.0.1","12683");
         fmt::println("Client set to send on port 12683");
      }
   };

   //Set NetMsgClient to send on port 12684
   keyboard[SDLK_x].onKeyDown = [this](){
      if (client == nullptr) {
         client = NetMessengerClient::New("127.0.0.1","12684");
         fmt::println("Client set to send on port 12684");
      }
   };

   //Send Message from this instance to the port
   //specified from whichever port is selected w/ Z or X
   //contents: Pose of gulfstream2
   keyboard[SDLK_c].onKeyDown = [this](){
      if (client == nullptr) return;
      MyNetMsg_Pose pose(gulfstream2->getPose());
      client->sendNetMsgSynchronousTCP(pose);
   };

   //Read Pose Message & move gulfstream2 to that pose
   subscribe_NetMsg_to_callback<MyNetMsg_Pose>([this](auto msg) {
      gulfstream2->setPose(msg->pose);
   });

   //Send Message from this instance to the port
   //specified from whichever port is selected w/ Z or X
   //contents: random position
   keyboard[SDLK_v].onKeyDown = [this](){
      if (client == nullptr) return;
      MyNetMsg_RVec vec;
      client->sendNetMsgSynchronousTCP(vec);
   };

   //Read Vec Message & create a WO at that Vec Position
   subscribe_NetMsg_to_callback<MyNetMsg_RVec>([this](auto msg) {
      //audioman.play("Duck");
      Aftr::WO* duck = WO::New(LMM("models/duck.dae"), Vector( 1.f, 1.f, 1.f ), MESH_SHADING_TYPE::mstAUTO );
      duck->setPosition( msg->vec );
      duck->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      /* duck->upon_async_model_loaded([&duck](){
         ModelMeshSkin& skin = duck->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         skin.setAmbient( aftrColor4f( 1.f, 1.f, 1.f, 1.0f ) ); //Color of object when it is not in any light
         skin.setDiffuse( aftrColor4f( .1f, .1f, .1f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.2f, 0.2f, 0.2f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      }); */
      duck->setLabel( "Duck" );
      worldLst->push_back( duck );
   });

   ManagerOpenGLState::GL_CLIPPING_PLANE( 1000.0 );
   ManagerOpenGLState::GL_NEAR_PLANE( 0.1f );
   ManagerOpenGLState::enableFrustumCulling( false );
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition( 15,15,10 );

   setSkyBox(SMM("images/skyboxes/early_morning+6.jpg"));

   {
      //Create a light
      const float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
      //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }

   { 
      //Create the infinite grass plane (the floor)
      WO* wo = WO::New(SMM("models/grassFloor400x400_pp.wrl"), Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      wo->upon_async_model_loaded([wo](){
         ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         grassSkin.getMultiTextureSet().at( 0 ).setTexRepeats( 5.0f );
         grassSkin.setAmbient( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Color of object when it is not in any light
         grassSkin.setDiffuse( aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object)
         grassSkin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         grassSkin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      });
      wo->setLabel( "Grass" );
      worldLst->push_back( wo );
   }

   {
      gulfstream = WO::New(SMM("models/Aircraft/Gulfstream3/G3.obj"), Vector( 1.0f, 1.0f, 1.0f ), MESH_SHADING_TYPE::mstAUTO );
      gulfstream->setPosition( Vector( 0, 0, 10 ) );
      gulfstream->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      gulfstream->upon_async_model_loaded([this](){
         ModelMeshSkin& skin = gulfstream->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         skin.setAmbient( aftrColor4f( 0.1f, 0.1f, 0.1f, 1.0f ) ); //Color of object when it is not in any light
         //skin.setDiffuse( aftrColor4f( .1f, .1f, .5f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      });
      gulfstream->setLabel( "Gulfstream GIII" );
      worldLst->push_back( gulfstream );
   }

   {
      gulfstream2 = WO::New(SMM("models/Aircraft/Gulfstream3/G3.obj"), Vector( 1.0f, 1.0f, 1.0f ), MESH_SHADING_TYPE::mstAUTO );
      gulfstream2->setPosition( Vector( 0, 0, 30 ) );
      gulfstream2->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      gulfstream2->upon_async_model_loaded([this](){
         ModelMeshSkin& skin = gulfstream2->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         skin.setAmbient( aftrColor4f( 0.1f, 0.1f, 0.1f, 1.0f ) ); //Color of object when it is not in any light
         skin.setDiffuse( aftrColor4f( .1f, .1f, .5f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      });
      gulfstream2->setLabel( "Gulfstream GIII" );
      worldLst->push_back( gulfstream2 );
   }

   obj_move_gui.obj = gulfstream2; //Object Movement GUI set to gulfstream2

   {
      //Make a sphere
      moon = WO::New();
      MGLIndexedGeometry* mglSphere = MGLIndexedGeometry::New( moon );
      IndexedGeometrySphereTriStrip* geoSphere = IndexedGeometrySphereTriStrip::New( 3.0f, 12, 12, true, true );
      mglSphere->setIndexedGeometry( geoSphere );
      moon->setModel( mglSphere );
      moon->setLabel( "Moon" );
      moon->setPosition( { 15,15,15 } );
      moon->renderOrderType = RENDER_ORDER_TYPE::roTRANSPARENT;
      worldLst->push_back( moon );

      //Place a texture on the sphere, now its a moon
      Tex tex = *ManagerTex::loadTexAsync(SMM("images/moonMap.jpg"));
      moon->getModel()->getSkin().getMultiTextureSet().at( 0 ) = tex;
      moon->setPosition( {15,2,10});

      //We always want some axes, too!
      WO* axes = WOAxesTubes::New( { 15.0f,15.0f,15.0f }, .2f );
      axes->setParentWorldObject( moon );
      axes->setPosition( moon->getPosition() ); //match parent position before locking
      axes->lockWRTparent(); //makes a joint that "welds" this child rigidly to parent
      moon->getChildren().push_back( axes );     
   }

/*    {
      spider = WO::New(LMM("models/spider.obj"), Vector( .5f, .5f, .5f ), MESH_SHADING_TYPE::mstAUTO );
      spider->setPosition( Vector( 150, 0, 10 ) );
      spider->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      spider->upon_async_model_loaded([this](){
         ModelMeshSkin& skin = spider->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         skin.setAmbient( aftrColor4f( 1.f, 1.f, 1.f, 1.0f ) ); //Color of object when it is not in any light
         //skin.setDiffuse( aftrColor4f( .1f, .1f, .1f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.2f, 0.2f, 0.2f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      });
      spider->setLabel( "Spider" );
      worldLst->push_back( spider );
   }

   {
      duck = WO::New(LMM("models/duck.dae"), Vector( 1.f, 1.f, 1.f ), MESH_SHADING_TYPE::mstAUTO );
      duck->setPosition( Vector( 70, 20, 10 ) );
      duck->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      duck->upon_async_model_loaded([this](){
         ModelMeshSkin& skin = duck->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
         skin.setAmbient( aftrColor4f( 1.f, 1.f, 1.f, 1.0f ) ); //Color of object when it is not in any light
         skin.setDiffuse( aftrColor4f( .1f, .1f, .1f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.2f, 0.2f, 0.2f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
      });
      duck->setLabel( "Duck" );
      worldLst->push_back( duck );
   }

   {
      cube = WO::New(LMM("models/RotatingCube.3DS"), Vector( .25f, .25f, .25f ), MESH_SHADING_TYPE::mstAUTO );
      cube->setPosition( Vector( 50, 0, 30 ) );
      cube->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      cube->upon_async_model_loaded([this](){
         ModelMeshSkin skin (*ManagerTex::loadTexAsync(LMM("images/drkwood2.jpg")));
         skin.setMeshShadingType(MESH_SHADING_TYPE::mstAUTO);
         skin.getMultiTextureSet().at(0).setTexRepeats(2.0f);
         skin.setAmbient( aftrColor4f( 1.f, 1.f, 1.f, 1.0f ) ); //Color of object when it is not in any light
         skin.setDiffuse( aftrColor4f( .1f, .1f, .1f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object) // Make it blue? Why not?
         skin.setSpecular( aftrColor4f( 0.2f, 0.2f, 0.2f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
         skin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
         cube->getModel()->getSkin() = std::move(skin);
      });
      cube->setLabel( "Cube" );
      worldLst->push_back( cube );
   } */

   {
      // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
      WayPointParametersBase params(this);
      params.frequency = 5000;
      params.useCamera = true;
      params.visible = true;
      WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
      wayPt->setPosition( Vector( 50, 0, 3 ) );
      worldLst->push_back( wayPt );
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
      auto show_moon_orbit_params   = [this]() { orbit_gui.draw(); };
      auto show_My_ObjMovement      = [this]() { obj_move_gui.draw(); };

      gui->subscribe_drawImGuiWidget([=,this](){
         //We defined the callbacks above, now hook them into the menu labels
         menu.attach( "Edit", "Show WO Editor", woEditFunc );
         menu.attach( "Demos", "Show Default ImGui Demo", showDemoWindow_ImGui );
         menu.attach( "Demos", "Show Default ImPlot Demo", showDemoWindow_ImGuiPlot );
         menu.attach( "Demos", "Show Aftr ImGui w/ Markdown & File Dialogs", showDemoWindow_AftrDemo );
         menu.attach( "Orbit Gui", "Show Orbit", show_moon_orbit_params );
         menu.attach( "Move Object", "Show Object Mover", show_My_ObjMovement );
         menu.draw(); //The menu.draw() is the entry point for your gui. It is called once per frame to draw the GUI.
      });
      worldLst->push_back( gui );
   }
}
 