#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 200

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^';
}

int infixToPostfix(const char *infix, char *postfix) {
    char stack[MAX];
    int top = -1, j = 0;
    int expectOperand = 1;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace((unsigned char)c))
            continue;

        if (isdigit((unsigned char)c)) {
            if (!expectOperand) return 0;
            postfix[j++] = c;
            expectOperand = 0;
        } else if (c == '(') {
            if (!expectOperand || top == MAX - 1) return 0;
            stack[++top] = c;
            expectOperand = 1;
        } else if (c == ')') {
            if (expectOperand) return 0;

            while (top >= 0 && stack[top] != '(')
                postfix[j++] = stack[top--];

            if (top < 0) return 0;
            top--;
            expectOperand = 0;
        } else if (isOperator(c)) {
            if (expectOperand || top == MAX - 1) return 0;

            while (top >= 0 && stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(c) ||
                   (precedence(stack[top]) == precedence(c) && c != '^'))) {
                postfix[j++] = stack[top--];
            }

            stack[++top] = c;
            expectOperand = 1;
        } else {
            return 0;
        }

        if (j >= MAX - 1) return 0;
    }

    if (expectOperand) return 0;

    while (top >= 0) {
        if (stack[top] == '(') return 0;
        postfix[j++] = stack[top--];
        if (j >= MAX) return 0;
    }

    postfix[j] = '\0';
    return 1;
}

int evaluatePostfix(const char *postfix, long long *result) {
    long long stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit((unsigned char)c)) {
            if (top == MAX - 1) return 0;
            stack[++top] = c - '0';
        } else if (isOperator(c)) {
            if (top < 1) return 0;

            long long b = stack[top--];
            long long a = stack[top--];
            long long r;

            switch (c) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0) return 0;
                    r = a / b;
                    break;
                case '%':
                    if (b == 0) return 0;
                    r = a % b;
                    break;
                case '^':
                    if (b < 0 || b > 63) return 0;
                    r = 1;
                    for (long long k = 0; k < b; k++) {
                        if (a != 0 &&
                            (r > 0 ? (a > 0 && r > LLONG_MAX / a) :
                                     (a > 0 && r < LLONG_MIN / a)))
                            return 0;
                        r *= a;
                    }
                    break;
                default: return 0;
            }

            stack[++top] = r;
        } else {
            return 0;
        }
    }

    if (top != 0) return 0;
    *result = stack[top];
    return 1;
}

int main(void) {
    char infix[MAX], postfix[MAX];
    long long result;

    printf("Enter infix expression (single-digit operands): ");
    if (fgets(infix, sizeof(infix), stdin) == NULL)
        return 1;

    infix[strcspn(infix, "\n")] = '\0';

    if (!infixToPostfix(infix, postfix)) {
        printf("Invalid infix expression.\n");
        return 1;
    }

    printf("Postfix: %s\n", postfix);

    if (!evaluatePostfix(postfix, &result)) {
        printf("Cannot evaluate expression.\n");
        return 1;
    }

    printf("Result: %lld\n", result);
    return 0;
}