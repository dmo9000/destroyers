#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>
#include "object.h"
#include "actor.h"



class World : public Object
{

public:
    World();
    ~World();
    int RegisterActor(Actor *a);
    int UnregisterActor(Actor *a);
    int RenderActors();
    int ProcessTicks(float d);
    int CleanupExpired();
		int SpawnQueuedActors();

protected:

private:
    std::vector<Actor*> RegisteredActors;
    std::vector<Actor*> SpawnedActors;
    int cleanup_count = 0;

};

World *GetWorld();

#endif /* __WORLD_H__ */
