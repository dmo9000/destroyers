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
};


int main(int argc, char *argv[])
{

		uint64_t counter = 0;
    TTY *myTTY = NULL;
		StarField *MyStarField = NULL;

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

    FILE *myfile = NULL;
    myfile = fopen("data/ansi/frogue.ans", "rb");
    while (!feof(myfile) && !ferror(myfile)) {
        memset(&buffer, 0, 2048);
        bytes = fread(&buffer, 1, 2047, myfile);
        myTTY->puts(buffer);
    }
    fclose(myfile);

    myTTY->puts("                         (development version only)\n");


    fprintf(stderr, "Waiting for input ...\n");
    while (myTTY->getchar() == 0) {
        ansitty_canvas_setdirty(true);
    }

    myTTY->puts("\x1b\x5B""2J");

    ansitty_canvas_setdirty(true);

    //myTTY->puts("\x1b\x5B""?25l");

    running = true;

		while (running) {
        if (myTTY->hasinput()) {
							printf("+++ got data!\n");
							running = false;
				}

//				gfx_opengl_lock();
//				gfx_opengl_unlock();
				counter++;
				if (!(counter % 100)) {
					MyStarField->Scroll();
				}
				gfx_opengl_lock();
			  clearTexture(myTTY->TTYDevice->canvas);
				MyStarField->Render();
    		ansitty_canvas_setdirty(true);
				gfx_opengl_unlock();
			}


    exit(0);
}

