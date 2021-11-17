#include "ui.h"


void logOutMessage()
{
    printf("\nCERRANDO SESION...\n");
    Sleep(2000);
}

void logInMessage()
{
    gotoxy(49,20);
    printf("INICIANDO SESION.  \n");
    Sleep(800);
    gotoxy(49,20);
    printf("INICIANDO SESION.. \n");
    Sleep(800);
    gotoxy(49,20);
    printf("INICIANDO SESION...\n");
    Sleep(800);
}

void logInErrorMessage()
{
    gotoxy(42,20);
    puts("USUARIO O PASSWORD INCORRECTA...\n");
    Sleep(2000);
}

void userExistsMessage()
{
    printf("\nNombre de usuario ya existente! Elije otro...\n");
    Sleep(2000);
}


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
    int x0=32,y0=12;
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

void UIheader()
{
    color(main_color);
    system("cls");
    gotoxy(0,0);
    puts("=======================================================================================================================");
    gotoxy(0,2);
    printf("||");
    gotoxy(34,2);
    color(15);
    printf("CALENDAR.IO");
    color(main_color);
    gotoxy(75,2);
    printf("||");
    gotoxy(79,2);
    showTime();
    gotoxy(118,2);
    printf("||");
    gotoxy(0,3);
    puts("=======================================================================================================================");
}

void showTime() /// MUESTRA EL MES, EL DIA DE LA SEMANA Y LA HORA ACTUAL
{
    time_t s;
    struct tm* tiempo;
    char dia[DAY_LENGTH], mes[MONTH_LENGTH];

    s=time(NULL);
    tiempo=localtime(&s);

    dayName((*tiempo).tm_wday, dia);
    monthName((*tiempo).tm_mon, mes);

    color(15);
    printf("%s",mes);
    color(main_color);
    printf("   |   ");
    color(15);
    printf("%s",dia);
    color(main_color);
    printf("   |   ");
    color(15);
    printf("%02d:%02d",tiempo->tm_hour, tiempo->tm_min);
    color(main_color);
}

void UIcalendarTable(treeNode * userNode)//(int posActiva) /// IMPRIME CALENDARIO CON FECHAS Y CANTIDAD DE EVENTOS POR DIA, POR CATEGORIA (5 FILAS, 7 COLUMNAS)
{
    int i,j,x0=3,y0=5;
    int diaSemana,aux;

    int colorTrabajo=1,colorHogar=2,colorEstudio=5,colorCumpleanios=6,colorPersonal=7;
    time_t s;
    struct tm* tiempo;

    s=time(NULL);
    tiempo=localtime(&s);


//// HEADERS (DIAS DE LA SEMANA) ----------------------

    UIcalendarHeader (x0, y0);

// TABLE ------------------------

    UIcalendarPrtLines (x0, y0);

// FECHAS --------------------------------


    diaSemana=(*tiempo).tm_wday;

    int y=(*tiempo).tm_year, m=(*tiempo).tm_mon, d=(*tiempo).tm_mday;

    struct tm t = { .tm_year=y, .tm_mon=m, .tm_mday=d };

    t.tm_mday -= (7+diaSemana);

    for (i=0; i<5; i++)
    {
        j=0;
        color(COLOR_DOMINGO);
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
            color(COLOR_SEMANA);
        }
    }
}


void UIcalendarHeader (int x0, int y0)
{
    gotoxy(x0+5,y0-1);
    color(COLOR_DOMINGO);
    printf("Domingo");
    gotoxy(x0+5+17,y0-1);
    color(COLOR_SEMANA);
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

}

void UIcalendarPrtLines (int x0, int y0)
{
    color(7);
    int i,j;

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
}


void UIdaily(treeNode * userNode)
{
    int x0=33,y0=6;
    char day[DAY_LENGTH];
    int input;

    time_t s;
    struct tm* current;

    s=time(NULL);
    current=localtime(&s);

    int y=(*current).tm_year, m=(*current).tm_mon, d=(*current).tm_mday, dSem=(*current).tm_wday;
    struct tm t = { .tm_year=y, .tm_mon=m, .tm_mday=d, .tm_wday=dSem };

    do
    {
        mktime(&t);
        dayName(t.tm_wday,day);

        color(7);

        gotoxy(x0,y0);
        puts("_______________________________________________________");
        gotoxy(x0+16,y0-1);
        printf("%s %d del %d, año %d      ", day, t.tm_mday, t.tm_mon+1, t.tm_year+1900);

        for (int i=0; i<18; i++)
        {
            gotoxy(0,y0+1+i);
            puts("                                                                                                                   ");
        }

        gotoxy(x0,y0-3);
        puts("_______________________________________________________");
        gotoxy(x0+17,y0+17);
        color(main_color);
        puts("    PARA CAMBIAR DÍAS");
        gotoxy(x0+17,y0+17);
        color(7);
        puts("+/- ");
        gotoxy(x0-33,y0+21);
        puts("                                                                                                                                                  ");
        color(main_color);
        gotoxy(x0+23,y0+21);
        puts("     Volver");
        gotoxy(x0+23,y0+21);
        color(7);
        puts("ESC)");
        gotoxy(x0,y0+18);
        puts("_______________________________________________________");

        prtEventsByDay(userNode->eventList, t);

        input=getch();
        if (input==45)
            t.tm_mday-=1;
        else if (input==43)
            t.tm_mday+=1;

    }
    while (input!=ESC);

}

void prtEventsByDay (node * eventList, struct tm t)
{
    int i,x0=30,y0=8,cont;

    while (eventList!=NULL)
    {
        if(eventList->value.date.DD==t.tm_mday && eventList->value.date.MM==(t.tm_mon+1)
                && eventList->value.date.AAAA==(t.tm_year+1900)
                && eventList->value.activo==1)
        {

            prtEventRedux(eventList->value,x0,y0);
            cont++;
            if (cont==5)
            {
                x0=30;
                y0+=4;
                cont=0;
            }
            else
                x0+=20;

        }

        eventList=eventList->next;
    }
}



void dayName(int dayNumber, char day[]) /// LE ASIGNA NOMBRES A LAS VARIABLES DEFINIDAS EN STRUCT TIME QUE REFIEREN AL DIA DE LA SEMANA
{
    switch(dayNumber)
    {
    case 0:
        strcpy(day,"Domingo");
        break;
    case 1:
        strcpy(day,"Lunes");
        break;
    case 2:
        strcpy(day,"Martes");
        break;
    case 3:
        strcpy(day,"Miércoles");
        break;
    case 4:
        strcpy(day,"Jueves");
        break;
    case 5:
        strcpy(day,"Viernes");
        break;
    case 6:
        strcpy(day,"Sábado");
        break;
    }
}

void monthName(int monthNumber, char month[]) /// LO MISMO PERO CON LOS MESES...
{
    switch(monthNumber)
    {
    case 0:
        strcpy(month,"Enero");
        break;
    case 1:
        strcpy(month,"Febrero");
        break;
    case 2:
        strcpy(month,"Marzo");
        break;
    case 3:
        strcpy(month,"Abril");
        break;
    case 4:
        strcpy(month,"Mayo");
        break;
    case 5:
        strcpy(month,"Junio");
        break;
    case 6:
        strcpy(month,"Julio");
        break;
    case 7:
        strcpy(month,"Agosto");
        break;
    case 8:
        strcpy(month,"Septiembre");
        break;
    case 9:
        strcpy(month,"Octubre");
        break;
    case 10:
        strcpy(month,"Noviembre");
        break;
    case 11:
        strcpy(month,"Diciembre");
        break;
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

void deleteWarningMessage()
{
    printf("\nSe perderan todos los datos de manera permanete!");
    printf("\nEsta seguro que desea continuar? (s/n): ");
}


void mainMenu()
{
    //system("cls");
    color(3);
    UIintro();

    color(sec_color);
    gotoxy(30,27);
    puts("1)");
    color(main_color);
    gotoxy(35,27);
    printf("Login");
    color(sec_color);
    gotoxy(70,27);
    puts("2)");
    color(main_color);
    gotoxy(75,27);
    printf("Crear Cuenta");

//    color(7);
//    printf("\n 1) Log in");
//    printf("\n 2) Crear usuario");
//    printf("\n 3) Lista usuarios");
//    printf("\n 4) Ver Arbol");
//    printf("\n\n  ESC) Salir\n");
}

/// Muestra la vista de usuario loggeado
void userMenu()
{
    //system("cls");
    //printf("\nCALENDAR.IO\n");
    printf("\n 1) Crear evento");
    printf("\n 2) Ver eventos");
    printf("\n 3) Perfil");
    printf("\n 4) Vista Diaria");
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
