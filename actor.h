#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "object.h"

class Actor : public Object
{

public:
    Actor();
    ~Actor();
		virtual int Render();
		virtual int Tick();
		int SubtractDeltaTime(float d);
		bool IsTickable();
		bool IsVisible();
		

protected:
		/* by default, tick on every frame */
    float TickFreq = 0.0f;
		/* ticks are disabled by default */
    bool bCanEverTick = false;
		/* debugging flag */
		bool bShowDebug = false;
		/* rendered at all? */
		bool bIsVisible = true;

private:
    float TickToGo = TickFreq;

};

#endif /* __ACTOR_H__ */
