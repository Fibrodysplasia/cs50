#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"

int dictionary_word_count = 0;
bool dictionary_loaded = false;

// Hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 10000;
node *table[N];

// Load dictionary into memory
bool load(const char *dictionary) {
    FILE *open_dictionary = fopen(dictionary, "r");
    if (open_dictionary == NULL) {
        printf("Couldn't open dictionary. \n");
        return false;
    }
    else if (open_dictionary != NULL) {
        char buffer[LENGTH + 1];
        int hash_value = 0;
        while (fscanf(open_dictionary, "%s", buffer) != EOF) {
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL) {
                printf("Couldn't allocate memory for new node. \n");
                return false;
                break;
            }
            else {
                strcpy(new_node->word, buffer);
                new_node->next = NULL;
                hash_value = hash(buffer);
                if (table[hash_value] == NULL) {
                    table[hash_value] = new_node;
                }
                else if (table[hash_value] != NULL) {
                    new_node->next = table[hash_value];
                    table[hash_value] = new_node;
                }
                dictionary_word_count++;
            }
        }
        dictionary_loaded = true;
        fclose(open_dictionary);
        return true;
    }
    else {
        return false;
    }
}

// Unloads dictionary from memory
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL) {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}

// Returns true if word is in dictionary, else false

// TODO:
// Staff solution spends 0 time in check somehow, figure it out
bool check(const char *word) {
    int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL) {
        if (strcasecmp(word, cursor->word) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    // TODO: Improve this hash function, it's garbage
    return toupper(word[0]) - 'A';
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    int size = dictionary_loaded ? dictionary_word_count : 0;
    return size;
}
