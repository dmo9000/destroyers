#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <cassert>
#include "object.h"
#include "vector2.h"
#include "vector3.h"

typedef uint8_t u8;

extern "C" {
    void setTexturePixel(int x, int y, u8 r, u8 g, u8 b);
    int grx_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r, uint8_t g, uint8_t b);
    int grx_fillbox(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r, uint8_t g, uint8_t b);
};

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
    int WorldRegister();
    bool SetVisibility(bool v);
    bool SetTickable(bool t);
    int SetActorLocation(Vector2 l);
    int GetActorLocation(Vector2 *l);
    int SetTickFrequency(float f);
    bool CanBeDeleted();
    /* ready for deletion? wrap in method call please */
    bool bCanBeDeleted = false;


protected:
    /* by default, tick on every frame */
    float TickFreq = 0.0f;
    /* ticks are disabled by default */
    bool bCanEverTick = false;
    /* debugging flag */
    bool bShowDebug = false;
    /* rendered at all? */
    bool bIsVisible = false;
    /* actor location */
    Vector2 ActorLocation;

private:
    float TickToGo = TickFreq;

};

#endif /* __ACTOR_H__ */
