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

    return e;
}

void loadEvent(node **head, char *username)
{
    node *temp = newNode(insertEvent(*head, username));
    addToHead(head, temp);
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
       PRINTING FUNCTIONS
*******************************/

void prtEvent(event e)
{
    printf("\nID.....: %d", e.id);
    printf("\nTitle..: %s", e.title);
    printf("\nDate...: %02d/%02d/%02d", e.date.DD, e.date.MM, e.date.AAAA);
    printf("\nTime...: %02d:%02d", e.date.hh, e.date.mm);
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
