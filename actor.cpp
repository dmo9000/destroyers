#include <cassert>
#include "actor.h"
#include "world.h"

Actor::Actor()
{

//    std::cout << "Actor created" << std::endl;
		WorldRegister();

}

Actor::~Actor()
{

   std::cout << "Actor destroyed" << std::endl;

}

int Actor::Render()
{
		/* declared virtual, and usually overridden by derived class */
    std::cout << "Actor::Render()" << std::endl;

}

int Actor::Tick()
{

		/* declared virtual, and usually overridden by derived class */
    std::cout << "Actor::Tick()" << std::endl;
}

int Actor::SubtractDeltaTime(float d)
{

    TickToGo -= d;

		//std::cout << "SubtractDeltaTime(" << d << ") = " << TickToGo << std::endl;
    if (TickToGo <= 0.0f) {
        //std::cout << "Tick triggered!" << std::endl;
       	Tick();
    		TickToGo = TickFreq;
				//std::cout << "Reset Tick Timer " << TickFreq << std::endl;
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
