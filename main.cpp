#include <chrono>
#include <cstring>
#include <iostream>
#include "actor.h"
#include "tty.h"
#include "unistd.h"
#include "ansitty.h"
#include "starfield.h"

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
};


int main(int argc, char *argv[])
{

		uint64_t counter = 0;
    TTY *myTTY = NULL;
		StarField *MyStarField = NULL;
		float DeltaTime = 0.0f;

    char buffer[2048];
    int bytes =0;
    bool running = false;

    myTTY = new TTY();
    myTTY->Init();

		MyStarField = new StarField;
		MyStarField->Init(); 

    sleep(1);

    /* temporary splash screen */

    myTTY->puts("\x1b\x5B""?25l");
    myTTY->puts("\n\n");

/*
    FILE *myfile = NULL;
    myfile = fopen("data/ansi/frogue.ans", "rb");
    while (!feof(myfile) && !ferror(myfile)) {
        memset(&buffer, 0, 2048);
        bytes = fread(&buffer, 1, 2047, myfile);
        myTTY->puts(buffer);
    }
    fclose(myfile);

    myTTY->puts("                         (development version only)\n");

     ansitty_canvas_setdirty(true);
	*/

/*
    fprintf(stderr, "Waiting for input ...\n");
    while (myTTY->getchar() == 0) {
        ansitty_canvas_setdirty(true);
    }
*/

    myTTY->puts("\x1b\x5B""2J");

    ansitty_canvas_setdirty(true);

    //myTTY->puts("\x1b\x5B""?25l");

    running = true;


		auto CurrentChrono = std::chrono::high_resolution_clock::now();
		auto PreviousChrono = CurrentChrono;
		auto DeltaChrono = CurrentChrono - PreviousChrono; 

//		MyStarField->TickToGo = 1000.0f; 


		while (running) {

				/* calculate the time delta since we last went through the loop. this will
 					 be used to trigger ticks on the various game actors based on their tick frequency */

				PreviousChrono = CurrentChrono;
				CurrentChrono = std::chrono::high_resolution_clock::now();
				DeltaChrono = CurrentChrono - PreviousChrono;
				//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(CurrentChrono-PreviousChrono).count() << endl;
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
					}
					myTTY->TTYDevice->canvas->is_dirty = true;
				gfx_opengl_unlock();
    		gfx_opengl_expose();
			}


    exit(0);
}

