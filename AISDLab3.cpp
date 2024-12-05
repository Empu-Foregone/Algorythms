#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE_PERCENTAGE 0.75

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** table;
    int size;    
} HashTable;

int hashFunction(int key, int size) {
    return key % size;
}

HashTable* initHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

void removeElement(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    Node* current = ht->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data == key) {
            Node* toDelete = current;
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void display(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Index %d: ", i);
        Node* current = ht->table[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int main() {

    int N = 7 * 5 + 50; 
    int S = (int)(N * HASH_SIZE_PERCENTAGE); 
    printf("Розмір хеш-таблиці S: %d\n", S);

    HashTable* ht = initHashTable(S);

    srand(time(NULL));
    int M = S; 
    printf("Вставлені елементи: ");
    for (int i = 0; i < M; i++) {
        int num = rand() % 100;
        printf("%d ", num);
        insert(ht, num);
    }
    printf("\n\nХеш-таблиця після заповнення:\n");
    display(ht);

    printf("\nВидалення парних чисел...\n");
    for (int i = 0; i < 100; i += 2) {
        removeElement(ht, i);
    }

    printf("\nХеш-таблиця після видалення парних чисел:\n");
    display(ht);

    freeHashTable(ht);

    return 0;
}
