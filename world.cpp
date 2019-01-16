#include <algorithm>
#include "world.h"
#include "starfield.h"
#include "alienbackplane.h"

World::World()
{

    std::cerr << "World created" << std::endl;


}

World::~World()
{

    std::cerr << "World destroyed" << std::endl;

}

int World::RegisterActor(Actor *a)
{

    std::cerr << "Registering actor ... " << std::endl;

//    RegisteredActors.push_back(a);
    SpawnedActors.push_back(a);
   	std::cerr << "Register::WorldActorCount=" << RegisteredActors.size() << std::endl;
}

int World::UnregisterActor(Actor *a)
{

    std::vector<Actor*>::iterator iter, end;
    for (iter = RegisteredActors.begin() ; iter != RegisteredActors.end(); ++iter) {
        if ((*iter) == a) {
            //				std::cerr << "+++ Marking actor for deletion" << std::endl;
            //RegisteredActors.erase((iter));
            (*iter)->bCanBeDeleted = true;
            cleanup_count ++;
        }
    }
//		 RegisteredActors.erase(std::remove(RegisteredActors.begin(), RegisteredActors.end(), (Actor*) NULL), RegisteredActors.end());
    // std::cerr << "Unregister::WorldActorCount=" << RegisteredActors.size() << std::endl;

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

int World::SpawnQueuedActors()
{

    std::vector<Actor*>::iterator iter, end;
    for (iter =SpawnedActors.begin() ; iter != SpawnedActors.end(); ++iter) {
        if ((*iter)) {
								RegisteredActors.push_back(*iter);
                *iter = NULL;
        }
    }
    SpawnedActors.erase(std::remove(SpawnedActors.begin(), SpawnedActors.end(), (Actor*) NULL), SpawnedActors.end());

		return 1;
}


int World::ProcessTicks(float d)
{
    int cleaned_up = 0;
    std::vector<Actor*>::iterator iter, end;
    // std::cerr << "World::ProcessTicks(" << d << ")" << std::endl;
    for (iter = RegisteredActors.begin() ; iter != RegisteredActors.end(); ++iter) {

        if ((*iter)->IsTickable()) {
            (*iter)->SubtractDeltaTime(d);
        }
    }

    return 1;
}

int World::CleanupExpired()
{
    if (cleanup_count) {
        std::vector<Actor*>::iterator iter, end;
//    std::cerr << "World::ProcessTicks() -> cleanup " << cleanup_count << std::endl;
        for (iter = RegisteredActors.begin() ; iter != RegisteredActors.end(); ++iter) {
            if ((*iter)->CanBeDeleted()) {
                //          std::cerr << "+++ Removing actor" << std::endl;
                delete(*iter);
                *iter = NULL;
                cleanup_count --;
            }
        }
        RegisteredActors.erase(std::remove(RegisteredActors.begin(), RegisteredActors.end(), (Actor*) NULL), RegisteredActors.end());
//    std::cerr << "Unregister::WorldActorCount=" << RegisteredActors.size() << std::endl;
        assert(!cleanup_count);
    }
    return 1;
}
