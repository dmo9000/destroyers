#include "alienbackplane.h"
#include "world.h"


AlienBackPlane::AlienBackPlane()
{

    std::cerr << "AlienBackPlane created" << std::endl;
    bCanEverTick = true;
    TickFreq = 500.0f;
    //TickFreq = 10.0f;
//		TickFreq = 50.0f;
    bIsVisible = false;
//		bShowDebug = true;


    RowColors[0] = { 0, 192, 219 };
    RowColors[1] = { 239, 0, 137 };
    RowColors[2] = { 138, 199, 39 };
    RowColors[3] = { 247, 92, 0 };
    RowColors[4] = { 255, 186, 0 };



    for (int jj = 0 ; jj < ALIEN_ROWS; jj++) {
        for (int ii = 0 ; ii < ALIEN_COLS; ii++) {
            Aliens[ii][jj] = new AlienActor;
            Aliens[ii][jj]->SetGridLocation(ii,jj);
            Aliens[ii][jj]->SetBackPlane(this);
            Aliens[ii][jj]->SetVisibility(true);
            Aliens[ii][jj]->SetBaseColor(RowColors[jj]);
            Aliens[ii][jj]->SetAnimationType(jj % 5);
            AlienCount++;
        }
    }

}

AlienBackPlane::~AlienBackPlane()
{

    std::cerr << "AlienBackPlane destroyed" << std::endl;

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
        std::cerr << "AlienBackPlane::Tick()\n" << std::endl;
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
        std::cerr << "XTickCount = " << XTickCount << std::endl;
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

int AlienBackPlane::CheckOverlap(Actor *a)
{

    World *MyWorld = NULL;
    Vector2 ActorLocation;
    Vector2 CellLocation;
//    std::cerr << "AlienBackPlane::CheckOverlap()" << std::endl;
    assert(a);
    a->GetActorLocation(&ActorLocation);
    //std::cerr << "AlienBackPlane::Object = " << ActorLocation.x << ", " << ActorLocation.y << std::endl;

    /* we go backwards through the rows as a cheap optimization, since the projectiles travel up the screen */

    for (int jj = ALIEN_ROWS-1; jj >= 0; jj--) {
        for (int ii = 0; ii < ALIEN_COLS; ii++) {
            GetFormationPosition(&CellLocation, ii, jj);
            if (ActorLocation.x >= CellLocation.x && ActorLocation.x < (CellLocation.x + 48) &&
                    ActorLocation.y >= CellLocation.y && ActorLocation.y < (CellLocation.y + 48)) {
                MyWorld = GetWorld();
                //std::cerr << "+++ Projectile overlapped with cell " << ii << ", " << jj << std::endl;
                /* delete the alien */
                if (Aliens[ii][jj]) {
                    Aliens[ii][jj]->SetTickable(false);
                    Aliens[ii][jj]->SetVisibility(false);
                    MyWorld->UnregisterActor(Aliens[ii][jj]);
                    Aliens[ii][jj] = NULL;
                    AlienCount--;
                    std::cerr << "+++ AlienCount is now " << AlienCount << std::endl;
                    if (!AlienCount) {
                        std::cerr << "+++ WAVE COMPLETED! +++" << std::endl;
                    }
                }
            }
        }
    }

    return 1;

}
