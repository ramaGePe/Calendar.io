#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define eFile "events.dat"

#define TITLE_LENGTH 20
#define USERNAME_LENGTH 20
#define CAT_LENGTH 20

#ifndef EVENT_H
#define EVENT_H

#define ESC 27

typedef struct
{
	int AAAA, MM, DD, hh, mm;
}Date;

typedef struct
{
	int id;
	char username[USERNAME_LENGTH];
	char title[TITLE_LENGTH];
	Date date;
	char category[CAT_LENGTH];
	int activo;
} event;

typedef struct _node
{
	event value;
	struct _node *next;
} node;

// LISTS LIB FUNCTIONS
void initList(node **head);
node *newNode(event value);
void addToHead(node **head, node *newNode);
int countListNodes(node *head);
void deleteEvent(node **head, int id);
void deleteList(node **head);

// EVENT SPEC FUNCTIONS
void loadEvent(node **head, char *username);
void modifyEvent(node **head);

// PRINTING FUNCTIONS
void prtEvent(event e);
void prtEvents(node *head);

int countByCategoryAndDay (node * eventList, char category[], struct tm t);
void prtEventRedux(event e, int x, int y);
int colorByCategory(event e);


#endif // EVENT_H



