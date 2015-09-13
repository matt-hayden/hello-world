#include <stdio.h>
#include <sys/ioctl.h>


int
main (void)
{
    struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
    printf ("lines %d\n", max.ws_row);
    printf ("columns %d\n", max.ws_col);
}
