#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;

Node *createNode(int x) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    n->data = x;
    n->next = NULL;
    return n;
}

int length(void) {
    int count = 0;
    Node *p = head;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

void insertBeginning(int x) {
    Node *n = createNode(x);
    n->next = head;
    head = n;
}

void insertEnd(int x) {
    Node *n = createNode(x);
    if (head == NULL) {
        head = n;
        return;
    }
    Node *p = head;
    while (p->next != NULL)
        p = p->next;
    p->next = n;
}

void insertPosition(int x, int pos) {
    if (pos < 1 || pos > length() + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        insertBeginning(x);
        return;
    }
    Node *p = head;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    Node *n = createNode(x);
    n->next = p->next;
    p->next = n;
}

void deleteBeginning(void) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node *p = head;
    head = head->next;
    free(p);
    printf("Deleted successfully.\n");
}

void deleteEnd(void) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Deleted successfully.\n");
        return;
    }
    Node *p = head;
    while (p->next->next != NULL)
        p = p->next;
    free(p->next);
    p->next = NULL;
    printf("Deleted successfully.\n");
}

void deletePosition(int pos) {
    int n = length();
    if (pos < 1 || pos > n) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        deleteBeginning();
        return;
    }
    Node *p = head;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    Node *q = p->next;
    p->next = q->next;
    free(q);
    printf("Deleted successfully.\n");
}

void search(int key) {
    Node *p = head;
    int pos = 1;
    while (p != NULL) {
        if (p->data == key) {
            printf("Found at position %d.\n", pos);
            return;
        }
        p = p->next;
        pos++;
    }
    printf("Element not found.\n");
}

void display(void) {
    Node *p = head;
    if (p == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

int main(void) {
    int ch, x, pos;

    do {
        printf("\n1.Insert beginning  2.Insert end  3.Insert position\n");
        printf("4.Delete beginning  5.Delete end  6.Delete position\n");
        printf("7.Search  8.Display  9.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1)
            return 1;

        switch (ch) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                insertBeginning(x);
                break;
            case 2:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                insertEnd(x);
                break;
            case 3:
                printf("Value and position: ");
                if (scanf("%d%d", &x, &pos) != 2) return 1;
                insertPosition(x, pos);
                break;
            case 4:
                deleteBeginning();
                break;
            case 5:
                deleteEnd();
                break;
            case 6:
                printf("Position: ");
                if (scanf("%d", &pos) != 1) return 1;
                deletePosition(pos);
                break;
            case 7:
                printf("Search value: ");
                if (scanf("%d", &x) != 1) return 1;
                search(x);
                break;
            case 8:
                display();
                break;
            case 9:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 9);

    while (head != NULL)
        deleteBeginning();

    return 0;
}