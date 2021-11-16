#include "util.h"

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

int maxx(int a, int b)
{
    return (a>=b)? a : b;
}

int diff(int a, int b)
{
    return (a-b<0)?(a-b)*(-1):a-b;
}
