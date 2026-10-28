#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int x) {
    if (rear == MAX - 1) {
        printf("Queue overflow.\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = x;
    printf("Inserted %d.\n", x);
}

void dequeue(void) {
    if (front == -1 || front > rear) {
        printf("Queue underflow.\n");
        return;
    }

    printf("Deleted: %d\n", queue[front++]);

    if (front > rear)
        front = rear = -1;
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

    printf("Queue: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
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