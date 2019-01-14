#ifndef __PLAYERACTOR_H__
#define __PLAYERACTOR_H__

#include "actor.h"


class PlayerActor : public Actor
{

public:
    PlayerActor();
    virtual ~PlayerActor();
    virtual int Render();
    virtual int Tick();
    int MoveLeft();
    int MoveRight();
    int LaunchProjectile();
    int LastInertia = 0;
    int Inertia  = 0;


protected:

private:
    Vector2 MyLocation;
    Vector3 BaseColor = { 255, 255, 255 };
    float CoolDownTimer = 0.0f;

};

#endif /* __PLAYERACTOR_H__ */
