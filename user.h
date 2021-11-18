#include "event.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define uFile "users.dat"

#define USER_LENGTH 20
#define PASS_LENGTH 20
#define ADMIN_USER "admin"
#define ADMIN_PASS "abc123"

#ifndef USER_H
#define USER_H

typedef struct
{
	char username[USER_LENGTH];
	char password[PASS_LENGTH];
}user;

typedef struct t_node
{
	user val;
	node *eventList;
	struct t_node *left;
	struct t_node *right;
}treeNode;

// ABB LIBRARY FUNCIONTS
void initTree(treeNode **head);
treeNode *newTreeNode(user val);
treeNode *findFromUsername(treeNode *root, char *username);
void insertTreeNode(treeNode **root, treeNode *newNode);
int countNodes(treeNode *root);
treeNode *rightestNode(treeNode *root);
treeNode *leftestNode(treeNode *root);
void deleteTreeNode(treeNode **root, char *username);
void deleteTree(treeNode **root);
void balanceTree(treeNode **root);
void forceBalanceTree(treeNode **root);

// USER SPECIFIC FUNCTIONS
void loadUser(treeNode **root);
char *logIn(treeNode *root);
void changeUsername(treeNode *root, char *username);
void changePassword(char *password);
int deleteUser(treeNode **root, char *username);
void pullData(char *usrFile, char *eveFile, treeNode **root);
void pushData(char *usrFile, char *eveFile, treeNode *root);
int countAllEvents(treeNode *root);

// PRINTING FUNCTIONS
void prtUser(user u);
void prtInOrder(treeNode *root);
void prtTree(treeNode *root);

#endif // USER_H
