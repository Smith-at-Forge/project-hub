#include "dynamic_array.h"
#include <stdio.h>// printf
#include <string.h>// memcpy
/*
Diese Datei vereint dynamic_array.c und Hauptprogramm.
Um mit zwei Dateien zu arbeiten, setzen Sie SWITCH = 0.
    Das habe ich schon gemacht und das Ergebnis in "aufgabe-3.exe" gespeichert.
    Sie können also auch direkt "aufgabe-3.exe" starten.
*/
#define SWITCH 1
#if SWITCH
static void grow(dynamic_array* array);

dynamic_array create_dynamic_array(void) {
    dynamic_array new_array;
    new_array.data = NULL;
    new_array.size = 0;
    new_array.capacity = 0;
    return new_array;
}

void add_to_dynamic_array(dynamic_array* array, int value) {
    if (array->size >= array->capacity) {
        grow(array);
    }
    array->data[array->size] = value;
    array->size++;
}
// gibt Speicherbereich wieder frei
void clear_dynamic_array(dynamic_array* array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

static void grow(dynamic_array* array) {
    size_t new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;
    int* new_data = (int*)malloc(new_capacity * sizeof(int));

    if (new_data == NULL) {
        // validiere Eingabe
        fprintf(stderr, "Funktion 'grow' fehlgeschlagen\n");
        exit(EXIT_FAILURE);
    }

    if (array->data != NULL) {
        memcpy(new_data, array->data, array->size * sizeof(int));
        free(array->data);
    }

    array->data = new_data;
    array->capacity = new_capacity;
}
#endif // SWITCH
// Hauptprogramm für den Test
int main() {
    dynamic_array my_array = create_dynamic_array();
    int input;

    printf("Geben Sie Zahlen ein (ungueltige Eingabe zum Beenden):\n");
    while (scanf("%d", &input) == 1) {
        add_to_dynamic_array(&my_array, input);
    }

    printf("Eingegebene Zahlen:");
    for (size_t i = 0; i < my_array.size; i++) {
        printf(" %d", my_array.data[i]);
    }
    printf("\n");

    clear_dynamic_array(&my_array);

    return 0;
}
