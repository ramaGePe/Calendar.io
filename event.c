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

char *chooseCat()
{
    char input, cats[][10]={"Personal", "Trabajo", "Estudio"};
    char *cat = (char*)malloc(sizeof(char)*10);

    printf("\nCategoria:");
    printf("\n 1) Personal");
    printf("\n 2) Trabajo");
    printf("\n 3) Estudio");

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
    }

    return cat;
}

int eventActive()
{
    char input;
    bool active;

    printf("\nMarcar como activo? (s/n)");
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

    if(head)
        e.id = findTail(head)->value.id + 1;
    else
        e.id = 1;

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

void modifyEvent(node **head)
{
    prtEvents(*head);
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








/// FUNCION PARA CONTAR EVENTOS POR CATEGORIA
int countByCategoryAndDay (node * eventList, char * category, struct tm t)
{
    int result=0;

    while (eventList!=NULL)
    {
        if ((strcmpi(eventList->value.category,category)==0) && (eventList->value.date.AAAA==t.tm_year) && (eventList->value.date.MM==t.tm_mon) && (eventList->value.date.DD==t.tm_mday))
            result++;

        eventList=eventList->next;
    }

    return result;
}







