#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node *createNode(int x) {
    Node *n = malloc(sizeof(Node));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    n->data = x;
    n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int x) {
    if (root == NULL)
        return createNode(x);

    if (x < root->data)
        root->left = insert(root->left, x);
    else if (x > root->data)
        root->right = insert(root->right, x);

    return root;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    Node *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    int ch;

    do {
        printf("\n\n1.Inorder  2.Preorder  3.Postorder  4.Display all  5.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1) {
            freeTree(root);
            return 1;
        }

        switch (ch) {
            case 1:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\nPreorder: ");
                preorder(root);
                printf("\nPostorder: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 5);

    freeTree(root);
    return 0;
}