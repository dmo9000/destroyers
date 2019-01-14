#include <cassert>
#include "playerprojectile.h"

PlayerProjectile::PlayerProjectile()
{

    bShowDebug = true;
    if (bShowDebug) {
        std::cerr << "PlayerProjectile created" << std::endl;
    }
    TickFreq = PROJECTILE_SPEED;
    SetTickFrequency(PROJECTILE_SPEED);

}

PlayerProjectile::~PlayerProjectile()
{

    std::cerr << "PlayerProjectile destroyed" << std::endl;

}

int PlayerProjectile::Render()
{
    int ry1 = 0;
    int ry2 = 0;
    /* declared virtual, and usually overridden by derived class */
//    std::cerr << "PlayerProjectile::Render(" << ActorLocation.x << ", " << ActorLocation.y  << ")" << std::endl;

    grx_fillbox(ActorLocation.x-1, (ActorLocation.y >= 0 ? ActorLocation.y : 0), ActorLocation.x+1, ActorLocation.y+16, 255, 255, 255);

    return 1;
}

int PlayerProjectile::Tick()
{
    World *MyWorld = NULL;
    MyWorld = GetWorld();
    assert(MyWorld);

    /* declared virtual, and usually overridden by derived class */
    //std::cerr << "PlayerProjectile::Tick() -> " << TickFreq << ", " << TickToGo << std::endl;
    if (ActorLocation.y >= 4) {
        ActorLocation.y -= 1;
    } else {
//				std::cerr << "Time to despawn!" << std::endl;
        SetTickable(false);
        SetVisibility(false);
        MyWorld->UnregisterActor(this);
        //delete this;
    }

    return 1;
}

