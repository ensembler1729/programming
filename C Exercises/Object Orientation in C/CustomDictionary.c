#include "CustomDictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DNode *dict_find(const Dictionary *self, char *key) {
    if (!key)
        return NULL;
    DNode *curr = self->head;
    while (curr != NULL) {
        if (curr->key != NULL && strcmp(key, curr->key) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

char *dict_get(const Dictionary *self, char *key) {
    DNode *node = self->find(self, key);
    if (node == NULL)
        return NULL;
    return node->value;
}

void dict_put(Dictionary *self, char *key, char *value) {
    DNode *node = self->find(self, key);

    size_t len = strlen(value) + 1;
    char *v = malloc(len);
    if (v)
        memcpy(v, value, len);

    if (node != NULL) {
        node->value = v;
    }

    node = malloc(sizeof(*node));
    len = strlen(key) + 1;
    char *k = malloc(len);
    if (k)
        memcpy(k, key, len);
    node->key = k;
    node->value = v;
    node->next = NULL;
    if (self->tail == NULL) {
        self->head = node;
        self->tail = node;
    } else {
        self->tail->next = node;
        self->tail = node;
    }
}

void dict_print(const Dictionary *self) {
    printf("{\n");
    DNode *curr = self->head;
    while (curr != NULL) {
        printf("\t\"%s\": \"%s\"", curr->key, curr->value);
        curr = curr->next;
        if (curr)
            printf(",");
        printf("\n");
    }
    printf("}");
    printf("\n");
}

void dict_delete(const Dictionary *self) {
    DNode *curr, *next;
    curr = self->head;
    while (curr) {
        free(curr->key);
        free(curr->value);
        next = curr->next;
        free(curr);
        curr = next;
    }
    free((void *)self);
}

Dictionary *dict_new() {
    Dictionary *dict = malloc(sizeof(*dict));
    dict->head = NULL;
    dict->tail = NULL;
    dict->count = 0;

    dict->find = &dict_find;
    dict->get = &dict_get;
    dict->put = &dict_put;

    dict->print = &dict_print;

    dict->del = &dict_delete;
    return dict;
}
