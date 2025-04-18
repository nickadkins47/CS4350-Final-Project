
//Broke Down ModuleGLView into several smaller files
//This: updateWorld()

#include "ModuleHdr.h"
using namespace Aftr;

void Module::updateWorld() {
   GLView::updateWorld();

   if( this->gulfstream != nullptr && this->moon != nullptr ) {
      Mat4 const newPos = this->orbit_gui.compute_pose( this->gulfstream->getModel()->getPose() );
      //if (audioman["siren"] != nullptr)
      //   audioman["siren"]->setPosition(VecAtoI(newPos.getPosition()));
      this->moon->setPose(newPos);
   }

   camera.update();
   obj_move_gui.update();
   audioman.updateListenerPos();

   /*if (WOIsBetweenTwoOthers(cam, gulfstream2, moon)) {
      audioman["siren"]->setVolume(0);
   } else {
      audioman["siren"]->setVolume(3.5);
   }*/

}