#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>
#include "unistd.h"
#include "ansitty.h"
#include "tty.h"
#include "actor.h"
#include "world.h"
#include "starfield.h"
#include "alienbackplane.h"

using std::cout;
using std::endl;
using std::memset;

//extern int fireMain();
extern "C" {
    void fireMain(void);
    void ansitty_canvas_setdirty(bool state);
    void clearTexture(ANSICanvas *canvas);
    void gfx_opengl_lock();
    void gfx_opengl_unlock();
    void gfx_opengl_expose();
    int  gfx_opengl_setwindowtitle(char *newtitle);
};

World *MyWorld = NULL;

World *GetWorld()
{

		return MyWorld; 
}

int main(int argc, char *argv[])
{

    uint64_t counter = 0;
    TTY *myTTY = NULL;
    StarField *MyStarField = NULL;
    AlienBackPlane *MyAlienBackPlane = NULL;
    float DeltaTime = 0.0f;

    char buffer[2048];
    int bytes =0;
    bool running = false;

    myTTY = new TTY();
    myTTY->Init();
		MyWorld = new World;

    sleep(1);

    MyStarField = new StarField;
    MyStarField->Init();
    MyAlienBackPlane = new AlienBackPlane;

//		MyWorld->RegisterActor(MyStarField);
//		MyWorld->RegisterActor(MyAlienBackPlane);

    gfx_opengl_setwindowtitle("Destroyers");

    running = true;

    auto CurrentChrono = std::chrono::high_resolution_clock::now();
    auto PreviousChrono = CurrentChrono;
    auto DeltaChrono = CurrentChrono - PreviousChrono;


    while (running) {

        /* calculate the time delta since we last went through the loop. this will
        	 be used to trigger ticks on the various game actors based on their tick frequency */

        PreviousChrono = CurrentChrono;
        CurrentChrono = std::chrono::high_resolution_clock::now();
        DeltaChrono = CurrentChrono - PreviousChrono;
        DeltaTime =  std::chrono::duration_cast<std::chrono::milliseconds>(CurrentChrono-PreviousChrono).count();
        DeltaTime /= 100.0;

        if (DeltaTime <= 0.001f) {
            DeltaTime = 0.001f;
        }

        //MyStarField->TickToGo -= DeltaTime;
        //fprintf(stderr, "DeltaTime %f, MyStarField->TickToGo %f\n", DeltaTime, MyStarField->TickToGo);

            //printf("+++ Starfield Scroll Timer expired\n");
          
				/*
        if (MyStarField->TickToGo <= 0.0f) {
            MyStarField->Scroll();
            MyStarField->TickToGo = MyStarField->TickFreq;
        }
				*/

        /* input processing */

        if (myTTY->hasinput()) {
            printf("+++ got data!\n");
            running = false;
        }

				
				MyWorld->ProcessTicks(DeltaTime);

        gfx_opengl_lock();
        if (myTTY->TTYDevice->canvas->is_dirty != true) {
            clearTexture(myTTY->TTYDevice->canvas);
						MyWorld->RenderActors();
        }
        myTTY->TTYDevice->canvas->is_dirty = true;
        gfx_opengl_unlock();
    }

    exit(0);
}

