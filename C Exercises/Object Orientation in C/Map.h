#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H

typedef struct MapEntry MapEntry;
typedef struct Map Map;
typedef struct MapIter MapIter;

struct MapEntry {
    char *key;
    int value;
    MapEntry *__prev;
    MapEntry *__next;
};

struct Map {
    struct MapEntry *__head;
    struct MapEntry *__tail;
    int __count;

    void (*put)(Map *self, char *key, int value);
    int (*get)(const Map *self, char *key, int def);
    int (*size)(const Map *self);
    MapIter *(*iter)(const Map *self);
    void (*print)(const Map *self);
    void (*del)(const Map *self);
};

Map *Map_new();

struct MapIter {
    MapEntry *__current;

    MapEntry *(*next)(MapIter *self);
    void (*del)(const MapIter *self);
};

#endif
