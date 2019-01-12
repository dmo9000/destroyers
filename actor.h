#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "object.h"

class Actor : public Object
{

public:
    Actor();
    ~Actor();
    float TickFreq = 100.0f;
    float TickToGo = TickFreq;
    bool bCanEverTick = false;

protected:

private:

};

#endif /* __ACTOR_H__ */
