#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MapEntry *__Map_find(const Map *self, char *key) {
    if (!key)
        return NULL;
    MapEntry *curr = self->__head;
    while (curr != NULL) {
        if (curr->key != NULL && strcmp(key, curr->key) == 0)
            return curr;
        curr = curr->__next;
    }
    return NULL;
}

int __Map_get(const Map *self, char *key, int def) {
    MapEntry *entry = __Map_find(self, key);
    if (entry == NULL)
        return def;
    return entry->value;
}

void __Map_put(Map *self, char *key, int value) {
    MapEntry *entry = __Map_find(self, key);
    if (entry != NULL)
        entry->value = value;

    entry = malloc(sizeof(*entry));
    size_t len = strlen(key) + 1;
    char *k = malloc(len);
    if (k)
        memcpy(k, key, len);
    entry->key = k;
    entry->value = value;
    entry->__next = NULL;
    if (self->__tail == NULL) {
        self->__head = entry;
        self->__tail = entry;
    } else {
        self->__tail->__next = entry;
        self->__tail = entry;
    }
}

int __Map_size(const Map *self) { return self->__count; }

MapEntry *__MapIter_next(MapIter *self) {
    MapEntry *entry = self->__current;
    if (entry == NULL)
        return NULL;
    self->__current = self->__current->__next;
    return entry;
}

void __MapIter_del(const MapIter *self) { free((void *)self); }

MapIter *__Map_iter(const Map *self) {
    MapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head;
    iter->next = &__MapIter_next;
    iter->del = &__MapIter_del;
    return iter;
}

void __Map_print(const Map *self) {
    MapEntry *curr;
    printf("Object Map count=%d\n", self->__count);
    for (curr = self->__head; curr != NULL; curr = curr->__next) {
        printf(" %s=%d\n", curr->key, curr->value);
    }
}

void __Map_del(const Map *self) {
    MapEntry *curr, *next;
    curr = self->__head;
    while (curr) {
        free(curr->key);
        next = curr->__next;
        free(curr);
        curr = next;
    }
    free((void *)self);
}

Map *Map_new() {
    Map *map = malloc(sizeof(*map));
    map->__head = NULL;
    map->__tail = NULL;
    map->__count = 0;

    map->put = &__Map_put;
    map->get = &__Map_get;
    map->size = &__Map_size;
    map->iter = &__Map_iter;
    map->print = &__Map_print;
    map->del = &__Map_del;
    return map;
}
