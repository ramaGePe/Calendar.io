#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include "ui.h"

#ifndef MAIN_H
#define MAIN_H

void mainMenu();
void userMenu();
void findUser(treeNode *root);
void userLogIn(treeNode **root);
char userProfile(treeNode **root, char *username);

#endif // MAIN_H
