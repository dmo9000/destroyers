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
    int SetBaseColor(Vector3 V);
    int SetAnimationType(int t);

protected:

private:
    AlienBackPlane *MyBackPlane = NULL;
    int GridX = -1;
    int GridY = -1;
    int AnimationType = 0;
    int AnimationPhase = 0;
    Vector3 BaseColor = { 255, 255, 255 };

};

#endif /* __ALIENACTOR_H__ */
