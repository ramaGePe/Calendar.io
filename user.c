#include "user.h"


/// TREE LIBRARY FUNCTIONS

void initTree(treeNode **head)
{
	(*head) = NULL;
}

treeNode *newTreeNode(user val)
{
	treeNode *temp = (treeNode*)malloc(sizeof(treeNode));

	temp->val = val;
    initList(&temp->eventList);
	temp->right = NULL;
	temp->left = NULL;

	return temp;
}

treeNode *findFromUsername(treeNode *root, char *username) //==> ??
{
    treeNode *temp = NULL;

    if(root)
    {
        if(strcmp(root->val.username, username)==0)
            temp = root;
        else
        {
            if(strcmp(root->val.username, username)>0)
                temp = findFromUsername(root->left, username);
            if(strcmp(root->val.username, username)<0)
                temp = findFromUsername(root->right, username);
        }
    }

    return temp;
}

void insertTreeNode(treeNode **root, treeNode *newNode)
{
    if(!(*root))
    {
        (*root) = newNode;
    }else
    {
        if(strcmp((*root)->val.username, newNode->val.username)<0)
            insertTreeNode(&(*root)->right, newNode);

        if(strcmp((*root)->val.username, newNode->val.username)>0)
            insertTreeNode(&(*root)->left, newNode);
    }
}

user insertUser()
{
    user u;

    printf("\nUsername: ");
    fflush(stdin);
    scanf("%s", u.username);
    // Valid Input...?
    printf("\nPassword: ");
    fflush(stdin);
    scanf("%s", u.password);
    // Valid Input...?

    return u;
}

void loadUser(treeNode **root)
{
    treeNode *temp = newTreeNode(insertUser());
    insertTreeNode(root, temp);
}

int countNodes(treeNode *root)
{
    int count=0;

    if(root)
    {
        count++;
        count += countNodes(root->right);
        count += countNodes(root->left);
    }

    return count;
}

treeNode *rightestNode(treeNode *root)
{
    treeNode *temp = NULL;

    if(root)
    {
        temp = root;

        if(root->right)
            temp = rightestNode(root->right);
    }

    return temp;
}

treeNode *leftestNode(treeNode *root)
{
    treeNode *temp = NULL;

    if(root)
    {
        temp = root;

        if(root->left)
            temp = leftestNode(root->left);
    }

    return temp;
}

void deleteTreeNode(treeNode **root, char *username)
{
    if(*root)
    {
        if(strcmp((*root)->val.username, username) == 0)
        {
            if((*root)->left)
            {
                treeNode *temp = rightestNode((*root)->left);
                (*root)->val = temp->val;
                deleteTreeNode(&(*root)->left, temp->val.username);
            }else if((*root)->right)
            {
                treeNode *temp = leftestNode((*root)->right);
                (*root)->val = temp->val;
                deleteTreeNode(&(*root)->right, temp->val.username);
            }else
            {
                free(*root);
                (*root) = NULL;
            }
        }else
        {
            if(strcmp((*root)->val.username, username) < 0)
                deleteTreeNode(&(*root)->right, username);

            else if(strcmp((*root)->val.username, username) > 0)
                deleteTreeNode(&(*root)->left, username);
        }
    }
}

void deleteTree(treeNode **root)
{
    if(*root)
    {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        deleteTreeNode(root, (*root)->val.username);
    }
}

int treeHeight(treeNode *root)
{
    int height = 0;

    if(root)
        height = 1 + maxx(treeHeight(root->right), treeHeight(root->left));

    return height;
}

int treeIsBalanced(treeNode *root)
{
    int flag=1;

    if(root)
    {
        if(diff(treeHeight(root->right), treeHeight(root->left))>1)
        {
            flag=0;
        }
    }

    return flag;
}

int treeToArray(treeNode *root, user *users, int i)
{
    if(root)
    {
        i=treeToArray(root->left, users, i);
        users[i]=root->val;
        i++;
        i=treeToArray(root->right, users, i);
    }

    return i;
}

user *genArray(int len)
{
    return (user*)malloc(sizeof(user)*len);
}

void arrayToTree(treeNode **root, user *users, int start, int end)
{
    if(start <= end)
    {
        int mid = (start + end)/2;
        insertTreeNode(root, newTreeNode(users[mid]));
        arrayToTree(&(*root)->left, users, start, mid-1);
        arrayToTree(&(*root)->right, users, mid+1, end);
    }
}

void balanceTree(treeNode **root)
{
    if(*root && !treeIsBalanced(*root))
    {
        user *users = genArray(countNodes(*root));
        int qNodes = treeToArray(*root, users, 0);
        deleteTree(root);
        arrayToTree(root, users, 0, qNodes-1);
    }
}

void forceBalanceTree(treeNode **root)
{
    if(*root)
    {
        user *users = genArray(countNodes(*root));
        int qNodes = treeToArray(*root, users, 0);
        deleteTree(root);
        arrayToTree(root, users, 0, qNodes-1);
    }
}


/// USERS SPECIFIC FUNCTIONS

char *checkUserLog(treeNode *root, char *username, char *password)
{
    char *temp = NULL;

    if(root)
    {
        if(strcmp(root->val.username, username)==0 && strcmp(root->val.password, password)==0)
            temp = root->val.username;
        else
        {
            if(strcmp(root->val.username, username)>0)
                temp = checkUserLog(root->left, username, password);
            if(strcmp(root->val.username, username)<0)
                temp = checkUserLog(root->right, username, password);
        }
    }

    return temp;
}

void insertLogIn(char *username, char *password)
{
    printf("\nUsername: ");
    fflush(stdin);
    scanf("%s", username);
    printf("\nPassword: ");
    fflush(stdin);
    scanf("%s", password);
}

char *logIn(treeNode *root)
{
    char username[USER_LENGTH], password[PASS_LENGTH];

    insertLogIn(username,password);

    return checkUserLog(root, username, password);
}

char *genPassword()
{
    char *password=(char*)malloc(sizeof(char)*PASS_LENGTH);
    printf("\nNuevo password: ");
    fflush(stdin);
    scanf(" %s", password);
    // Valid Input...?

    return password;
}

void changePassword(char *password)
{
    char *newPassword = genPassword();
    strcpy(password, newPassword);
}

int confirmDelete()
{
    int flag=0;
    char input;
    printf("\nSe perderan todos los datos de forma permanente\n");
    printf("\nEliminar cuenta? (s/n): ");
    fflush(stdin);
    scanf(" %c", &input);

    if(input==115)
        flag=1;

    return flag;
}

int deleteUser(treeNode **root, char *username)
{
    int delete=confirmDelete();

    if(delete)
    {
        deleteTreeNode(root, username);
    }

    return delete;
}

void usersToFile(treeNode *root, FILE *pFile)
{
    if(root)
    {
        fwrite(&root->val, sizeof(user), 1, pFile);
        usersToFile(root->left, pFile);
        usersToFile(root->right, pFile);
    }
}

void pushUsers(char *file, treeNode *root)
{
    FILE *pFile = fopen(file, "wb");

    if(pFile)
    {
        usersToFile(root, pFile);
        fclose(pFile);
    }
}

void pullUsers(char *file, treeNode **root)
{
    FILE *pFile = fopen(file, "rb");
    user u;

    if(pFile)
    {
        while(fread(&u, sizeof(u), 1, pFile)>0)
        {
            insertTreeNode(root, newTreeNode(u));
        }

        fclose(pFile);
    }
}

void eventsToFile(treeNode *root, FILE *pFile)
{
    if(root)
    {
        while(root->eventList)
        {
            fwrite(&root->eventList->value, sizeof(event), 1, pFile);
            root->eventList = root->eventList->next;
        }
        eventsToFile(root->left, pFile);
        eventsToFile(root->right, pFile);
    }
}

void pushEvents(char *file, treeNode *root)
{
    FILE *pFile = fopen(file, "wb");

    if(pFile)
    {
        eventsToFile(root, pFile);
        fclose(pFile);
    }
}

void pullEvents(char *file, treeNode **root)
{
    FILE *pFile = fopen(file, "rb");
    event e;

    if(pFile)
    {
        while(fread(&e, sizeof(e), 1, pFile)>0)
        {
            addToHead(&findFromUsername(*root, e.username)->eventList, newNode(e));
        }

        fclose(pFile);
    }
}

void pullData(char *usrFile, char *eveFile, treeNode **root)
{
    pullUsers(usrFile, root);
    pullEvents(eveFile, root);
}

void pushData(char *usrFile, char *eveFile, treeNode *root)
{
    pushUsers(usrFile, root);
    pushEvents(eveFile, root);
}

// ====> PRINTING FUNCTIONS <==== //

void prtUser(user u)
{
    printf("\nUsername: %s", u.username);
    printf("\nPassword: %s", u.password);
    printf("\n-----------------------");
}

void prtPreOrder(treeNode *root)
{
    if(root)
    {
        prtUser(root->val);
        prtPreOrder(root->left);
        prtPreOrder(root->right);
    }
}

void prtInOrder(treeNode *root)
{
    if(root)
    {
        prtInOrder(root->left);
        prtUser(root->val);
        prtInOrder(root->right);
    }
}

void prtPostOrder(treeNode *root)
{
    if(root)
    {
        prtPostOrder(root->left);
        prtPostOrder(root->right);
        prtUser(root->val);
    }
}

void prtUtil(treeNode *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    prtUtil(root->right, space);
    printf("\n");

    for (int i = 10; i < space; i++)
        printf(" ");

    printf("%s\n", root->val.username);
    prtUtil(root->left, space);
}

void prtTree(treeNode *root)
{
   prtUtil(root, 0);
}

void prtFile(char *file)
{
    FILE *pFile = fopen(file, "rb");
    user u;

    if(pFile)
    {
        while(fread(&u, sizeof(u), 1, pFile))
        {
            prtUser(u);
        }

        fclose(pFile);
    }
}
