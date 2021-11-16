#include "ui.h"


void logOutMessage()
{
    printf("\nCERRANDO SESION...\n");
    Sleep(2000);
}

void logInMessage()
{
    printf("\nINICIANDO SESION...\n");
    Sleep(2000);
}

void logInErrorMessage()
{
    printf("\nUSUARIO O PASSWORD INCORRECTA...\n");
    Sleep(2000);
}

void userExistsMessage()
{
    printf("\nNombre de usuario ya existente! Elije otro...\n");
    Sleep(2000);
}

<<<<<<< HEAD
void color(int c) /// CAMBIA EL COLOR DE LA FUENTE
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (c & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}


void UIintro() ///MUESTRA "CALENDAR.IO" COMO BIENVENIDA AL PROGRAMA
{
    int x0=30,y0=10;
    gotoxy(x0,y0);
    puts("   ___      _                _                  _       ");
    gotoxy(x0,y0+1);
    puts("  / __\\\__ _| | ___ _ __   __| | __ _ _ __      (_) ___  ");
    gotoxy(x0,y0+2);
    puts(" / /  / _` | |/ _ \\\ '_ \\\ / _` |/ _` | '__|     | |/ _ \\\ ");
    gotoxy(x0,y0+3);
    puts("/ /__| (_| | |  __/ | | | (_| | (_| | |     _  | | (_) |");
    gotoxy(x0,y0+4);
    puts("\\\____/\\\__,_|_|\\\___|_| |_|\\\__,_|\\\__,_|_|    (_) |_|\\\___/ ");

    hidecursor(0);
}

void UIcalendarTable(treeNode * userNode)//(int posActiva) /// IMPRIME CALENDARIO CON FECHAS Y CANTIDAD DE EVENTOS POR DIA, POR CATEGORIA (5 FILAS, 7 COLUMNAS)
{
    int i,j,x0=3,y0=5,colorDomingo=11,colorSemana=14;
    int diaSemana,aux;

    int colorTrabajo=1,colorHogar=2,colorEstudio=5,colorCumpleanios=6,colorPersonal=7;
    time_t s;
    struct tm* tiempo;

    s=time(NULL);
    tiempo=localtime(&s);


// HEADERS ----------------------
    gotoxy(x0+5,y0-1);
    color(colorDomingo);
    printf("Domingo");
    gotoxy(x0+5+17,y0-1);
    color(colorSemana);
    printf("Lunes");
    gotoxy(x0+6+16*2,y0-1);
    printf("Martes");
    gotoxy(x0+4+16*3,y0-1);
    printf("Miércoles");
    gotoxy(x0+5+16*4,y0-1);
    printf("Jueves");
    gotoxy(x0+5+16*5,y0-1);
    printf("Viernes");
    gotoxy(x0+6+16*6,y0-1);
    printf("Sábado");

// TABLE ------------------------

    color(7);


    for (i=1; i<8; i++)
    {
        gotoxy(x0+16*i,y0);
        puts("|");
    }

    for(i=0; i<6; i++)
    {
        gotoxy(x0,y0+4*i);
        puts("_________________________________________________________________________________________________________________");

    }

    for (i=1; i<7; i++)
    {
        gotoxy(x0+16*i,y0);
        puts("|");
    }

    for (i=0; i<8; i++)
    {
        for (j=0; j<20; j++)
        {
            gotoxy(x0+16*i,y0+1+j);
            puts("|");
        }
    }

// FECHAS --------------------------------


    diaSemana=(*tiempo).tm_wday;

    int y=(*tiempo).tm_year, m=(*tiempo).tm_mon, d=(*tiempo).tm_mday;

    struct tm t = { .tm_year=y, .tm_mon=m, .tm_mday=d };

    t.tm_mday -= (7+diaSemana);

    for (i=0; i<5; i++)
    {
        j=0;
        color(colorDomingo);
        for (j=0; j<7; j++)
        {
            mktime(&t);
            //---- fecha -------------------------------


            if(t.tm_mon!=m)
                color(8);
            else if (t.tm_mday==d && t.tm_mon==m)
            {
                color(10);
                gotoxy((x0+1)+16*j,(y0+2)+4*i);
                printf("X");
                gotoxy((x0+1)+16*j,(y0+3)+4*i);
                printf("X");
                gotoxy((x0+14)+16*j,(y0+2)+4*i);
                printf(" X");
                gotoxy((x0+14)+16*j,(y0+3)+4*i);
                printf(" X");
                color(7);

            }
            else
                color(7);
            gotoxy((x0+1)+16*j,(y0+1)+4*i);
            printf("%2d",t.tm_mday);



// CATEGORY DATA --------------------------

            color(7);

            aux=countByCategoryAndDay(userNode->eventList,"Trabajo",t);
            if (aux>0)
            {
                gotoxy((x0+4)+16*j,(y0+2)+4*i);
                color(colorTrabajo);
                printf("T:%2d",aux);
            }

            aux=countByCategoryAndDay(userNode->eventList,"Hogar",t);
            if (aux>0)
            {
                gotoxy((x0+4)+16*j,(y0+3)+4*i);
                color(colorHogar);
                printf("H:%2d",aux);
            }

            aux=countByCategoryAndDay(userNode->eventList,"Estudio",t);
            if (aux>0)
            {
                gotoxy((x0+9)+16*j,(y0+2)+4*i);
                color(colorEstudio);
                printf("E:%2d",aux);
            }

            aux=countByCategoryAndDay(userNode->eventList,"Cumpleaños",t);
            if (aux>0)
            {
                gotoxy((x0+9)+16*j,(y0+1)+4*i);
                color(colorCumpleanios);
                printf("C:%2d",aux);
            }

            aux=countByCategoryAndDay(userNode->eventList,"Personal",t);
            if (aux>0)
            {
                gotoxy((x0+9)+16*j,(y0+3)+4*i);
                color(colorPersonal);
                printf("P:%2d",aux);
            }

            t.tm_mday+=1;
            color(colorSemana);
        }
    }
}



void hidecursor(int ver)   /// Función para mostrar o esconder el cursor (0:ESCONDE, 1:MUESTRA)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = ver;
    SetConsoleCursorInfo(consoleHandle, &info);
}

/// Muestra las opciones del menú principal (Pre-usuario)
=======
void deleteWarningMessage()
{
    printf("\nSe perderan todos los datos de manera permanete!");
    printf("\nEsta seguro que desea continuar? (s/n): ");
}

>>>>>>> c7420f451b79eb79fd72b0e5498a229ce6769d02
void mainMenu()
{
    system("cls");
    color(3);
    UIintro();
    color(7);
    printf("\n 1) Log in");
    printf("\n 2) Crear usuario");
    printf("\n 3) Lista usuarios");
    printf("\n 4) Ver Arbol");
    printf("\n\n  ESC) Salir\n");
}

/// Muestra la vista de usuario loggeado
void userMenu()
{
    system("cls");
    //printf("\nCALENDAR.IO\n");
    printf("\n 1) Crear evento");
    printf("\n 2) Ver eventos");
    printf("\n 3) Perfil");
    printf("\n\n  ESC) Salir\n");
}

void profileMenu(user u)
{
    system("cls");
    printf("\nCALENDAR.IO\n");
    prtUser(u);
    printf("\n 1) Cambiar password");
    printf("\n 2) Borrar cuenta");
    printf("\n\n  ESC) Atras\n");
}
