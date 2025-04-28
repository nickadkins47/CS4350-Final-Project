
//Broke Down ModuleGLView into several smaller files
//This: updateWorld()

#include "ModuleHdr.h"
using namespace Aftr;

void Module::updateWorld() {
   GLView::updateWorld();

   camera.update();
   audioman.updateListenerPos();

}