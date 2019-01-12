#include <chrono>
#include <cstring>
#include <iostream>
#include "actor.h"
#include "tty.h"
#include "unistd.h"
#include "ansitty.h"
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

    MyStarField = new StarField;
    MyStarField->Init();
    MyAlienBackPlane = new AlienBackPlane;

    //gfx_opengl_setwindowtitle("Destroyers 0.01");

    sleep(3);


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

        MyStarField->TickToGo -= DeltaTime;
        //fprintf(stderr, "DeltaTime %f, MyStarField->TickToGo %f\n", DeltaTime, MyStarField->TickToGo);

        if (MyStarField->TickToGo <= 0.0f) {
            MyStarField->Scroll();
            MyStarField->TickToGo = MyStarField->TickFreq;
            //printf("+++ Starfield Scroll Timer expired\n");
        }

        /* input processing */

        if (myTTY->hasinput()) {
            printf("+++ got data!\n");
            running = false;
        }

        gfx_opengl_lock();
        if (myTTY->TTYDevice->canvas->is_dirty != true) {
            clearTexture(myTTY->TTYDevice->canvas);
            MyStarField->Render();
            MyAlienBackPlane->Render();
        }
        myTTY->TTYDevice->canvas->is_dirty = true;
        gfx_opengl_unlock();
        //gfx_opengl_expose();
    }


    exit(0);
}

