
#include "world.h"
#include "particlesystem.h"


ParticleSystem::ParticleSystem()
{
	std::cerr << "ParticleSystem spawned!" << std::endl;
	bIsVisible = false;
	bCanEverTick = false;
	TickFreq = 10.0f;
}

ParticleSystem::~ParticleSystem()
{
	std::cerr << "ParticleSystem destroyed!" << std::endl;
}

ParticleSystem::Setup()
{

	std::cerr << "ParticleSystem::Setup()" << std::endl;
	for (int ii = 0; ii < MAX_PARTICLES; ii++) {
			ParticleLocation[ii].x = (ActorLocation.x + 24) + ((rand() % 72) - 36);
			ParticleLocation[ii].y = (ActorLocation.y + 24) + ((rand() % 72) - 36);
			ParticleSize[ii].x = (rand() % 6) + 2;
			ParticleSize[ii].y = ParticleSize[ii].x;
			ParticleColor[ii] = 255;
			}
		ParticleCount = MAX_PARTICLES;
	

}

int ParticleSystem::Render()
{
//	std::cerr << "ParticleSystem render" << std::endl;
		for (int ii = 0; ii < MAX_PARTICLES; ii++ ) {
			grx_fillbox(ParticleLocation[ii].x, ParticleLocation[ii].y, 
					ParticleLocation[ii].x + ParticleSize[ii].x, ParticleLocation[ii].y + ParticleSize[ii].y, 
						ParticleColor[ii], ParticleColor[ii], ParticleColor[ii]); 
		}
	return 1;
}

int ParticleSystem::Tick()
{
//	std::cerr << "ParticleSystem render @ " << ActorLocation.x << ", " << ActorLocation.y << std::endl;
//
		for (int ii = 0; ii < MAX_PARTICLES; ii++ ) {
			if (ParticleLocation[ii].y < 350) {
				ParticleLocation[ii].y ++;
				ParticleLocation[ii].x = (ActorLocation.x + 24) + ((rand() % 72) - 36);
				ParticleLocation[ii].y = (ActorLocation.y + 24) + ((rand() % 72) - 36);
				ParticleSize[ii].x = (rand() % 6) + 2;
				ParticleSize[ii].y = ParticleSize[ii].x;
				if (ParticleColor[ii] >= 4) {
					ParticleColor[ii] -= 4;
					} else {
					ParticleCount--;
					}
			}
	}

	if (ParticleCount == 0) {
		World *MyWorld = NULL;
		MyWorld = GetWorld();
		std::cerr << "Particle system expired... " << std::endl;
		MyWorld->UnregisterActor(this);
		}
	return 1;

}

