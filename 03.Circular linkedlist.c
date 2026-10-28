#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *tail = NULL;

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
    if (tail == NULL) return 0;

    int count = 0;
    Node *p = tail->next;
    do {
        count++;
        p = p->next;
    } while (p != tail->next);
    return count;
}

void insertBeginning(int x) {
    Node *n = createNode(x);
    if (tail == NULL) {
        tail = n;
        n->next = n;
    } else {
        n->next = tail->next;
        tail->next = n;
    }
}

void insertEnd(int x) {
    insertBeginning(x);
    tail = tail->next;
}

void insertPosition(int x, int pos) {
    int n = length();
    if (pos < 1 || pos > n + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        insertBeginning(x);
        return;
    }
    if (pos == n + 1) {
        insertEnd(x);
        return;
    }

    Node *p = tail->next;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    Node *q = createNode(x);
    q->next = p->next;
    p->next = q;
}

void deleteBeginning(void) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *first = tail->next;
    if (first == tail) {
        tail = NULL;
    } else {
        tail->next = first->next;
    }
    free(first);
    printf("Deleted successfully.\n");
}

void deleteEnd(void) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (tail->next == tail) {
        free(tail);
        tail = NULL;
    } else {
        Node *p = tail->next;
        while (p->next != tail)
            p = p->next;
        p->next = tail->next;
        free(tail);
        tail = p;
    }
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
    if (pos == n) {
        deleteEnd();
        return;
    }

    Node *p = tail->next;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    Node *q = p->next;
    p->next = q->next;
    free(q);
    printf("Deleted successfully.\n");
}

void search(int key) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *p = tail->next;
    int pos = 1;
    do {
        if (p->data == key) {
            printf("Found at position %d.\n", pos);
            return;
        }
        p = p->next;
        pos++;
    } while (p != tail->next);

    printf("Element not found.\n");
}

void display(void) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *p = tail->next;
    printf("Circular list: ");
    do {
        printf("%d -> ", p->data);
        p = p->next;
    } while (p != tail->next);
    printf("(back to %d)\n", tail->next->data);
}

int main(void) {
    int ch, x, pos;

    do {
        printf("\n1.Insert beginning  2.Insert end  3.Insert position\n");
        printf("4.Delete beginning  5.Delete end  6.Delete position\n");
        printf("7.Search  8.Display  9.Exit\nChoice: ");

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
                display();
                break;
            case 9:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 9);

    while (tail != NULL)
        deleteBeginning();

    return 0;
}