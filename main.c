#include "main.h"

int main()
{
    setlocale(LC_ALL,"");

	treeNode *root;
	char input;

	initTree(&root);
	pullData(uFile, eFile, &root);

    system("cls");
    UIintro();
    Sleep(1500);

	do {
		UIheader();
		mainMenu();
		input = getch();
		switch (input)
		{
        /// LOGIN
		case 49:
			system("cls");
			userLogIn(&root);
			break;
        /// CREAR USUARIO
		case 50:
			system("cls");
			loadUser(&root);
			balanceTree(&root);
			break;
        /// IMPRIME ARBOL
		case 51:
			system("cls");
			prtTree(root);
			getch();
			break;
		default:
			break;
		}

	} while (input != ESC);

	pushData(uFile, eFile, root);

	return 0;
}

/// MENU USUARIO
void userInMenu(treeNode **root, char *userLog)
{
    char input;
    treeNode *temp = findFromUsername(*root, userLog);

    do {
        system("cls");
        UIheader();
        UIcalendarTable(temp);
        userMenu();
        input = getch();
        switch (input)
        {
        case 49:
            /// CARGAR EVENTO
            system("cls");
            loadEvent(&temp->eventList, userLog);
            break;
        case 50:
            /// MODIFICAR EVENTO
            system("cls");
            modifyEvent(&temp->eventList);
            break;
        case 101:
            /// IMPRIME EVENTOS
            system("cls");
            UIheader();
            prtEvents(temp->eventList);
            getch();
            break;
        case 113:
            /// VISTA DIARIA
            system("cls");
            UIheader();
            UIdaily(temp);
            break;
        case 51:
            /// PERFIL
            system("cls");
            input = userProfile(root, userLog);
            break;
        default:
            break;
        }
    } while (input != ESC);

    logOutMessage();
}

/// DATOS GENERALES DE ADMIN
void adminData(treeNode *root)
{
    color(sec_color);
    gotoxy(27, 16);
    printf("Usuarios activos: ");
    color(main_color);
    gotoxy(45, 16);
    printf("%d", countNodes(root));
    color(sec_color);
    gotoxy(28, 18);
    printf("Eventos creados: ");
    color(main_color);
    gotoxy(45, 18);
    printf("%d", countAllEvents(root));
}

/// PERMITE AL ADMIN ACCESO A CUALQUIER CUENTA
void accessAnyUser(treeNode **root)
{
    char username[USER_LENGTH];

    gotoxy(50,21);
    printf("Username: ");
    fflush(stdin);
    scanf("%s", username);

    treeNode *userLog = findFromUsername(*root, username);

    if(userLog)
        userInMenu(root, username);
    else
    {
        color(sec_color);
        gotoxy(50,23);
        printf("Usuario inexistente...");
        Sleep(2000);
        color(main_color);
    }
}

/// MENU ADMIN
void adminInMenu(treeNode **root)
{
    char input;

    do{
        system("cls");
        UIheader();
        dragonKing();
        adminLogo();
        adminData(*root);
        adminMenu();
        input=getch();
        switch(input)
        {
        case 49:
            accessAnyUser(root);
            break;
        case 50:
            system("cls");
            prtInOrder(*root);
            getch();
            break;
        case 51:
            system("cls");
            prtTree(*root);
            getch();
            break;
        default:
            break;
        }
    }while(input!=ESC);
}

/// FUNCION DE LOGUEO
void userLogIn(treeNode **root)
{
	char *userLog = logIn(*root);

	if (userLog)
    {
        if(strcmp(userLog, ADMIN_USER)==0)
        {
            logInMessage();
            adminInMenu(root);
        }else
        {
            logInMessage();
            userInMenu(root, userLog);
        }
    }else
    {
		logInErrorMessage();
    }
}

/// MENU DE PERFIL/MODIFICACION DE USUARIO
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
