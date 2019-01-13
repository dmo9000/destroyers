#include "alienbackplane.h"


AlienBackPlane::AlienBackPlane()
{

    std::cout << "AlienBackPlane created" << std::endl;
		bCanEverTick = true;
		TickFreq = 100.0f;
		//TickFreq = 10.0f;	
//		TickFreq = 50.0f;	
		bIsVisible = false;
//		bShowDebug = true;


	/*
		std::cout << "Array width:  " << ARRAY_WIDTH << std::endl;
		std::cout << "Array height: " << ARRAY_HEIGHT << std::endl;
		std::cout << "Array xoffset: " << ARRAY_XOFFSET << std::endl;
		std::cout << "Array yoffset: " << ARRAY_YOFFSET << std::endl;
	*/

		for (int jj = 0 ; jj < ALIEN_ROWS; jj++) {
			for (int ii = 0 ; ii < ALIEN_COLS; ii++) {
//			if (!(jj % 2)) {
				Aliens[ii][jj] = new AlienActor;
				Aliens[ii][jj]->SetGridLocation(ii,jj); 
				Aliens[ii][jj]->SetBackPlane(this);
				Aliens[ii][jj]->SetVisibility(true);
//				}
			}
		}

}

AlienBackPlane::~AlienBackPlane()
{

    std::cout << "AlienBackPlane destroyed" << std::endl;

}

int AlienBackPlane::Render()
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

int AlienBackPlane::GetFormationPosition(Vector2 *p, int x, int y)
{
	int XTickOffset = XTickCount * 2;

	assert(p);

	p->x = ARRAY_XOFFSET + (x * ALIEN_CELLSIZE) + XTickOffset; 
	p->y = ARRAY_YOFFSET + (y * ALIEN_CELLSIZE) + YTickOffset;

	return 1;
}
