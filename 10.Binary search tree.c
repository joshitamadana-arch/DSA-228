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
    else
        printf("Duplicate values are not allowed.\n");

    return root;
}

Node *minimum(Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL) {
        printf("Value not found.\n");
        return NULL;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

Node *search(Node *root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;

        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
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
    int ch, x;

    do {
        printf("\n1.Insert  2.Delete  3.Search\n");
        printf("4.Inorder  5.Preorder  6.Postorder  7.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1) {
            freeTree(root);
            return 1;
        }

        switch (ch) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) {
                    freeTree(root);
                    return 1;
                }
                root = insert(root, x);
                break;
            case 2:
                printf("Value to delete: ");
                if (scanf("%d", &x) != 1) {
                    freeTree(root);
                    return 1;
                }
                if (search(root, x) == NULL)
                    printf("Value not found.\n");
                else {
                    root = deleteNode(root, x);
                    printf("Deleted successfully.\n");
                }
                break;
            case 3:
                printf("Search value: ");
                if (scanf("%d", &x) != 1) {
                    freeTree(root);
                    return 1;
                }
                printf("%s\n", search(root, x) ?
                       "Value found." : "Value not found.");
                break;
            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 7);

    freeTree(root);
    return 0;
}