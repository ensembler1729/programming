#ifndef CUSTOM_DICT_H
#define CUSTOM_DICT_H

typedef struct DNode DNode;
typedef struct Dictionary Dictionary;

struct DNode {
    char *key;
    char *value;
    DNode *next;
};

struct Dictionary {
    DNode *head;
    DNode *tail;
    int count;

    DNode *(*find)(const Dictionary *self, char *key);
    char *(*get)(const Dictionary *self, char *key);
    void (*put)(Dictionary *self, char *key, char *value);

    void (*print)(const Dictionary *self);

    // Destructor
    void (*del)(const Dictionary *self);
};

// Constructor
Dictionary *dict_new();

#endif
