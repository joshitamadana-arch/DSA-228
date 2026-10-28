#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int n;

void BFS(int start) {
    int queue[MAX];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS: ");

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            DFS(i);
    }
}

int main(void) {
    int edges, u, v, start, ch;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0 ||
        edges > n * (n - 1) / 2) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    printf("Enter each edge as two vertices (0 to %d):\n", n - 1);

    for (int i = 0; i < edges; i++) {
        if (scanf("%d%d", &u, &v) != 2 ||
            u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    do {
        printf("\n1.BFS  2.DFS  3.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1)
            return 1;

        if (ch == 1 || ch == 2) {
            printf("Starting vertex: ");
            if (scanf("%d", &start) != 1 ||
                start < 0 || start >= n) {
                printf("Invalid starting vertex.\n");
                return 1;
            }

            if (ch == 1) {
                BFS(start);
            } else {
                for (int i = 0; i < n; i++)
                    visited[i] = 0;

                printf("DFS: ");
                DFS(start);
                printf("\n");
            }
        } else if (ch != 3) {
            printf("Invalid choice.\n");
        }
    } while (ch != 3);

    return 0;
}