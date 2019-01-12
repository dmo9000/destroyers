#include "starfield.h"


StarField::StarField()
{

    std::cout << "StarField created" << std::endl;


}

StarField::~StarField()
{

    std::cout << "StarField destroyed" << std::endl;

}

int StarField::Init()
{
    std::cout << "StarField::Init()" << std::endl;

    for (int i = 0; i < MAX_STARS; i++) {
        /* FIXME: get resolution from underlying canvas/display device */
        Stars[i].position.x = rand() % 640;
        Stars[i].position.y = rand() % 384;
        Stars[i].speed.x = 0;
        Stars[i].speed.y = (rand() % 5) + 1;
        Stars[i].color = (rand() % 255);
    }

    return 1;

}

void StarField::Scroll()
{

    for (int i = 0; i < MAX_STARS; i++) {
        Stars[i].position.y += Stars[i].speed.y;
        if (Stars[i].position.y >= 384) {
            Stars[i].position.y = (Stars[i].position.y % 384);
            Stars[i].position.x = rand() % 640;
            Stars[i].color = (rand() % 255);
            Stars[i].speed.y = (rand() % 5) + 1;
        }
    }
    return;
}

void StarField::Render()
{

    for (int i = 0; i < MAX_STARS; i++) {
        setTexturePixel(Stars[i].position.x, Stars[i].position.y,
                        Stars[i].color, Stars[i].color, Stars[i].color);
    }
    return;
}
