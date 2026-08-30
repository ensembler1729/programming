#include "CustomList.h"
#include <stdio.h>
#include <stdlib.h>

int list_length(const List *self) { return self->count; }

void list_append(List *self, char *str) {
    LNode *curr = malloc(sizeof(*curr));
    curr->text = str;
    curr->next = NULL;

    LNode *tail = self->tail;
    if (tail == NULL) {
        self->head = curr;
        self->tail = curr;
        self->count++;
        return;
    }
    tail->next = curr;
    self->tail = curr;
    self->count++;
}

int list_index(const List *self, char *str) { return -1; }

void list_print(const List *self) {
    printf("[ ");
    LNode *curr = self->head;
    while (1) {
        printf("\"%s\"", curr->text);
        if (curr->next == NULL) {
            printf(" ]");
            break;
        }
        printf(", ");
        curr = curr->next;
    }
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
