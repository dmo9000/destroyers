#include <cstdlib>
#include "actor.h"
#include "vector2d.h"


typedef uint8_t u8;

#define MAX_STARS	100


extern "C" {
	void setTexturePixel(int x, int y, u8 r, u8 g, u8 b);	
};

class StarField : public Actor
{

public:
	StarField();
	~StarField();
	int Init();
	void Scroll();
	void Render();

protected:

private:
	Vector2D star_positions[MAX_STARS];

};

