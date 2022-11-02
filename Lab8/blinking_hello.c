#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#define MESSAGE "Hello, world"
#define BLANK   "            "

void move_msg(int);
int set_ticker(int);

int row;
int col;

int main() 
{
    int delay;
    int c;
    void move_msg(int);

    initscr();
    crmode();
    noecho();
    clear();

    row   = 10;
    col   = 20;
    delay = 2000;

    move(row, col);
    addstr(MESSAGE);
    signal(SIGALRM, move_msg);
    set_ticker(delay);

    while(1) 
    {
        c = getch();
        if (c == 'Q') break;
    }
    endwin();
    return 0;
}

void move_msg(int signum)
{	
    signal(SIGALRM, move_msg);
    move(row, col);
    addstr(BLANK);
    refresh();	
    sleep(1);
    move(row, col);		
    addstr(MESSAGE);		
    refresh();	  
}

int set_ticker(int n_msecs)
{
    struct itimerval new_timeset;
    long n_sec,n_usecs;
    
    n_sec=n_msecs/1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL,&new_timeset,NULL);
}
