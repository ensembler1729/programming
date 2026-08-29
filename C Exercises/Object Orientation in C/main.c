#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CustomString.h"

struct Point {
    double x;
    double y;

    void (*del)(const struct Point *self);
    void (*dump)(const struct Point *self);
    double (*origin)(const struct Point *self);
};

void point_dump(const struct Point *self) {
    printf("Object Point@%p x=%f y=%f\n", self, self->x, self->y);
}

void point_del(const struct Point *self) { free((void *)self); }

double point_origin(const struct Point *self) {
    return sqrt(self->x * self->x + self->y * self->y);
}

struct Point *point_new(double x, double y) {
    struct Point *p = malloc(sizeof(*p));
    p->x = x;
    p->y = y;
    p->dump = &point_dump;
    p->origin = &point_origin;
    p->del = &point_del;
    return p;
}

int main() {

    // Point
    struct Point *pt = point_new(4.0, 3.0);
    pt->dump(pt);
    printf("Origin %f\n", pt->origin(pt));
    pt->del(pt);

    // String
    String *str = string_new();
    str_append(str, 'H');
    str_appends(str, "ello World!");
    dump(str);
    printf("String Data: %s\n", get_str(str));

    str_assign(str, "String Implementation.");
    dump(str);
    printf("String Data: %s\n", get_str(str));

    char string[30];
    printf("Enter the string: ");
    if (fgets(string, sizeof(string), stdin) == NULL)
        return 0;
    string[strcspn(string, "\n")] = '\0';

    str_assign(str, string);
    dump(str);
    printf("String Data: %s\n", get_str(str));

    string_delete(str);
    return 0;
}
