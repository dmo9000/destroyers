#ifndef __ALIENACTOR_H__
#define __ALIENACTOR_H__

#include "actor.h"
#include "alienbackplane.h"

class AlienBackPlane;

class AlienActor : public Actor 
{

public:
    AlienActor();
    ~AlienActor();
		virtual int Render();
		virtual int Tick();
		int SetBackPlane(AlienBackPlane *bp);
		int SetGridLocation(int x, int y);		


protected:

private:
		AlienBackPlane *MyBackPlane = NULL;
		int GridX = -1;
		int GridY = -1;
		int AnimationPhase = 0;

};

#endif /* __ALIENACTOR_H__ */
