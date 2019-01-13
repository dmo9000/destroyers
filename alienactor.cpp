#include <cassert>
#include "alienactor.h"
#include "world.h"


int pixels_A[2][16][16] {
		{
  	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
    	{ 0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0 },
    	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
    	{ 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		},
		{
  	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
   	 	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
    	{ 0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0 },
    	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
    	{ 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		}
};

int pixels_B[2][16][16] {
    {
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
      { 0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0 },
      { 0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,0 },
      { 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
    },
    {
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
      { 0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0 },
      { 0,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0 },
      { 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
    }
};



AlienActor::AlienActor()
{

    //std::cout << "AlienActor created" << std::endl;
    WorldRegister();
    //bShowDebug = true;
   	//TickFreq = 2500.0f;
   	TickFreq = 250.0f;
   	bCanEverTick = true;
		bShowDebug = false;
		 
}

AlienActor::~AlienActor()
{

//    std::cout << "AlienActor destroyed" << std::endl;

}

int AlienActor::Render()
{
		int (*pixels)[16][16] = pixels_B; 
    Vector2 MyLocation;
    /* declared virtual, and usually overridden by derived class */
    if (bShowDebug) {
        std::cout << "AlienActor::Render()" << std::endl;
    }
    assert(MyBackPlane);
    MyBackPlane->GetFormationPosition(&MyLocation, GridX, GridY);
    if (bShowDebug) {
        std::cout << "MyLocation = " << MyLocation.x << ", " << MyLocation.y << std::endl;
    }

//		grx_line(MyLocation.x, MyLocation.y, MyLocation.x + 48, MyLocation.y + 48, 255, 0, 0);
//		grx_line(MyLocation.x, MyLocation.y+48, MyLocation.x + 48, MyLocation.y, 255, 0, 0);


    for (int ii = 0; ii < 16; ii++) {
        for (int jj = 0; jj < 16; jj++) {
            if (pixels[AnimationPhase][jj][ii]) {
//                setTexturePixel(MyLocation.x + ii, MyLocation.y + jj, 255, 255, 255);
									grx_fillbox(MyLocation.x + ((ii)*3), MyLocation.y + ((jj)*3), 
																MyLocation.x + ((ii+1) * 3), MyLocation.y + ((jj+1) * 3), BaseColor.r, BaseColor.g, BaseColor.b); 
            }
        }
    }

}

int AlienActor::Tick()
{

    /* declared virtual, and usually overridden by derived class */
    if (bShowDebug) {
        std::cout << "AlienActor Tick" << std::endl;
    }
		AnimationPhase = AnimationPhase + 1;
		AnimationPhase = (AnimationPhase % 2);
}

int AlienActor::SetBackPlane(AlienBackPlane *bp)
{

    MyBackPlane = bp;
    return 0;
}


int AlienActor::SetGridLocation(int x, int y)
{

//    std::cout << "AlienActor::SetGridLocation(" << x << ", " << y << ")" << std::endl;
    GridX = x;
    GridY = y;
    return 0;
}

int AlienActor::SetBaseColor(Vector3 V)
{
               BaseColor.r = V.r;
               BaseColor.g = V.g;
               BaseColor.b = V.b;

}
