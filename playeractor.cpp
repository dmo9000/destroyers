#include <cassert>
#include <cstdlib>
#include "playeractor.h"
#include "world.h"
#include "playerprojectile.h"


int pixels[16][16] {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
    { 0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0 },
    { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
    { 0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
    { 0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0 },
    { 0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

PlayerActor::PlayerActor()
{

    //std::cerr << "PlayerActor created" << std::endl;
    bShowDebug = true;
    //TickFreq = 2500.0f;
    TickFreq = 20.0f;
    bCanEverTick = true;
    bShowDebug = false;
    MyLocation.x = 296;
    MyLocation.y = 340;
    bIsVisible = true;

}

PlayerActor::~PlayerActor()
{

//    std::cerr << "PlayerActor destroyed" << std::endl;

}


int PlayerActor::Render()
{

    /* declared virtual, and usually overridden by derived class */
    if (bShowDebug) {
        std::cerr << "PlayerActor::Render()" << std::endl;
    }
    if (bShowDebug) {
        std::cerr << "MyLocation = " << MyLocation.x << ", " << MyLocation.y << std::endl;
    }


    for (int ii = 0; ii < 16; ii++) {
        for (int jj = 0; jj < 16; jj++) {
            if (pixels[jj][ii]) {
                int xoffset = MyLocation.x + (ii * 3);
                int yoffset = MyLocation.y + (jj * 3);
                grx_fillbox(xoffset, yoffset, xoffset+2, yoffset+2, BaseColor.r, BaseColor.g, BaseColor.b);
            }
        }
    }

}

int PlayerActor::Tick()
{

    /* declared virtual, and usually overridden by derived class */
    if (bShowDebug) {
        std::cerr << "PlayerActor Tick" << std::endl;
    }

    if (CoolDownTimer > 0.0) {
        CoolDownTimer -= TickFreq;
        if (CoolDownTimer < 0.0f) {
            CoolDownTimer = 0.0f;
        }
    }

    if (Inertia != 0) {
//				std::cerr << "Inertia: " << Inertia << std::endl;

        if (Inertia < 0) {
            Inertia ++;
        } else {
            Inertia --;
        }

        MyLocation.x += Inertia;

        if (MyLocation.x > 584) {
            MyLocation.x = 584;
            Inertia = 0;
        }

        if (MyLocation.x < 12) {
            MyLocation.x = 12;
            Inertia = 0;
        }

        //MyLocation.x += Inertia;
    }

}

int PlayerActor::MoveLeft()
{
    if (!Inertia) {
        Inertia -= 4;
    } else {
        if (Inertia > 0) {
            Inertia /= 4;
        } else {
            Inertia *= 4;
        }
    }
    if (Inertia < -4) {
        Inertia = -4;
    }
    return 1;
}

int PlayerActor::MoveRight()
{
    if (!Inertia) {
        Inertia += 4;
    } else {
        if (Inertia < 0) {
            Inertia /= 4;
        } else {
            Inertia *= 4;
        }
    }
    if (Inertia > 4) {
        Inertia = 4;
    }
    return 1;
}

int PlayerActor::LaunchProjectile()
{

    Vector2 SpawnLocation;
    PlayerProjectile *MyNewProjectile = NULL;
    if (bShowDebug) {
        fprintf(stderr, "PlayerActor::LaunchProjectile(%d, %d)\n", MyLocation.x, MyLocation.y);
    }

    if (CoolDownTimer > 0.0f) {
        if (bShowDebug) {
            fprintf(stderr, "(cooling down, %f)\n", CoolDownTimer);
        }
        return 0;
    }

    MyNewProjectile = new PlayerProjectile;
    SpawnLocation.x = MyLocation.x + 23;
    SpawnLocation.y = MyLocation.y - 16;
    MyNewProjectile->SetActorLocation(SpawnLocation);
    MyNewProjectile->SetVisibility(true);
    MyNewProjectile->SetTickFrequency(PROJECTILE_SPEED);
    MyNewProjectile->SetTickable(true);
    CoolDownTimer = 500.0f;
    return 1;
}
