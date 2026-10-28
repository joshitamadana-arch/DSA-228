#include <stdio.h>

#define MAX 5

int stack[MAX];
int top = -1;

void push(int x) {
    if (top == MAX - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack[++top] = x;
    printf("Pushed %d.\n", x);
}

void pop(void) {
    if (top == -1) {
        printf("Stack underflow.\n");
        return;
    }
    printf("Popped: %d\n", stack[top--]);
}

void peek(void) {
    if (top == -1)
        printf("Stack is empty.\n");
    else
        printf("Top element: %d\n", stack[top]);
}

void display(void) {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main(void) {
    int ch, x;

    do {
        printf("\n1.Push  2.Pop  3.Peek  4.Display  5.Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) return 1;

        switch (ch) {
            case 1:
                printf("Value: ");
                if (scanf("%d", &x) != 1) return 1;
                push(x);
                break;
            case 2:
                pop();
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