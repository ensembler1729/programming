#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CustomList.h"
#include "CustomString.h"

int main() {

    // String
    String *str = string_new();
    str->append(str, 'S');
    str->appends(str, "herlock Holmes");
    str->print(str);
    printf("String Data: %s\n", str->get_string(str));

    printf("\n");

    str->assign(str, "John Watson");
    str->print(str);
    printf("String Data: %s\n", str->get_string(str));

    printf("\n");

    char string[31];
    printf("Enter the string: ");
    if (fgets(string, sizeof(string), stdin) == NULL)
        return 0;
    string[strcspn(string, "\n")] = '\0';

    str->assign(str, string);
    str->print(str);
    printf("String Data: %s\n", str->get_string(str));

    printf("\n");

    // List
    List *list = list_new();
    list->append(list, "Zero");
    list->append(list, "One");
    list->append(list, "Two");
    list->print(list);
    list->append(list, "Three");
    list->append(list, "Four");
    list->print(list);
    printf("Size of list: %d\n", list->get_length(list));
    printf("Index of `Three`: %d\n", list->index(list, "Three"));
    printf("Index of NULL: %d\n", list->index(list, NULL));
    printf("Index of `Six`: %d\n", list->index(list, "Six"));
    list->append(list, "Five");
    list->append(list, "Six");
    list->append(list, "Seven");
    list->append(list, "Eight");
    list->print(list);
    printf("Size of list: %d\n", list->get_length(list));
    printf("Index of `Seven`: %d\n", list->index(list, "Seven"));

    str->del(str);
    list->del(list);
    return 0;
}
