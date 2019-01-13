#include <cstdlib>
#include <cstdbool>
#include "actor.h"
#include "vector2.h"

typedef uint8_t u8;

#define MAX_STARS	100

typedef struct _stardata {
    Vector2 position;
    Vector2 speed;
    uint8_t color;
} StarData;


/*
extern "C" {
    void setTexturePixel(int x, int y, u8 r, u8 g, u8 b);
};
*/

class StarField : public Actor
{

public:
    StarField();
    ~StarField();
    int Init();
   	int Tick() override;
    int Render() override;

protected:

private:
    StarData Stars[MAX_STARS];


};

