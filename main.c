#include "main.h"

int main()
{
	treeNode *root;
	char input;

	initTree(&root);
	pullData(uFile, eFile, &root);

	do {
		mainMenu();
		input = getch();
		switch (input)
		{
		case 49:
			system("cls");
			userLogIn(&root);
			break;
		case 50:
			system("cls");
			loadUser(&root);
			balanceTree(&root);
			break;
		case 51:
			system("cls");
			prtInOrder(root);
			getch();
			break;
		case 52:
			system("cls");
			prtTree(root);
			getch();
			break;
		case 53:
			system("cls");
			prtFile(uFile);
			getch();
		default:
			break;
		}

	} while (input != ESC);

	pushData(uFile, eFile, root);

	return 0;
}

void userLogIn(treeNode **root)
{
	char input;
	char *userLog = logIn(*root);

	if (userLog)
	{
		logInMessage();
		treeNode *temp = findFromUsername(*root, userLog);
		do {
			userMenu();
			input = getch();
			switch (input)
			{
			case 49:
				system("cls");
				loadEvent(&temp->eventList, userLog);
				break;
			case 50:
				system("cls");
				prtEvents(temp->eventList);
				getch();
				break;
			case 51:
				input = userProfile(root, userLog);
				break;
			default:
				break;
			}
		} while (input != ESC);
	} else
		logInErrorMessage();
}

char userProfile(treeNode **root, char *username)
{
	char input;
	int deleted = 0;
	treeNode *temp = findFromUsername(*root, username);

	do {
		profileMenu(temp->val);
		input = getch();
		switch (input)
		{
		case 49:
			changePassword(temp->val.password);
			break;
		case 50:
			deleted = deleteUser(root, temp->val.username);
			break;
		default:
			break;
		}
	} while (input != ESC && !deleted);

	if (deleted)
	{
		logOutMessage();
		input = ESC;
	} else
		input = 0;

	return input;
}