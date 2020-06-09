#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
struct Tree
{
    int info;
    struct Tree *left, *right;
} *root = NULL, *Loc, *par;

void findloc(int item, int s)
{
    char c[1000] = "Root", a[] = "->Left", b[] = "->Right";
    struct Tree *save = (struct Tree *)malloc(sizeof(struct Tree));
    struct Tree *ptr = (struct Tree *)malloc(sizeof(struct Tree));
    if (item == (root->info))
    {
        printf(c);
        Loc = root;
        par = NULL;
        goto label;
    }
    if ((root->info) < item)
    {
        strcat(c, b);
        save = root;
        ptr = root->right;
    }
    else
    {
        strcat(c, a);
        save = root;
        ptr = root->left;
    }
    while (ptr != NULL)
    {
        if ((ptr->info) == item)
        {
            par = save;
            Loc = ptr;
            break;
        }
        else if ((ptr->info) < item)
        {
            strcat(c, b);
            save = ptr;
            ptr = ptr->right;
        }
        else
        {
            strcat(c, a);
            save = ptr;
            ptr = ptr->left;
        }
    }
    if (s == 1)
        printf(c);
label:
    if (ptr == NULL)
    {
        par = save;
    }
}

void insertion(int item)
{
    // struct Tree *new_branch=(struct Tree*)malloc(sizeof(structTree)) ;
if (root == NULL)
{
    struct Tree *new_branch = (struct Tree *)malloc(sizeof(struct Tree));
    new_branch->info = item;
    new_branch->left = NULL;
    new_branch->right = NULL;
    root = new_branch;
}
else
{
    struct Tree *new_branch = (struct Tree *)malloc(sizeof(struct
                                                           Tree));
    new_branch->info = item;
    new_branch->left = NULL;
    new_branch->right = NULL;
    findloc(item, 0);
    if (item > (par->info))
        par->right = new_branch;
    else
        par->left = new_branch;
    // free(new_branch);
}
}
void Inorder(struct Tree *Tree)
{
    if (Tree == NULL)
        return;
    Inorder(Tree->left);
    printf(" %d ", Tree->info);
    Inorder(Tree->right);
}
void Preorder(struct Tree *Tree)
{
    if (Tree == NULL)
        return;
    printf(" %d ", Tree->info);
    Preorder(Tree->left);
    Preorder(Tree->right);
}
void Postorder(struct Tree *Tree)
{
    if (Tree == NULL)
        return;
    Postorder(Tree->left);
    Postorder(Tree->right);
    printf(" %d ", Tree->info);
}
void display()
{
    int ch;
    printf("\n Enter your mode of display : \n 1.Inorder(Ascending Order) \n 2.Preorder \n 3.Postorder : ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        Inorder(root);
        break;
    case 2:
        Preorder(root);
        break;
    case 3:
        Postorder(root);
        break;
    default:
        printf("\n Invalid choice . ");
        break;
    }
}
Tree *deletion(Tree *root, int item)
{
    if (root == NULL)
    {
        printf("\n Tree is empty .");
        return root;
    }
    if ((root->info) > item)
    {
        root->left = deletion(root->left, item);
        return root;
    }
    else if ((root->info) < item)
    {
        root->right = deletion(root->right, item);
        return root;
    }
    struct Tree *new_branch = (struct Tree *)malloc(sizeof(struct Tree));
    new_branch->info = item;
    new_branch->left = NULL;
    new_branch->right = NULL;
    //case A:if one child is empty or both
    if ((root->left) == NULL)
    {
        new_branch = root->right;
        root = NULL;
        root = new_branch;
        return new_branch;
    }
    else if ((root->right) == NULL)
    {
        new_branch = root->left;
        root = NULL;
        root = new_branch;
        return new_branch;
    }
    //case B://If both child exist
    else
    {
        Tree *sucpar = root->right;
        Tree *suc = root->right;
        while ((suc->left) != NULL)
        {
            sucpar = suc;
            suc = suc->left;
        }
        sucpar->left = root->left;
        root = sucpar;
        return root;
    }
}

int main()
{
    int ch = 4, item;
    printf("\n BST(Binary Search Tree) Operation Menu :");
    while (ch != 0)
    {
        printf("\n 1. Insertion \n 2. Deletion \n 3. Display \n 4.Searching \n 0.Exit : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\n Enter the item you want to insert in BST : ");
                    scanf("%d",&item);
                    insertion(item);
                    break;
            case 2: printf("\n Enter the item you want to delete : ");
                    scanf("%d",&item);
                    root=deletion(root,item);
                    break;
            case 3: display();
                    break;
            case 4: printf("\n Enter the item you want to search : ");
                    scanf("%d",&item);
                    findloc(item,1);
                    break;
            case 0: printf("You exit....");
                    break;
            default: printf("\n Invalid Choice");
                     break;
        }
    }
    return 0;
}