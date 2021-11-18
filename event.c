#include "event.h"

/*******************************
    LIBRARY RELATED FUNCTIONS
*******************************/

void initList(node **head)
{
    *head = NULL;
}

node *newNode(event value)
{
    node *aux = (node *) malloc (sizeof(node));

    aux->value = value;
    aux->next = NULL;

    return aux;
}

void addToHead(node **head, node *newNode)
{
    if(*head)
    {
        newNode->next = (*head);
        (*head) = newNode;
    }else
    {
        (*head) = newNode;
    }
}

node *findEvent(node *head, int id)
{
    if(head)
    {
        while(head && head->value.id != id)
        {
            head = head->next;
        }
    }

    return head;
}

void deleteEvent(node **head, int id)
{
    if((*head) && (*head)->value.id == id)
    {
        node *aux = (*head);
        (*head) = (*head)->next;
        free(aux);
    }else
    {
        node *prev;
        node *temp = (*head);

        while(temp && temp->value.id != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if(temp)
        {
            prev->next = temp->next;
            free(temp);
        }
    }
}

int countListNodes(node *head)
{
    int cant=0;

    while(head)
    {
        cant++;
        head=head->next;
    }

    return cant;
}

void deleteList(node **head)
{
    if(*head)
    {
        node *temp;

        while(*head)
        {
            temp = (*head);
            (*head) = (*head)->next;
            free(temp);
        }
    }
}

/*******************************
        EVENTS FUNCTIONS
*******************************/

int newEventPos(node *head)
{
    int pos=1;

    while(head)
    {
        head=head->next;
        pos++;
    }

    return pos;
}

void redefId(node *head)
{
    int pos = 1;

    while(head)
    {
        head->value.id = pos;
        pos++;
        head=head->next;
    }
}

char *chooseCat(int x0, int y0)
{
    char input, cats[][CAT_LENGTH]= {"Personal", "Trabajo", "Estudio", "Hogar", "Cumpleaños"};
    char *cat = (char*)malloc(sizeof(char)*CAT_LENGTH);
    gotoxy(x0,y0);
    printf("Categoria:");
    gotoxy(x0,y0+1);
    printf("1) Personal");
    gotoxy(x0,y0+2);
    printf("2) Trabajo");
    gotoxy(x0,y0+3);
    printf("3) Estudio");
    gotoxy(x0,y0+4);
    printf("4) Hogar");
    gotoxy(x0,y0+5);
    printf("5) Cumpleaños");

    fflush(stdin);
    input=getch();
    switch(input)
    {
    case 49:
        strcpy(cat, cats[0]);
        break;
    case 50:
        strcpy(cat, cats[1]);
        break;
    case 51:
        strcpy(cat, cats[2]);
        break;
    case 52:
        strcpy(cat, cats[3]);
        break;
    case 53:
        strcpy(cat, cats[4]);
        break;
    }

    return cat;
}

int eventActive(int x0, int y0)
{
    char input;
    bool active;
    gotoxy(x0,y0);
    printf("Marcar como activo? (s/n)");
    input=getch();
    switch(input)
    {
    case 115:
        active=true;
        break;
    case 110:
        active=false;
        break;
    default:
        break;
    }

    return active;
}

int validDate(int DD, int MM, int AAAA, int x, int y)
{
    int flag=1;

    if(DD>31 || MM>12 || AAAA<2021)
    {
        flag=0;
        gotoxy(x,y);
        printf("          ");
    }

    return flag;
}

int validTime(int hh, int mm, int x, int y)
{
    int flag=1;

    if(hh>23 || mm>59)
    {
        flag=0;
        gotoxy(x,y);
        printf("          ");
    }

    return flag;
}

event insertEvent(node *head, char *username)
{
    char title[TITLE_LENGTH];
    int AAAA, MM, DD, hh, mm, x0=44,y0=6;
    event e;

    e.id = newEventPos(head);

    strcpy(e.username, username);
    gotoxy(x0,y0);
    puts("X*****************************X\n");
    gotoxy(x0,y0+1);
    puts("XX                           XX\n");
    gotoxy(x0,y0+2);
    puts("XX                           XX\n");
    gotoxy(x0,y0+3);
    puts("XX                           XX\n");
    gotoxy(x0,y0+4);
    puts("XX                           XX\n");
    gotoxy(x0,y0+5);
    puts("XX                           XX\n");
    gotoxy(x0,y0+6);
    puts("XX                           XX\n");
    gotoxy(x0,y0+7);
    puts("XX                           XX\n");
    gotoxy(x0,y0+8);
    puts("XX                           XX\n");
    gotoxy(x0,y0+9);
    puts("XX                           XX\n");
    gotoxy(x0,y0+10);
    puts("XX                           XX\n");
    gotoxy(x0,y0+11);
    puts("XX                           XX\n");
    gotoxy(x0,y0+12);
    puts("XX                           XX\n");
    gotoxy(x0,y0+13);
    puts("XX                           XX\n");
    gotoxy(x0,y0+14);
    puts("XX                           XX\n");
    gotoxy(x0,y0+15);
    puts("XX                           XX\n");
    gotoxy(x0,y0+16);
    puts("XX                           XX\n");
    gotoxy(x0,y0+17);
    puts("X/                           \\X\n");
    gotoxy(x0,y0+18);
    puts("*******************************\n");

    gotoxy(x0+5,y0+2);
    printf("Title: ");
    fflush(stdin);
    gets(title);
    strcpy(e.title, title);

    do{
        gotoxy(x0+5,y0+4);
        printf("Date: ");
        fflush(stdin);
        scanf("%d/%d/%d", &DD, &MM, &AAAA);
    }while(!validDate(DD, MM, AAAA, 55, 10));

    e.date.DD = DD;
    e.date.MM = MM;
    e.date.AAAA = AAAA;

    do{
        gotoxy(x0+5,y0+6);
        printf("Time: ");
        fflush(stdin);
        scanf("%d:%d", &hh, &mm);
    }while(!validTime(hh, mm, 55, 12));

    e.date.hh = hh;
    e.date.mm = mm;

    color(7);
    strcpy(e.category, chooseCat(x0+5,y0+8));

    e.activo = eventActive(x0+3,y0+15);

    return e;
}

void loadEvent(node **head, char *username)
{
    node *temp = newNode(insertEvent(*head, username));
    addToHead(head, temp);
}

int chooseEvent(node *head)
{
    int idEvent;

    do{
        gotoxy(50,27);
        printf("Seleccione un evento: ");
        fflush(stdin);
        scanf("%d", &idEvent);
    }while(idEvent < 1 || idEvent >= newEventPos(head));

    return idEvent;
}

void modifyEventMenu(event e)
{
    int x0=26, y0=6;

    system("cls");

    gotoxy(x0,y0);
    puts("X******************************************************************X\n");
    gotoxy(x0,y0+1);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+2);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+3);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+4);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+5);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+6);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+7);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+8);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+9);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+10);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+11);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+12);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+13);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+14);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+15);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+16);
    puts("XX                                                                XX\n");
    gotoxy(x0,y0+17);
    puts("X/                                                                \\X\n");
    gotoxy(x0,y0+18);
    puts("********************************************************************\n");

    prtEvent(e,x0+12,y0+8);

    gotoxy(x0+36,y0+4);
    printf("Modificar:");
    gotoxy(x0+36,y0+6);
    printf(" 1) Titulo");
    gotoxy(x0+36,y0+7);
    printf(" 2) Fecha");
    gotoxy(x0+36,y0+8);
    printf(" 3) Hora");
    gotoxy(x0+36,y0+9);
    printf(" 4) Categoria");
    gotoxy(x0+36,y0+10);
    if(e.activo)
        printf(" 5) Cambiar a inactivo");
    else
        printf(" 5) Cambiar a activo");
    gotoxy(x0+36,y0+11);
    printf(" 0) Borrar evento");
    gotoxy(x0+36,y0+13);
    printf("ESC) Atras");
}

void modTitle(event *e)
{
    printf("Nuevo titulo: ");
    fflush(stdin);
    scanf("%s", e->title);
}

void modDate(event *e)
{
    int AAAA, MM, DD;
    do{
        gotoxy(38,21);
        printf("Nueva fecha: ");
        fflush(stdin);
        scanf("%d/%d/%d", &DD, &MM, &AAAA);
    }while(!validDate(DD, MM, AAAA, 51, 21));
    e->date.DD = DD;
    e->date.MM = MM;
    e->date.AAAA = AAAA;
}

void modHour(event *e)
{
    int hh, mm;
    do{
        gotoxy(38,21);
        printf("Nueva hora: ");
        fflush(stdin);
        scanf("%d:%d", &hh, &mm);
    }while(!validTime(hh, mm, 50, 21));

    e->date.hh = hh;
    e->date.mm = mm;
}

void modCategory(event *e)
{
    strcpy(e->category, chooseCat(38,17));
}

int delEvent()
{
    char input;
    int borrar;
    printf("Borrar evento? (s/n): ");
    fflush(stdin);
    scanf("%c", &input);
    if(input=='s')
        borrar=1;
    else
        borrar=0;

    return borrar;
}

int modDelete(node **head, int id)
{
    int borrar=0;

    if(delEvent())
    {
        borrar=1;
        deleteEvent(head, id);
    }

    return borrar;
}

void modifyEvent(node **head)
{
    int x0=38, y0=21;
    if(*head)
    {
        char input;
        prtEvents(*head);
        int id=chooseEvent(*head);
        node *temp = findEvent(*head, id);
        do
        {
            color(7);
            modifyEventMenu(temp->value);
            input=getch();
            switch(input)
            {
            case 48:
                gotoxy(x0,y0);
                if(modDelete(head, id))
                {
                    input=ESC;
                    redefId(*head);
                }
                break;
            case 49:
                gotoxy(x0,y0);
                modTitle(&temp->value);
                break;
            case 50:
                modDate(&temp->value);
                break;
            case 51:
                modHour(&temp->value);
                break;
            case 52:
                gotoxy(x0,y0);
                modCategory(&temp->value);
                break;
            case 53:
                if(temp->value.activo)
                    temp->value.activo=false;
                else
                    temp->value.activo=true;
                break;
            }
        }
        while(input!=ESC);
    }
    else
    {
        printf("\nNo hay eventos cargados...");
        getch();
    }

}

/*******************************
       PRINTING FUNCTIONS
*******************************/

void prtEvent(event e, int x, int y)
{
    int c;

    switch(e.activo)
    {
    case 1:
        c=colorByCategory(e);
        break;
    case 0:
        c=4;
        break;
    }

    color(c);
    gotoxy(x,y);
    printf("%s", e.title);
    color(c);
    gotoxy(x,y+1);
    printf("%02d/%02d/%02d", e.date.DD, e.date.MM, e.date.AAAA);
    color(c);
    gotoxy(x,y+2);
    printf("%02d:%02d", e.date.hh, e.date.mm);
}

void prtEvents(node *head)
{
    int i=1, x=5, y=4;
    while(head)
    {
        gotoxy(x-3,y);
        color(15);
        printf("%d", head->value.id);
        gotoxy(x,y);
        prtEvent(head->value, x, y);
        i++;
        x+=20;
        if(i==7)
        {
            i=1;
            x=5;
            y+=4;
        }

        head = head->next;
    }

    printf("\n");
}

void prtEventRedux(event e, int x, int y)
{
    int c;
    c=colorByCategory(e);

    color(7);
    gotoxy(x-3,y);
    printf("%d",e.id);
    color(c);
    gotoxy(x,y);
    printf("%s",e.title);
    gotoxy(x,y+1);
    printf("%02d:%02d",e.date.hh,e.date.mm);
    gotoxy(x,y+2);
    printf("%s",e.category);
    gotoxy(x,y+3);
}

int colorByCategory(event e) ///===> DETERMINA EL COLOR CON EL CUAL SE REPRESENTAN LAS DISTINTAS CATEGORIAS
{
    char cats[][CAT_LENGTH]= {"Trabajo","Hogar","Estudio","Cumpleaños","Personal"};
    int color;

    if(e.activo)
    {
        if(strcmp(e.category,cats[0])==0)
            color=1;
        if(strcmp(e.category,cats[1])==0)
            color=2;
        if(strcmp(e.category,cats[2])==0)
            color=5;
        if(strcmp(e.category,cats[3])==0)
            color=6;
        if(strcmp(e.category,cats[4])==0)
            color=7;
    }
    else
    {
        color=4;
    }

    return color;
}

/// FUNCION PARA CONTAR EVENTOS POR CATEGORIA
int countByCategoryAndDay (node * eventList, char category[], struct tm t)
{
    int result=0;

    while (eventList!=NULL)
    {
        if ((strcmpi(eventList->value.category,category)==0) && (eventList->value.date.AAAA==t.tm_year+1900) && (eventList->value.date.MM==t.tm_mon+1) && (eventList->value.date.DD==t.tm_mday) && (eventList->value.activo==1))
            result++;

        eventList=eventList->next;
    }

    return result;
}
