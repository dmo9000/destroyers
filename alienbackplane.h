#ifndef __ALIENBACKPLANE_H__
#define __ALIENBACKPLANE_H__

#include "actor.h"

extern "C" {
    int grx_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r, uint8_t g, uint8_t b);
};

class AlienBackPlane : public Actor
{

public:
    AlienBackPlane();
    ~AlienBackPlane();
    void Render();

protected:

private:

};

#endif /* __ALIENBACKPLANE_H__ */
