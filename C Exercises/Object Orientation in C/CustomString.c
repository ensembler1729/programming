#include "CustomString.h"

#include <stdio.h>
#include <stdlib.h>

String *string_new() {
    String *str = malloc(sizeof(*str));
    str->length = 0;
    str->allocated = 10;
    str->data = malloc(10);
    str->data[str->length] = '\0';
    return str;
}

void string_delete(const String *self) {
    free((void *)self->data);
    free((void *)self);
}

int length(const String *self) { return self->length; }

char *get_str(const String *self) { return self->data; }

void dump(const String *self) {
    printf("String length:%d allocated:%d data:{%s}\n", self->length,
           self->allocated, self->data);
}

void str_append(String *self, char c) {
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

void str_appends(String *self, char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        str_append(self, str[i]);
}

void str_assign(String *self, char *str) {
    self->length = 0;
    self->data[self->length] = '\0';
    str_appends(self, str);
}
