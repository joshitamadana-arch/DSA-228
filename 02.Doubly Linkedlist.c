#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node *head = NULL, *tail = NULL;

Node *createNode(int x) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    n->data = x;
    n->prev = n->next = NULL;
    return n;
}

int length(void) {
    int count = 0;
    for (Node *p = head; p != NULL; p = p->next)
        count++;
    return count;
}

void insertBeginning(int x) {
    Node *n = createNode(x);
    n->next = head;
    if (head != NULL)
        head->prev = n;
    else
        tail = n;
    head = n;
}

void insertEnd(int x) {
    Node *n = createNode(x);
    n->prev = tail;
    if (tail != NULL)
        tail->next = n;
    else
        head = n;
    tail = n;
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
    if (pos == length() + 1) {
        insertEnd(x);
        return;
    }

    Node *p = head;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    Node *n = createNode(x);
    n->next = p->next;
    n->prev = p;
    p->next->prev = n;
    p->next = n;
}

void deleteBeginning(void) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node *p = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;
    free(p);
    printf("Deleted successfully.\n");
}

void deleteEnd(void) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node *p = tail;
    tail = tail->prev;
    if (tail != NULL)
        tail->next = NULL;
    else
        head = NULL;
    free(p);
    printf("Deleted successfully.\n");
}

void deletePosition(int pos) {
    if (pos < 1 || pos > length()) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        deleteBeginning();
        return;
    }
    if (pos == length()) {
        deleteEnd();
        return;
    }

    Node *p = head;
    for (int i = 1; i < pos; i++)
        p = p->next;

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    printf("Deleted successfully.\n");
}

void search(int key) {
    int pos = 1;
    for (Node *p = head; p != NULL; p = p->next, pos++) {
        if (p->data == key) {
            printf("Found at position %d.\n", pos);
            return;
        }
    }
    printf("Element not found.\n");
}

void displayForward(void) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward: ");
    for (Node *p = head; p != NULL; p = p->next)
        printf("%d <-> ", p->data);
    printf("NULL\n");
}

void displayBackward(void) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Backward: ");
    for (Node *p = tail; p != NULL; p = p->prev)
        printf("%d <-> ", p->data);
    printf("NULL\n");
}

int main(void) {
    int ch, x, pos;

    do {
        printf("\n1.Insert beginning  2.Insert end  3.Insert position\n");
        printf("4.Delete beginning  5.Delete end  6.Delete position\n");
        printf("7.Search  8.Forward display  9.Backward display  10.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1) return 1;

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
                displayForward();
                break;
            case 9:
                displayBackward();
                break;
            case 10:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 10);

    while (head != NULL)
        deleteBeginning();

    return 0;
}