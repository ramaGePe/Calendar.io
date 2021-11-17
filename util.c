#include "util.h"


void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}


//void gotoxy (int x, int y) /// CORRIMIENTO DADO POR LOS VALORES DE COORDENADAS X e Y
//{
//    COORD xy = {0, 0};
//    xy.X = x;
//    xy.Y = y; // X and Y coordinates
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
//}


int maxx(int a, int b)
{
    return (a>=b)? a : b;
}

int diff(int a, int b)
{
    return (a-b<0)?(a-b)*(-1):a-b;
}

