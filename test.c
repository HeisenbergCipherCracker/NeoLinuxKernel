/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Enable color
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Print colored messages
    attron(COLOR_PAIR(1));
    printw("Press any key to continue...");
    attroff(COLOR_PAIR(1));
    refresh();
    getch();

    attron(COLOR_PAIR(2));
    printw("Hello, world!");
    attroff(COLOR_PAIR(2));
    refresh();
    getch();

    // Clean up ncurses
    endwin();

    return 0;
}
