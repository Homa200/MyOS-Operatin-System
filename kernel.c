#include "video.h"
#include "keyboard.h"
#include "resume.h"

void buildFrame();
void civil();
void interests();
void education();


void kmain(unsigned long magic, unsigned long addr) {
	cls();
	chg_color(BG_WHITE | BLACK);
	disable_cursor();
	ata_test();
	print("Checking magic value  [OK]\n");
	ata_write();
	crt_scroll();
	print("Kernel loading! [OK]\nIt works!\n");
	chg_color(BG_WHITE | BLACK);
	while(1);
}


