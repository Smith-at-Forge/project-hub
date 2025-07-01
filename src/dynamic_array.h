#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>// size_t

typedef struct {
    int* data;
    size_t size;// Anzahl der Elemente im Array
    size_t capacity;//maximal mögliche Anzahl, bevor es vergroessert werden muss
} dynamic_array;

dynamic_array create_dynamic_array(void);
void add_to_dynamic_array(dynamic_array* array, int value);
void clear_dynamic_array(dynamic_array* array);

#endif
