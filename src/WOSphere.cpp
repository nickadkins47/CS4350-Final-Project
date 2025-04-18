#include "WOWayPointSpherical.h"
#include "MGLWayPointSpherical.h"
#include "WayPointParameters.h"
using namespace Aftr;

WOWayPointSpherical* WOWayPointSpherical::New( const WayPointParametersBase& params, float radius )
{
   WOWayPointSpherical* ptr = new WOWayPointSpherical(params, radius);
   ptr->onCreate();
   return ptr;
}

void WOWayPointSpherical::onCreate()
{
   model = new MGLWayPointSpherical( this );
   this->renderOrderType = RENDER_ORDER_TYPE::roTRANSPARENT;
}

WOWayPointSpherical::WOWayPointSpherical( const WayPointParametersBase& params, float radius ) : IFace( this ), WOWayPointAbstract( params )
{
   this->radius = radius * radius;
}

WOWayPointSpherical::~WOWayPointSpherical()
{
}

void WOWayPointSpherical::onTrigger()
{
   std::cout << std::endl
             << "This WOWayPoint is a base class. onTrigger()\n"
             << "does NOT do anything. Inherit a from WOWayPoint\n"
             << "and overload virtual void onTrigger() to specify an action!" 
             << "\n";
}

bool WOWayPointSpherical::activate(Aftr::WO *activator)
{
   if (activator == nullptr)
   {
      std::cout << "NULL activator!\n";
      return false;
   }
   Vector translateAmt = this->getPosition();
   Vector position = activator->getPosition();
   if(pow(translateAmt.x - position.x,2.0f) + pow(translateAmt.y - position.y, 2.0f) + pow(translateAmt.z - position.z, 2.0f) < radius)
      return true;
   return false;
}