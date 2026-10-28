#include <stdio.h>

#define MAX 5

int deque[MAX];
int front = -1, rear = -1;

int isFull(void) {
    return (front == 0 && rear == MAX - 1) ||
           (front == rear + 1);
}

int isEmpty(void) {
    return front == -1;
}

void insertFront(int x) {
    if (isFull()) {
        printf("Deque overflow.\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else if (front == 0)
        front = MAX - 1;
    else
        front--;

    deque[front] = x;
    printf("Inserted %d at front.\n", x);
}

void insertRear(int x) {
    if (isFull()) {
        printf("Deque overflow.\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;

    deque[rear] = x;
    printf("Inserted %d at rear.\n", x);
}

void deleteFront(void) {
    if (isEmpty()) {
        printf("Deque underflow.\n");
        return;
    }

    printf("Deleted from front: %d\n", deque[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
}

void deleteRear(void) {
    if (isEmpty()) {
        printf("Deque underflow.\n");
        return;
    }

    printf("Deleted from rear: %d\n", deque[rear]);

    if (front == rear)
        front = rear = -1;
    else if (rear == 0)
        rear = MAX - 1;
    else
        rear--;
}

void display(void) {
    if (isEmpty()) {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque: ");
    int i = front;

    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main(void) {
    int ch, x;

    do {
        printf("\n1.Insert front  2.Insert rear\n");
        printf("3.Delete front  4.Delete rear\n");
        printf("5.Display  6.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1) return 1;

        switch (ch) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                insertFront(x);
                break;
            case 2:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                insertRear(x);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 6);

    return 0;
}