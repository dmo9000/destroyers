#include <cassert>
#include "actor.h"
#include "world.h"

Actor::Actor()
{

//    std::cerr << "Actor created" << std::endl;
    WorldRegister();

}

Actor::~Actor()
{

//    std::cerr << "Actor destroyed" << std::endl;

}

int Actor::Render()
{
    /* declared virtual, and usually overridden by derived class */
    std::cerr << "Actor::Render()" << std::endl;

}

int Actor::Tick()
{

    /* declared virtual, and usually overridden by derived class */
    std::cerr << "Actor::Tick()" << std::endl;
}

int Actor::SubtractDeltaTime(float d)
{

    TickToGo -= d;

    //std::cerr << "SubtractDeltaTime(" << d << ") = " << TickToGo << std::endl;
    if (TickToGo <= 0.0f) {
        //std::cerr << "Tick triggered!" << std::endl;
        Tick();
        TickToGo = TickFreq;
        //std::cerr << "Reset Tick Timer " << TickFreq << std::endl;
    }

    return 0;
}

int Actor::WorldRegister()
{
    World *ThisWorld = NULL;
    ThisWorld = GetWorld();
    assert(ThisWorld);
    ThisWorld->RegisterActor(this);
    return 1;
}

bool Actor::IsTickable()
{
    return bCanEverTick;
}

bool Actor::IsVisible()
{
    return bIsVisible;
}

bool Actor::SetVisibility(bool vs)
{
    bIsVisible = vs;
    return (bIsVisible);
}

bool Actor::SetTickable(bool ts)
{
    bCanEverTick = ts;
    TickToGo= TickFreq;
    return (bCanEverTick);
}


int Actor::SetActorLocation(Vector2 v)
{

    ActorLocation.x = v.x;
    ActorLocation.y = v.y;
    return 1;
}

int Actor::SetTickFrequency(float f)
{
    TickFreq = f;
    TickToGo = TickFreq;
    return 1;
}

bool Actor::CanBeDeleted()
{
    return bCanBeDeleted;
}
