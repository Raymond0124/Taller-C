#include <stdio.h>
#include <stdlib.h>

int *copyArray(const int *values, int size)
{
    if (values == NULL || size <= 0) {
        return NULL;
    }

    int *copy = malloc((size_t)size * sizeof *copy);
    if (copy == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        copy[i] = values[i];
    }

    return copy;
}

/* Ordena ascendentemente, in situ, por inserción. */
void insertionSort(int *a, int size)
{
    for (int i = 1; i < size; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];     /* desplaza hacia la derecha */
            j--;
        }
        a[j + 1] = key;          /* inserta en su posición */
    }
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

    int *sorted = copyArray(original, size);
    if (sorted == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return EXIT_FAILURE;
    }

    insertionSort(sorted, size);

    printArray("Original", original, size);
    printArray("Ordenado", sorted, size);

    free(sorted);
    sorted = NULL;

    return EXIT_SUCCESS;
}

