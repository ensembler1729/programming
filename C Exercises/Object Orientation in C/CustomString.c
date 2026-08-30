#include "CustomString.h"

#include <stdio.h>
#include <stdlib.h>

int string_length(const String *self) { return self->length; }

char *string_get(const String *self) { return self->data; }

void string_append(String *self, char c) {
    if (self->length >= (self->allocated - 2)) {
        self->allocated += 10;
        char *tmp = (char *)realloc(self->data, self->allocated);
        if (tmp == NULL) {
            // Handle Failure
            // realloc failed — s->data is STILL VALID (unchanged)
            return;
        }
        self->data = tmp;
    }
    self->data[self->length++] = c;
    self->data[self->length] = '\0';
}

void string_appends(String *self, char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        string_append(self, str[i]);
}

void string_assign(String *self, char *str) {
    self->length = 0;
    self->data[self->length] = '\0';
    string_appends(self, str);
}

void string_print(const String *self) {
    printf("String <length:%d allocated:%d data:[%s]>\n", self->length,
           self->allocated, self->data);
}

void string_delete(const String *self) {
    free((void *)self->data);
    free((void *)self);
}

String *string_new() {
    String *str = malloc(sizeof(*str));
    str->length = 0;
    str->allocated = 10;
    str->data = malloc(10);
    str->data[str->length] = '\0';

    str->get_length = &string_length;
    str->get_string = &string_get;
    str->append = &string_append;
    str->appends = &string_appends;
    str->assign = &string_assign;

    str->print = &string_print;

    str->del = &string_delete;
    return str;
}
