#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#define eFile "events.dat"

#define TITLE_LENGTH 20
#define USERNAME_LENGTH 20
#define CAT_LENGTH 20

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

void initList(node **head);
node *newNode(event value);
void addToHead(node **head, node *newNode);
node *findTail(node *head);
void addToTail(node **head, node *newNode);
node *findEvent(node *head, int id);
int eventExists(node *head, int id);
void deleteEvent(node **head, int id);
void deleteHead(node **head);
void deleteTail(node **head);
void addInOrder(node **head, node *newNode);
int sumValues(node *head);
void deleteList(node **head);
void fileToList(char *file, node **head, void(*add)(node**,node*));
node *fusionLists(node **head, node **lista, node *fusion);

void loadEvent(node **head, char *username);
void modifyEvent(node **head);

void prtEvent(event e);
void prtEvents(node *head);

