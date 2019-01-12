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
		int RenderActors();
		int ProcessTicks(float d);

protected:

private:
		std::vector<Actor*> RegisteredActors;	

};

#endif /* __WORLD_H__ */
