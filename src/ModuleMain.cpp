
//Broke Down ModuleGLView into several smaller files
//This: New() + most of the smaller functions

#include "ModuleHdr.h"
using namespace Aftr;

Module* Module::New( const svector<string>& args ) {
   Module* glv = new Module( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   
   //onCreate() moved/inlined here
   if( glv->pe != NULL ) {
      glv->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      glv->pe->setGravityScalar( Aftr::GRAVITY );
   }
   glv->setActorChaseType( STANDARDEZNAV );

   return glv;
}

Module::Module( const svector<string>& args ) : GLView( args ) {}

Module::~Module() {}

//call parent's resize method.
void Module::onResizeWindow( GLsizei width, GLsizei height ) {
   GLView::onResizeWindow( width, height );
} 

void Module::onMouseDown( const SDL_MouseButtonEvent& e ) {
   GLView::onMouseDown( e );
}

void Module::onMouseUp( const SDL_MouseButtonEvent& e ) {
   GLView::onMouseUp( e );
}

void Module::onMouseMove( const SDL_MouseMotionEvent& e ) {
   GLView::onMouseMove( e );
}

void Module::onKeyDown( const SDL_KeyboardEvent& key ) {
   GLView::onKeyDown( key );
   keyboard.onKeyDown(key.keysym.sym);
}

void Module::onKeyUp( const SDL_KeyboardEvent& key ) {
   GLView::onKeyUp( key );
   keyboard.onKeyUp(key.keysym.sym);
}

void Module::setSkyBox(string const& imgPath) {
   WO* wo = WOSkyBox::New(imgPath, this->getCameraPtrPtr());
   wo->setPosition(Vector(0,0,0));
   wo->setLabel("Sky Box");
   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   worldLst->push_back( wo );
}

bool Module::WOIsBetweenTwoOthers(WO const *const wo1, WO *const wo2, WO const *const wo3) {
   if (wo1 == nullptr || wo2 == nullptr || wo3 == nullptr) return false;
   Vector dummy;
   AftrGeometricTerm ret = wo2->getNearestPointWhereLineIntersectsMe(
      wo1->getPosition(), wo3->getPosition(), dummy
   );
   return (ret == Aftr::AftrGeometricTerm::geoSUCCESS);
}

string Module::LMM( string const& input ) {
   return ManagerEnvironmentConfiguration::getLMM() + input;
}

string Module::SMM( string const& input ) {
   return ManagerEnvironmentConfiguration::getSMM() + input;
}
