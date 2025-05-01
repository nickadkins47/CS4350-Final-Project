
#pragma once

//Broke Down ModuleGLView into several smaller files
//This: Mostly intact ModuleGLView.h header, minus the includes

#include "ModuleIncludes.h" //all includes moved here

namespace Aftr {
   class Camera;
   class WOImGui;

/**
   \class Module
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/
class Module : public GLView {
public:
   static Module* New( const svector<string>& outArgs );
   virtual ~Module();
   virtual void updateWorld() override; ///< Called once per frame
   virtual void loadMap() override; ///< Called once at startup to build this module's scene
   virtual void onResizeWindow( GLsizei width, GLsizei height ) override;
   virtual void onMouseDown( const SDL_MouseButtonEvent& e ) override;
   virtual void onMouseUp  ( const SDL_MouseButtonEvent& e ) override;
   virtual void onMouseMove( const SDL_MouseMotionEvent& e ) override;
   virtual void onKeyDown( const SDL_KeyboardEvent& key ) override;
   virtual void onKeyUp  ( const SDL_KeyboardEvent& key ) override;

protected:
   Module( const svector<string>& args );

   //Sets the SkyBox with the provided image path
   //NOTE: will keep adding new WOs every time its called, slows down everything a LOT
   void setSkyBox( string const& imgPath );

   //Check if wo2 is between wo1 & wo3 (via getNearestPointWhereLineIntersectsMe)
   bool WOIsBetweenTwoOthers(WO const *const wo1, WO *const wo2, WO const *const wo3);

   MyKeyboard keyboard;
   MyCam camera;
   MyAudioManager audioman;

   WOImGui* gui = nullptr;
   AftrImGui_MenuBar menu;
   AftrImGui_WO_Editor wo_editor;

   MyGrid grid; //Grid of Chunks, each of which is a 16x16x32 grid
   WORawQuads* rquads = nullptr; //test

};

} //namespace Aftr
