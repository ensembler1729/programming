#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

typedef struct {
    int length;
    int allocated; /* The length of the *data */
    char *data;
} String;

// Constructor
String *string_new();

// Destructor
void string_delete(const String *self);

int length(const String *self);

char *get_str(const String *self);

void dump(const String *self);

/* x = x + 'h' */
void str_append(String *self, char c);

/* x = x + "hello" */
void str_appends(String *self, char *str);

/* x = "Hello" */
void str_assign(String *self, char *str);

#endif
