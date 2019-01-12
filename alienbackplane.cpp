#include "alienbackplane.h"

AlienBackPlane::AlienBackPlane()
{

    std::cout << "AlienBackPlane created" << std::endl;
		//bCanEverTick = true;
		TickFreq = 1000.0f;
		bIsVisible = false;

}

AlienBackPlane::~AlienBackPlane()
{

    std::cout << "AlienBackPlane destroyed" << std::endl;

}

AlienBackPlane::Render()
{

    /* just a shitty green marker box for now */

    grx_line(48, 48, 592, 48, 0, 255, 0);
    grx_line(592, 48, 592, 200, 0, 255, 0);
    grx_line(592, 200, 48, 200, 0, 255, 0);
    grx_line(48, 200, 48, 48, 0, 255, 0);

}


int AlienBackPlane::Tick()
{
	
		/* empty, since this actor does not tick (yet) */
		if (bShowDebug) {
			std::cout << "AlienBackPlane::Tick()\n" << std::endl;
			}
		return 0;
}
