// Hash Table Implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TABLE_SIZE 100000

typedef struct entry_t
{
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct
{
    entry_t **entries;
} ht_t;

unsigned int hash(const char *key)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i)
    {
        value = value * 37 + key[i];
    }

    // make sure value is 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

entry_t *ht_pair(const char *key, const char *value)
{

    // allocate the entry
    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copy the key and value in place
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    // next starts out as null but may be set later on
    entry->next = NULL;

    return entry;
}

ht_t *ht_create(void)
{

    // allocate table
    ht_t *hashtable = malloc((sizeof(ht_t) * 1));

    // allocate table entries
    hashtable->entries = malloc(sizeof(entry_t *) * TABLE_SIZE);

    // set each to null
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(ht_t *hashtable, const char *key, const char *value)
{
    unsigned int bucket = hash(key);

    // try to lookup an entry set
    entry_t *entry = hashtable->entries[bucket];

    // if no entry, insert immediately
    if (entry == NULL)
    {
        hashtable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    // walk through each entry until either the end is
    // reached or a matching key is found
    while (entry != NULL)
    {
        // check key
        if (strcmp(entry->key, key) == 0)
        {
            // match found, replace value
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // end of chain reached without a match, add new
    prev->next = ht_pair(key, value);
}

char *ht_get(ht_t *hashtable, const char *key)
{
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    entry_t *entry = hashtable->entries[bucket];

    // no entry
    if (entry == NULL)
    {
        return NULL;
    }

    // walk through each entry in the bucket
    while (entry != NULL)
    {
        // return value if found
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }

        // proceed to next key if available
        entry = entry->next;
    }

    // no key match
    return NULL;
}

void ht_del(ht_t *hashtable, const char *key)
{
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    entry_t *entry = hashtable->entries[bucket];

    // no entry
    if (entry == NULL)
    {
        return;
    }

    entry_t *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL)
    {
        // check key
        if (strcmp(entry->key, key) == 0)
        {
            // first item and no next entry
            if (entry->next == NULL && idx == 0)
            {
                hashtable->entries[bucket] = NULL;
            }

            // first item with a next entry
            if (entry->next != NULL && idx == 0)
            {
                hashtable->entries[bucket] = entry->next;
            }

            // last item
            if (entry->next == NULL && idx != 0)
            {
                prev->next = NULL;
            }

            // middle item
            if (entry->next != NULL && idx != 0)
            {
                prev->next = entry->next;
            }

            // free the deleted entry
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_dump(ht_t *hashtable)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL)
        {
            continue;
        }

        printf("slot[%4d]: ", i);

        for (;;)
        {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL)
            {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

int main(int argc, char **argv) {

    ht_t *ht = ht_create();

    ht_set(ht, "array", "contiguous memory collection");
    ht_set(ht, "linked_list", "nodes connected by pointers");
    ht_set(ht, "doubly_linked_list", "nodes with next and previous links");
    ht_set(ht, "circular_list", "last node points to first");
    ht_set(ht, "stack", "LIFO structure");
    ht_set(ht, "queue", "FIFO structure");
    ht_set(ht, "deque", "double-ended queue");
    ht_set(ht, "priority_queue", "elements ordered by priority");
    ht_set(ht, "hash_table", "key-value storage");
    ht_set(ht, "binary_tree", "tree with max two children");
    ht_set(ht, "binary_search_tree", "ordered binary tree");
    ht_set(ht, "heap", "complete binary tree");
    ht_set(ht, "graph", "nodes and edges");
    ht_set(ht, "trie", "prefix tree");
    ht_set(ht, "set", "unique elements collection");
    ht_set(ht, "map", "key to value mapping");
    ht_set(ht, "adjacency_list", "graph representation");
    ht_set(ht, "adjacency_matrix", "graph matrix representation");
    ht_set(ht, "bloom_filter", "probabilistic membership structure");
    ht_set(ht, "skip_list", "layered linked list");
    ht_set(ht, "segment_tree", "range query structure");
    ht_set(ht, "disjoint_set", "union-find structure");

    ht_dump(ht);

    return 0;
}