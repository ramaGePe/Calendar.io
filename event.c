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

node *findTail(node *head)
{
    node *tail = head;

    if(tail)
    {
        while(tail->next)
        {
            tail = tail->next;
        }
    }

    return tail;
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

int eventExists(node *head, int id)
{
    int flag = 0;

    if(head)
    {
        while(head && head->value.id != id)
        {
            head = head->next;
        }

        if(head && head->value.id == id)
        {
            flag = 1;
        }
    }

    return flag;
}

void addToTail(node **head, node *newNode)
{
    if(!(*head))
    {
        *head = newNode;
    }else
    {
        node *tail = findTail(*head);
        tail->next = newNode;
    }
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

void addInOrder(node **head, node *newNode)
{
    if(*head == NULL)
    {
        *head = newNode;
    }else
    {
        if(*head && newNode->value.id <= (*head)->value.id)
        {
            newNode->next = (*head);
            (*head) = newNode;
        }else
        {
            node *temp = (*head);
            node *prev;

            while(temp && temp->value.id <= newNode->value.id)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = newNode;
            newNode->next = temp;
        }
    }
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

void deleteHead(node **head)
{
    if(*head)
    {
        node *temp = (*head);
        (*head) = (*head)-> next;
        free(temp);
    }
}

void deleteTail(node **head)
{
    if(*head)
    {
        if((*head)->next == NULL)
        {
            node *temp = (*head);
            (*head) = (*head)->next;
            free(temp);
        }else
        {
            node *temp = (*head);
            node *prev;

            while(temp->next)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = NULL;
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

char *chooseCat()
{
    char input, cats[][10]={"Personal", "Trabajo", "Estudio", "Hogar", "Cumpleaños"};
    char *cat = (char*)malloc(sizeof(char)*CAT_LENGTH);

    printf("\nCategoria:");
    printf("\n 1) Personal");
    printf("\n 2) Trabajo");
    printf("\n 3) Estudio");
    printf("\n 4) Hogar");
    printf("\n 5) Cumpleaños");

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

int eventActive()
{
    char input;
    bool active;

    printf("\n\nMarcar como activo? (s/n)");
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

event insertEvent(node *head, char *username)
{
    char title[TITLE_LENGTH];
    int AAAA, MM, DD, hh, mm;
    event e;

    e.id = newEventPos(head);

    strcpy(e.username, username);

    printf("\nTitle: ");
    fflush(stdin);
    scanf(" %s", title);
    // Verify input..?
    strcpy(e.title, title);

    printf("\nDate: ");
    fflush(stdin);
    scanf("%d/%d/%d", &DD, &MM, &AAAA);
    // Verify input..?
    e.date.DD = DD;
    e.date.MM = MM;
    e.date.AAAA = AAAA;

    printf("\nTime: ");
    fflush(stdin);
    scanf("%d:%d", &hh, &mm);
    // Verify input..?
    e.date.hh = hh;
    e.date.mm = mm;

    strcpy(e.category, chooseCat());

    e.activo = eventActive();

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
        printf("\nSeleccione un evento: ");
        fflush(stdin);
        scanf("%d", &idEvent);
    }while(idEvent < 1 || idEvent >= newEventPos(head));

    return idEvent;
}

void modifyEventMenu(event e)
{
    system("cls");
    prtEvent(e);
    printf("\n\nModificar:\n");
    printf("\n 1) Titulo");
    printf("\n 2) Fecha");
    printf("\n 3) Hora");
    printf("\n 4) Categoria");
    if(e.activo)
        printf("\n 5) Cambiar a inactivo");
    else
        printf("\n 5) Cambiar a activo");
    printf("\n\n 0) Borrar evento");
    printf("\n\nESC) Atras");
}

void modTitle(event *e)
{
    printf("\nNuevo titulo: ");
    fflush(stdin);
    scanf("%s", e->title);
}

void modDate(event *e)
{
    int AAAA, MM, DD;
    printf("\nNueva fecha: ");
    fflush(stdin);
    scanf("%d/%d/%d", &DD, &MM, &AAAA);
    // Valid input..??
    e->date.DD = DD;
    e->date.MM = MM;
    e->date.AAAA = AAAA;
}

void modHour(event *e)
{
    int hh, mm;
    printf("\nNueva hora: ");
    fflush(stdin);
    scanf("%d:%d", &hh, &mm);
    // Valid input..?
    e->date.hh = hh;
    e->date.mm = mm;
}

void modCategory(event *e)
{
    strcpy(e->category, chooseCat());
}

int delEvent()
{
    char input;
    int borrar;
    printf("\n\nBorrar evento? (s/n)");
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
    if(*head)
    {
        char input;
        prtEvents(*head);
        int id=chooseEvent(*head);
        node *temp = findEvent(*head, id);
        do{
            modifyEventMenu(temp->value);
            input=getch();
            switch(input)
            {
            case 48:
                if(modDelete(head, id))
                {
                    input=ESC;
                    redefId(*head);
                }
                break;
            case 49:
                modTitle(&temp->value);
                break;
            case 50:
                modDate(&temp->value);
                break;
            case 51:
                modHour(&temp->value);
                break;
            case 52:
                modCategory(&temp->value);
                break;
            case 53:
                if(temp->value.activo)
                    temp->value.activo=false;
                else
                    temp->value.activo=true;
                break;
            }
        }while(input!=ESC);
    }else{
        printf("\nNo hay eventos cargados...");
        getch();
    }

}

/*******************************
       PRINTING FUNCTIONS
*******************************/

void prtEvent(event e)
{
    printf("\nID.........: %d", e.id);
    printf("\nTitulo.....: %s", e.title);
    printf("\nFecha......: %02d/%02d/%02d", e.date.DD, e.date.MM, e.date.AAAA);
    printf("\nHora.......: %02d:%02d", e.date.hh, e.date.mm);
    printf("\nCategoria..: %s", e.category);
    printf("\nActivo.....: %d", e.activo);
    printf("\n-----------------------");
}

void prtEvents(node *head)
{
    printf("\n");

    while(head)
    {
        prtEvent(head->value);
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
        if ((strcmpi(eventList->value.category,category)==0) && (eventList->value.date.AAAA==t.tm_year+1900) && (eventList->value.date.MM==t.tm_mon+1) && (eventList->value.date.DD==t.tm_mday))
            result++;

        eventList=eventList->next;
    }

    return result;
}







