#include "world.h"
#include "starfield.h"
#include "alienbackplane.h"

World::World()
{

    std::cout << "World created" << std::endl;


}

World::~World()
{

    std::cout << "World destroyed" << std::endl;

}

int World::RegisterActor(Actor *a)
{

//    std::cout << "Registering actor ... " << std::endl;
    RegisteredActors.push_back(a);

}

int World::RenderActors()
{

    std::vector<Actor*>::iterator iter, end;
    for (iter = RegisteredActors.begin() ; iter != RegisteredActors.end(); ++iter) {
				if ((*iter)->IsVisible()) {
        	(*iter)->Render();
					}
    }
}


int World::ProcessTicks(float d)
{
    std::vector<Actor*>::iterator iter, end;
//    std::cout << "World::ProcessTicks(" << d << ")" << std::endl;
    for (iter = RegisteredActors.begin() ; iter != RegisteredActors.end(); ++iter) {
				if ((*iter)->IsTickable()) {
	        (*iter)->SubtractDeltaTime(d);
					}
    }
    return 1;
}
