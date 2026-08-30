#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

typedef struct LNode LNode;
typedef struct List List;

struct LNode {
    char *text;
    LNode *next;
};

struct List {
    LNode *head;
    LNode *tail;
    int count;

    int (*get_length)(const List *self);

    void (*append)(List *self, char *str);

    // -1 if not found
    int (*index)(const List *self, char *str);

    void (*print)(const List *self);

    // Destructor
    void (*del)(const List *self);
};

// Constructor
List *list_new();

#endif
