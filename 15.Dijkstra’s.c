#include <stdio.h>

#define MAX 20
#define INF 1000000000LL

long long graph[MAX][MAX];
long long dist[MAX];
int visited[MAX];
int parent[MAX];

int main(void) {
    int n, source;

    printf("Enter number of vertices (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter weighted adjacency matrix (-1 for no edge):\n");

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
                graph[i][j] = 0;
            } else if (w == -1) {
                graph[i][j] = INF;
            } else if (w >= 0 && w < INF) {
                graph[i][j] = w;
            } else {
                printf("Invalid edge weight.\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);

    if (scanf("%d", &source) != 1 ||
        source < 0 || source >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        long long minimum = INF;

        /* Find the unvisited vertex with minimum distance. */
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minimum) {
                minimum = dist[i];
                u = i;
            }
        }

        /* No more reachable vertices. */
        if (u == -1)
            break;

        visited[u] = 1;

        /* Relax the outgoing edges of u. */
        for (int v = 0; v < n; v++) {
            if (!visited[v] &&
                graph[u][v] != INF &&
                dist[u] != INF &&
                dist[u] <= INF - graph[u][v]) {

                long long newDistance = dist[u] + graph[u][v];

                if (newDistance < dist[v]) {
                    dist[v] = newDistance;
                    parent[v] = u;
                }
            }
        }
    }

    printf("\nVertex\tDistance\tShortest path\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", i);

        if (dist[i] == INF) {
            printf("INF\t\tNo path\n");
            continue;
        }

        printf("%lld\t\t", dist[i]);

        /* Reconstruct the shortest path. */
        int path[MAX];
        int length = 0;
        int current = i;

        while (current != -1 && length < MAX) {
            path[length++] = current;
            current = parent[current];
        }

        for (int j = length - 1; j >= 0; j--) {
            printf("%d", path[j]);

            if (j > 0)
                printf(" -> ");
        }

        printf("\n");
    }

    return 0;
}