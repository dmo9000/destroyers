#include "alienbackplane.h"

#define DISPLAY_WIDTH		640
#define DISPLAY_HEIGHT	384

#define ALIEN_CELLSIZE	48
#define ALIEN_COLS			12
#define ALIEN_ROWS			5
#define ARRAY_WIDTH			(ALIEN_CELLSIZE * ALIEN_COLS)
#define ARRAY_HEIGHT		(ALIEN_CELLSIZE * ALIEN_ROWS)
#define ARRAY_XOFFSET		((DISPLAY_WIDTH - ARRAY_WIDTH) / 2)
#define ARRAY_YOFFSET		(ARRAY_XOFFSET)

AlienBackPlane::AlienBackPlane()
{

    std::cout << "AlienBackPlane created" << std::endl;
		bCanEverTick = true;
		TickFreq = 1000.0f;
		//TickFreq = 10.0f;	
		bIsVisible = true;
//		bShowDebug = true;


		std::cout << "Array width:  " << ARRAY_WIDTH << std::endl;
		std::cout << "Array height: " << ARRAY_HEIGHT << std::endl;
		std::cout << "Array xoffset: " << ARRAY_XOFFSET << std::endl;
		std::cout << "Array yoffset: " << ARRAY_YOFFSET << std::endl;

}

AlienBackPlane::~AlienBackPlane()
{

    std::cout << "AlienBackPlane destroyed" << std::endl;

}

AlienBackPlane::Render()
{

		int XTickOffset = XTickCount * 2;
    /* just a shitty green marker box for now */

		for (int x = 0; x <= ALIEN_COLS; x++) {
			grx_line(ARRAY_XOFFSET + (x * ALIEN_CELLSIZE) + XTickOffset, ARRAY_YOFFSET + YTickOffset, 
								ARRAY_XOFFSET + (x * ALIEN_CELLSIZE) + XTickOffset, ARRAY_YOFFSET + YTickOffset + ARRAY_HEIGHT, 
						0, 255, 0);
			}
		for (int y = 0; y <= ALIEN_ROWS; y++) {
			grx_line(ARRAY_XOFFSET + XTickOffset, ARRAY_YOFFSET + YTickOffset + (y * ALIEN_CELLSIZE), 
								ARRAY_XOFFSET + XTickOffset + ARRAY_WIDTH, ARRAY_YOFFSET + YTickOffset + (y * ALIEN_CELLSIZE), 
									0, 255, 0);
			}

}


int AlienBackPlane::Tick()
{
		static bool ChangedDirectionFlag = false;	

		/* empty, since this actor does not tick (yet) */
		if (bShowDebug) {
			std::cout << "AlienBackPlane::Tick()\n" << std::endl;
			}

		if ((XTickCount == 10 || XTickCount == -10) && !ChangedDirectionFlag) {
				/* flip direction */
				XDirection = XDirection * -1;
				if (YTickOffset <= 64) {
						YTickOffset += 2;
						}
				ChangedDirectionFlag = true;
				} else {
				XTickCount += XDirection;
				ChangedDirectionFlag = false;
				}
		if (bShowDebug) {
			std::cout << "XTickCount = " << XTickCount << std::endl;
			}

		return 0;
}
