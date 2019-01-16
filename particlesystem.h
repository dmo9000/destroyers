#ifndef  __PARTICLESYSTEM_H__ 
#define  __PARTICLESYSTEM_H__ 

#include "actor.h"

#define MAX_PARTICLES 20	


class ParticleSystem : public Actor
{

public:
		ParticleSystem();
		virtual	~ParticleSystem();
		virtual Tick();
		virtual Render();
		int Setup();


protected:


private:
		Vector2 ParticleLocation[MAX_PARTICLES];
		Vector2 ParticleSize[MAX_PARTICLES];
		uint8_t ParticleColor[MAX_PARTICLES];
		uint8_t ParticleCount;

};


#endif /* __PARTICLESYSTEM_H__ */

