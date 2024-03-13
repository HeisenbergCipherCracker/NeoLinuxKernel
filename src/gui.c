/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include "console.h"
#include "gui.h"

void draw_taskbar(){
	printf("DESKTOP");
        console_gotoxy(80,20);
        printf("________________________________________________________________________________");
}

void draw_desktop(){
	console_init(COLOR_WHITE, COLOR_BLUE);
	draw_taskbar();
}

