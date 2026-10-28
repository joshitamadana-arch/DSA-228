#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int x) {
    if ((rear + 1) % MAX == front) {
        printf("Circular queue overflow.\n");
        return;
    }

    if (front == -1)
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;

    queue[rear] = x;
    printf("Inserted %d.\n", x);
}

void dequeue(void) {
    if (front == -1) {
        printf("Circular queue underflow.\n");
        return;
    }

    printf("Deleted: %d\n", queue[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
}

void peek(void) {
    if (front == -1)
        printf("Queue is empty.\n");
    else
        printf("Front element: %d\n", queue[front]);
}

void display(void) {
    if (front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular queue: ");
    int i = front;

    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main(void) {
    int ch, x;

    do {
        printf("\n1.Enqueue  2.Dequeue  3.Peek  4.Display  5.Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) return 1;

        switch (ch) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                enqueue(x);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 5);

    return 0;
}