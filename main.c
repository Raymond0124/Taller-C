
#include <stdio.h>
#include <stdlib.h>

// Ejercicio 1: Intercambio de valores

void swap(int *a, int *b) {
    int temporal = *a;
    *a = *b;
    *b = temporal;
}


// Ejercicio 2: Estadisticas de un arreglo

int sumarArreglo(const int valores[], int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += valores[i];
    }

    return suma;
}

int buscarMinimo(const int valores[], int tamano) {
    int minimo = valores[0];

    for (int i = 1; i < tamano; i++) {
        if (valores[i] < minimo) {
            minimo = valores[i];
        }
    }

    return minimo;
}

int buscarMaximo(const int valores[], int tamano) {
    int maximo = valores[0];

    for (int i = 1; i < tamano; i++) {
        if (valores[i] > maximo) {
            maximo = valores[i];
        }
    }

    return maximo;
}

int contarNegativos(const int valores[], int tamano) {
    int cantidad = 0;

    for (int i = 0; i < tamano; i++) {
        if (valores[i] < 0) {
            cantidad++;
        }
    }

    return cantidad;
}

void imprimirInverso(const int valores[], int tamano) {
    for (int i = tamano - 1; i >= 0; i--) {
        printf("%d ", valores[i]);
    }

    printf("\n");
}


// Ejercicio 5: Buscar dos valores que sumen el objetivo

int findPair(const int *values, int size, int target) {
    int izquierda = 0;
    int derecha = size - 1;

    while (izquierda < derecha) {
        int suma = values[izquierda] + values[derecha];

        if (suma == target) {
            printf("Un par valido es (%d, %d)\n",
                   values[izquierda], values[derecha]);
            return 1;
        }

        if (suma < target) {
            izquierda++;
        } else {
            derecha--;
        }
    }

    printf("No existe un par\n");
    return 0;
}


// Ejercicio 6: 3Sum

int threeSum(const int *values, int size) {
    if (size < 3) {
        return 0;
    }

    // Reservar memoria para una copia del arreglo
    int *copia = malloc(size * sizeof(int));

    if (copia == NULL) {
        return -1;
    }

    // Copiar los elementos para no modificar el original
    for (int i = 0; i < size; i++) {
        copia[i] = values[i];
    }

    // Ordenar la copia usando insercion
    for (int i = 1; i < size; i++) {
        int actual = copia[i];
        int j = i - 1;

        while (j >= 0 && copia[j] > actual) {
            copia[j + 1] = copia[j];
            j--;
        }

        copia[j + 1] = actual;
    }

    int cantidad = 0;

    // Elegir el primer numero de cada terna
    for (int i = 0; i < size - 2; i++) {

        // Evitar repetir el primer numero
        if (i > 0 && copia[i] == copia[i - 1]) {
            continue;
        }

        int izquierda = i + 1;
        int derecha = size - 1;

        while (izquierda < derecha) {
            int suma = copia[i] + copia[izquierda]
                       + copia[derecha];

            if (suma == 0) {
                printf("(%d, %d, %d)\n",
                       copia[i], copia[izquierda],
                       copia[derecha]);

                cantidad++;

                izquierda++;
                derecha--;

                // Saltar numeros repetidos
                while (izquierda < derecha &&
                       copia[izquierda] == copia[izquierda - 1]) {
                    izquierda++;
                }

                while (izquierda < derecha &&
                       copia[derecha] == copia[derecha + 1]) {
                    derecha--;
                }

            } else if (suma < 0) {
                izquierda++;
            } else {
                derecha--;
            }
        }
    }

    // Liberar la memoria utilizada
    free(copia);

    return cantidad;
}


// Pruebas de los ejercicios

int main(void) {

    // Ejercicio 1
    printf("EJERCICIO 1\n");

    int a = 8;
    int b = -3;

    printf("Antes: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("Despues: a = %d, b = %d\n\n", a, b);


    // Ejercicio 2
    printf("EJERCICIO 2\n");

    int numeros[] = {4, -2, 0, 7, -5};
    int tamano = sizeof(numeros) / sizeof(numeros[0]);

    printf("Suma: %d\n", sumarArreglo(numeros, tamano));
    printf("Minimo: %d\n", buscarMinimo(numeros, tamano));
    printf("Maximo: %d\n", buscarMaximo(numeros, tamano));
    printf("Negativos: %d\n", contarNegativos(numeros, tamano));

    printf("Inverso: ");
    imprimirInverso(numeros, tamano);


    // Ejercicio 5
    printf("\nEJERCICIO 5\n");

    int ordenados[] = {-4, -1, 0, 2, 5};

    findPair(ordenados, 5, 1);
    findPair(ordenados, 5, 8);

    int ceros[] = {0, 0};
    findPair(ceros, 2, 0);

    int uno[] = {3};
    findPair(uno, 1, 6);


    // Ejercicio 6
    printf("\nEJERCICIO 6\n");

    int caso1[] = {-1, 0, 1, 2, -1, -4};
    int caso2[] = {0, 1, 1};
    int caso3[] = {0, 0, 0};
    int caso4[] = {0, 0, 0, 0};
    int caso5[] = {-2, 0, 0, 2, 2};

    printf("Caso 1:\n");
    printf("Cantidad: %d\n", threeSum(caso1, 6));

    printf("Caso 2:\n");
    printf("Cantidad: %d\n", threeSum(caso2, 3));

    printf("Caso 3:\n");
    printf("Cantidad: %d\n", threeSum(caso3, 3));

    printf("Caso 4:\n");
    printf("Cantidad: %d\n", threeSum(caso4, 4));

    printf("Caso 5:\n");
    printf("Cantidad: %d\n", threeSum(caso5, 5));

    return 0;
}
