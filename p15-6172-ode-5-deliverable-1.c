#include <stdio.h>
#include <curses.h>
#define DELAY 60000
int main (int argc, char *argv[])
{ 
    initscr(); 
    noecho();

    curs_set(FALSE);
    int max_x, max_y, i, c;
    getmaxyx(stdscr, max_y, max_x);
    int pos_x = 0, pos_y = max_y - 1, direction_x = 1, direction_y = 1, g = 1, next_x, next_y;
    double vX = 0, vY = 0;
    double vXNew = 0, vYNew = 0;
    
    
    double aX = 0, aY = 0;
    
    double dt = 1;
    double f = 1;
    
    WINDOW *menu_win = newwin(max_y, max_x, 0, 0);
    keypad(menu_win, TRUE);
    for (i = 0; i < 5000; i++) {
        clear();
        mvprintw(pos_y, pos_x, "o");

        refresh();
        nodelay(stdscr, FALSE),
        c = wgetch(menu_win);
        switch(c)
        { 
            case KEY_LEFT:
            vXNew = ((pos_x + direction_x) - pos_x) * dt;
            aX = (vXNew - vX) * dt;
            vX = vXNew;
            pos_x -= vXNew; 
            break;
        
            case KEY_RIGHT: 
            vXNew = ((pos_x + direction_x) - pos_x) * dt;
            aX = (vXNew - vX) * dt;
            vX = vXNew;
            pos_x += vXNew; 
            break;

            case ' ':
            vYNew = ((pos_y + direction_y) - pos_y) * dt;
            aY = (vYNew - vY) * dt;
            pos_y -= vYNew;
            vY = vYNew;
            
            break;
            
            default:
            vX = 0;
            vY = 0;
            vXNew = 0;
            vYNew = 0;
            aX = 0;
            aY = 0;
        }
        if(c != ' '){
            vYNew = g;
            vY = g;
            pos_y += vYNew;
        }
        next_x = pos_x + vXNew;
        next_y = pos_y + vYNew;
        if (next_y == max_y)
            pos_y = (max_y - 2);
        if (next_x == max_x) 
            pos_x = (max_x-2);
        if (next_x == 0) 
            pos_x = 2;
    }
    endwin();
    return 0;
}
