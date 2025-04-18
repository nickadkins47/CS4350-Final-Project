
#pragma once

#include "WOWayPointAbstract.h"

namespace Aftr
{

/**
\author Chad Mourning

The WOWayPoint class is used for any event driven interaction.
There are 3 basic types of WayPoints:  
Standard WayPoints' "onTrigger" method is called when an activator passes within \see radius distance of it.
Inverse WayPoints' "onTrigger" method is called when an activator passes outside of the \see radius
Global WayPoints' "onTrigger method is called whenever all of its prerequisettes have been met and it is enabled.
All subtypes of way points can be one-use or multi-use.  Mutli-use way points are automatically reenabled based on a given frequency (defauly is 1 second).

*/
class WOWayPointSpherical : public WOWayPointAbstract
{
public:	
   static WOWayPointSpherical* New( const WayPointParametersBase& params, float radius );
   /**
   Destructor
   */
   virtual ~WOWayPointSpherical();
   virtual void onTrigger();
   virtual bool activate(Aftr::WO* activator);
   float getRadius(){return radius;}
   float getRealRadius(){return sqrt(radius);}
protected:
   /**
   Constructor
   */
   WOWayPointSpherical( const WayPointParametersBase& params, float radius );
   virtual void onCreate();
   float radius;

};

}

