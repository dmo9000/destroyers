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
		star_positions[i].x = rand() % 640;
		star_positions[i].y = rand() % 384;
		}

	return 1;

}

void StarField::Tick()
{

	for (int i = 0; i < MAX_STARS; i++) {
			star_positions[i].y ++;
			if (star_positions[i].y >= 384) {
					star_positions[i].y = (star_positions[i].y % 384);
					}
			setTexturePixel(star_positions[i].x, star_positions[i].y, 255, 255, 255);
			}
	return;
} 
