#include <stdio.h>
#include <stdlib.h>

#define MAX 100

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

    Node *p = root;

    while (1) {
        if (x < p->data) {
            if (p->left == NULL) {
                p->left = createNode(x);
                break;
            }
            p = p->left;
        } else if (x > p->data) {
            if (p->right == NULL) {
                p->right = createNode(x);
                break;
            }
            p = p->right;
        } else {
            printf("Duplicate value ignored.\n");
            break;
        }
    }

    return root;
}

void inorder(Node *root) {
    Node *stack[MAX];
    int top = -1;
    Node *current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            if (top == MAX - 1) {
                printf("Tree is too large for this stack.\n");
                return;
            }
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }

    printf("\n");
}

void preorder(Node *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Node *stack[MAX];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        Node *p = stack[top--];
        printf("%d ", p->data);

        if (p->right != NULL) {
            if (top == MAX - 1) {
                printf("\nStack capacity exceeded.\n");
                return;
            }
            stack[++top] = p->right;
        }

        if (p->left != NULL) {
            if (top == MAX - 1) {
                printf("\nStack capacity exceeded.\n");
                return;
            }
            stack[++top] = p->left;
        }
    }

    printf("\n");
}

void postorder(Node *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Node *s1[MAX], *s2[MAX];
    int top1 = -1, top2 = -1;

    s1[++top1] = root;

    while (top1 != -1) {
        Node *p = s1[top1--];

        if (top2 == MAX - 1) {
            printf("Tree is too large for this stack.\n");
            return;
        }
        s2[++top2] = p;

        if (p->left != NULL) {
            if (top1 == MAX - 1) {
                printf("Tree is too large for this stack.\n");
                return;
            }
            s1[++top1] = p->left;
        }

        if (p->right != NULL) {
            if (top1 == MAX - 1) {
                printf("Tree is too large for this stack.\n");
                return;
            }
            s1[++top1] = p->right;
        }
    }

    while (top2 != -1)
        printf("%d ", s2[top2--]->data);

    printf("\n");
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
        printf("\n1.Insert  2.Inorder  3.Preorder  4.Postorder  5.Exit\nChoice: ");

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
                printf("Inorder: ");
                inorder(root);
                break;
            case 3:
                printf("Preorder: ");
                preorder(root);
                break;
            case 4:
                printf("Postorder: ");
                postorder(root);
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