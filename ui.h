#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "user.h"

#ifndef UI_H
#define UI_H

void logOutMessage();
void logInMessage();
void logInErrorMessage();
void userExistsMessage();
void color(int c);
void UIintro();
void UIcalendarTable();
void mainMenu();
void userMenu();
void profileMenu(user u);

#endif // UI_H
