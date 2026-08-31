#include "CustomList.h"
#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list_length(const List *self) { return self->count; }

void list_append(List *self, char *str) {
    LNode *curr = malloc(sizeof(*curr));
    curr->next = NULL;

    size_t len = strlen(str) + 1;
    char *strcopy = malloc(len);
    if (strcopy)
        memcpy(strcopy, str, len);
    curr->text = strcopy;

    if (self->tail == NULL) {
        self->head = curr;
        self->tail = curr;
    } else {
        self->tail->next = curr;
        self->tail = curr;
    }
    self->count++;
}

int list_index(const List *self, char *str) {
    if (!str)
        return -1;
    LNode *curr = self->head;
    int index = 0;

    while (curr != NULL) {
        if (curr->text && strcmp(str, curr->text) == 0)
            return index;
        curr = curr->next;
        index++;
    }

    return -1;
}

void list_print(const List *self) {
    printf("[ ");
    LNode *curr = self->head;
    while (curr != NULL) {
        printf("\"%s\"", curr->text);
        curr = curr->next;
        if (curr)
            printf(", ");
    }
    printf(" ]");
    printf("\n");
}

void list_delete(const List *self) {
    LNode *curr, *next;
    curr = self->head;
    while (curr) {
        free(curr->text);
        next = curr->next;
        free(curr);
        curr = next;
    }
    free((void *)self);
}

List *list_new() {
    List *list = malloc(sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    list->get_length = &list_length;
    list->append = &list_append;
    list->index = &list_index;

    list->print = &list_print;

    list->del = &list_delete;
    return list;
}
