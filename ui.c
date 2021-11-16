#include "ui.h"

void logOutMessage()
{
	printf("\nCERRANDO SESION...\n");
	Sleep(2000);
}

void logInMessage()
{
	printf("\nINICIANDO SESION...\n");
	Sleep(2000);
}

void logInErrorMessage()
{
	printf("\nUSUARIO O PASSWORD INCORRECTA...\n");
	Sleep(2000);
}

void userExistsMessage()
{
    printf("\nNombre de usuario ya existente! Elije otro...\n");
    Sleep(2000);
}

void mainMenu()
{
	system("cls");
	printf("\nCALENDAR.IO\n");
	printf("\n 1) Log in");
	printf("\n 2) Crear usuario");
	printf("\n 3) Lista usuarios");
	printf("\n 4) Ver Arbol");
	printf("\n\n  ESC) Salir\n");
}

void userMenu()
{
	system("cls");
	printf("\nCALENDAR.IO\n");
	printf("\n 1) Crear evento");
	printf("\n 2) Ver eventos");
	printf("\n 3) Perfil");
	printf("\n\n  ESC) Salir\n");
}

void profileMenu(user u)
{
	system("cls");
	printf("\nCALENDAR.IO\n");
	prtUser(u);
	printf("\n 1) Cambiar password");
	printf("\n 2) Borrar cuenta");
	printf("\n\n  ESC) Atras\n");
}
