#include "object.h"
extern "C" {
#include "ansitty.h"
int tty_getbuflen();
}

class TTY : public Object
{

public:
	TTY();
	~TTY();
	int Init();
	int putc(unsigned char c);
	int puts(const char *s);
	int getchar();
	int kb_getbuflen();

protected:

private:

};

