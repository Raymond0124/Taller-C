#include <stdio.h>
#include <stdlib.h>

int *copyArray(const int *values, int size)
{
    if (values == NULL || size <= 0) {
        return NULL;
    }

    int *copy = malloc((size_t)size * sizeof *copy);
    if (copy == NULL) {          /* la reserva falló */
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        copy[i] = values[i];
    }

    return copy;                 /* el llamador es dueño de este bloque */
}

static void printArray(const char *label, const int *a, int size)
{
    printf("%s: [", label);
    for (int i = 0; i < size; i++) {
        printf("%d%s", a[i], (i < size - 1) ? ", " : "");
    }
    printf("]\n");
}

int main(void)
{
    const int original[] = {4, -2, 0, 7, -5};
    const int size = (int)(sizeof original / sizeof original[0]);

    int *copy = copyArray(original, size);
    if (copy == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return EXIT_FAILURE;
    }

    copy[0] = 99;

    printArray("Original", original, size);
    printArray("Copia", copy, size);

    free(copy);
    copy = NULL;

    return EXIT_SUCCESS;
}

