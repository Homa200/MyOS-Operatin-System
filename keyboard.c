#include "video.h"

const char *scancode = "   1234567890-=\b^qwertyuiop[]\n^asdfghjkl;'`  zxcvbnm,./^*^   ^^^^^^^^^^^^^^789-456+1230.^^   !@#$%^&*()_+^^QWERTYUIOP{}\n^ASDFGHJKL:'^  ZXCVBNM<>?^*^   ^^^^^^^^^^^^^^&*(_$%^+!@#)>^^";


static inline char inb(short port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}


static inline void outb(short port, char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

int GetCH()
{
	char c = 0;
	while(1){
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c>0)
			{
				return scancode[c+1];
			}
		}
	}
	return 0;
}

char GetSCD()
{
	char c=0;
	do
	{
		if(inb(0x60)!=c)
		{
			c=inb(0x60);
			if(c>0)
			return c;
		}
	}while(1);
}

char GetChar()
{
	return scancode[GetSCD()+1];
}

void WaitKey(int key)
{
	while(inb(0x60)!=key);
}

void CLICommandParse(char key)
{
	switch(key)
        case '1':
        {
			chg_color(BG_BLACK |CYAN);
			locate(3,3);
            print("\nTest\nssh : / > ");
			break;
			  
		}
}


void kbd()
{
	do{
	GetChar();
	printchar(GetChar());
	CLICommandParse(GetChar());
	}while(10);
}

