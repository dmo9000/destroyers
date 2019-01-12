#include "alienbackplane.h"

AlienBackPlane::AlienBackPlane()
{

    std::cout << "AlienBackPlane created" << std::endl;


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
