#include <stdio.h>

#define SIZE 10
#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

int table[SIZE];
int status[SIZE];

int hashFunction(int key) {
    int index = key % SIZE;
    return index < 0 ? index + SIZE : index;
}

void insert(int key) {
    int start = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int index = (start + i) % SIZE;

        if (status[index] == OCCUPIED && table[index] == key) {
            printf("Key already exists.\n");
            return;
        }

        if (status[index] != OCCUPIED) {
            table[index] = key;
            status[index] = OCCUPIED;
            printf("Inserted %d at index %d.\n", key, index);
            return;
        }
    }

    printf("Hash table is full.\n");
}

int findIndex(int key) {
    int start = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int index = (start + i) % SIZE;

        if (status[index] == EMPTY)
            return -1;

        if (status[index] == OCCUPIED && table[index] == key)
            return index;
    }

    return -1;
}

void search(int key) {
    int index = findIndex(key);

    if (index == -1)
        printf("Key not found.\n");
    else
        printf("Key found at index %d.\n", index);
}

void deleteKey(int key) {
    int index = findIndex(key);

    if (index == -1) {
        printf("Key not found.\n");
        return;
    }

    status[index] = DELETED;
    printf("Deleted %d from index %d.\n", key, index);
}

void display(void) {
    printf("\nIndex\tValue\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", i);

        if (status[i] == OCCUPIED)
            printf("%d\n", table[i]);
        else if (status[i] == DELETED)
            printf("DELETED\n");
        else
            printf("EMPTY\n");
    }
}

int main(void) {
    int ch, key;

    do {
        printf("\n1.Insert  2.Search  3.Delete  4.Display  5.Exit\nChoice: ");

        if (scanf("%d", &ch) != 1) return 1;

        switch (ch) {
            case 1:
                printf("Key: ");
                if (scanf("%d", &key) != 1) return 1;
                insert(key);
                break;
            case 2:
                printf("Search key: ");
                if (scanf("%d", &key) != 1) return 1;
                search(key);
                break;
            case 3:
                printf("Delete key: ");
                if (scanf("%d", &key) != 1) return 1;
                deleteKey(key);
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