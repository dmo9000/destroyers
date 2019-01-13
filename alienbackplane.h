#ifndef __ALIENBACKPLANE_H__
#define __ALIENBACKPLANE_H__

#include "actor.h"
#include "alienactor.h"

class AlienActor;

/*
extern "C" {
    int grx_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t r, uint8_t g, uint8_t b);
};
*/

#define DISPLAY_WIDTH   640
#define DISPLAY_HEIGHT  384
#define ALIEN_CELLSIZE  48
#define ALIEN_COLS      12
#define ALIEN_ROWS      5
#define ARRAY_WIDTH     (ALIEN_CELLSIZE * ALIEN_COLS)
#define ARRAY_HEIGHT    (ALIEN_CELLSIZE * ALIEN_ROWS)
#define ARRAY_XOFFSET   ((DISPLAY_WIDTH - ARRAY_WIDTH) / 2)
#define ARRAY_YOFFSET   (ARRAY_XOFFSET)

class AlienBackPlane : public Actor
{

public:
    AlienBackPlane();
    virtual ~AlienBackPlane();
		int Tick() override;
    int Render() override;
		int GetFormationPosition(Vector2 *p, int x, int y);

protected:

private:
		int XDirection = 1;
		int XTickCount = 0;
		int YTickOffset = 0;
		AlienActor *Aliens[ALIEN_COLS][ALIEN_ROWS];
		Vector3 RowColors[ALIEN_ROWS];

};

#endif /* __ALIENBACKPLANE_H__ */
