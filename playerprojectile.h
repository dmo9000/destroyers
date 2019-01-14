#ifndef __PLAYERPROJECTILE_H__
#define __PLAYERPROJECTILE_H__

#include <cassert>
#include "actor.h"
#include "world.h"
#include "vector2.h"
#include "vector3.h"

typedef uint8_t u8;

#define PROJECTILE_SPEED	5.0f

class PlayerProjectile : public Actor
{

public:
    PlayerProjectile();
    virtual ~PlayerProjectile();
    virtual int Render();
    virtual int Tick();


protected:
    /* by default, tick on every frame */
    float TickFreq = PROJECTILE_SPEED;
    /* ticks are disabled by default */
    bool bCanEverTick = false;
    /* debugging flag */
    bool bShowDebug = false;
    /* rendered at all? */
    bool bIsVisible = false;

private:
    float TickToGo = TickFreq;
    bool bTickLatch  = false;

};

#endif /* __PLAYERPROJECTILE_H__ */
