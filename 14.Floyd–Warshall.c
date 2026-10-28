#include <stdio.h>

#define MAX 20
#define INF 1000000000LL

long long dist[MAX][MAX];

int main(void) {
    int n;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix (-1 for no edge):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long w;

            if (scanf("%lld", &w) != 1) {
                printf("Invalid input.\n");
                return 1;
            }

            if (i == j) {
                if (w != 0) {
                    printf("Diagonal entries must be 0.\n");
                    return 1;
                }
                dist[i][j] = 0;
            } else if (w == -1) {
                dist[i][j] = INF;
            } else if (w >= 0 && w < INF) {
                dist[i][j] = w;
            } else {
                printf("Invalid edge weight.\n");
                return 1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    long long candidate = dist[i][k] + dist[k][j];

                    if (candidate < dist[i][j])
                        dist[i][j] = candidate;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            printf("Negative cycle detected.\n");
            return 1;
        }
    }

    printf("\nAll-pairs shortest-distance matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7lld", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}