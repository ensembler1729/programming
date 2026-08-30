#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

typedef struct String String;

struct String {
    int length;
    int allocated; /* The length of the *data */
    char *data;

    int (*get_length)(const String *self);
    char *(*get_string)(const String *self);

    /* x = x + 'h' */
    void (*append)(String *self, char c);
    /* x = x + "hello" */
    void (*appends)(String *self, char *str);
    /* x = "Hello" */
    void (*assign)(String *self, char *str);

    void (*print)(const String *self);

    // Destructor
    void (*del)(const String *self);
};

// Constructor
String *string_new();

#endif
