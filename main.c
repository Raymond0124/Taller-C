
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


// Funcion para imprimir arreglos

void printArray(const char *nombre, const int *arreglo, int tamano) {
    printf("%s: [", nombre);

    for (int i = 0; i < tamano; i++) {
        printf("%d", arreglo[i]);

        if (i < tamano - 1) {
            printf(", ");
        }
    }

    printf("]\n");
}


// Ejercicio 3: Copia independiente

int *copyArray(const int *values, int size) {
    if (values == NULL || size <= 0) {
        return NULL;
    }

    int *copia = malloc(size * sizeof(int));

    if (copia == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        copia[i] = values[i];
    }

    return copia;
}


// Ejercicio 4: Ordenar una copia

void sortAscending(int *values, int size) {
    for (int i = 1; i < size; i++) {
        int actual = values[i];
        int j = i - 1;

        while (j >= 0 && values[j] > actual) {
            values[j + 1] = values[j];
            j--;
        }

        values[j + 1] = actual;
    }
}


// Ejercicio 5: Buscar dos numeros que sumen un objetivo

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

    // Crear una copia para conservar el arreglo original
    int *copia = copyArray(values, size);

    if (copia == NULL) {
        return -1;
    }

    // Ordenar la copia
    sortAscending(copia, size);

    int cantidad = 0;

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

                // Saltar valores repetidos
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

    free(copia);

    return cantidad;
}


// Ejercicio 7: Maximos desde ambos extremos

void buildLeftMax(const int *height, int size, int *leftMax) {
    if (height == NULL || leftMax == NULL || size <= 0) {
        return;
    }

    leftMax[0] = height[0];

    for (int i = 1; i < size; i++) {
        if (height[i] > leftMax[i - 1]) {
            leftMax[i] = height[i];
        } else {
            leftMax[i] = leftMax[i - 1];
        }
    }
}

void buildRightMax(const int *height, int size, int *rightMax) {
    if (height == NULL || rightMax == NULL || size <= 0) {
        return;
    }

    rightMax[size - 1] = height[size - 1];

    for (int i = size - 2; i >= 0; i--) {
        if (height[i] > rightMax[i + 1]) {
            rightMax[i] = height[i];
        } else {
            rightMax[i] = rightMax[i + 1];
        }
    }
}


// Ejercicio 8: Agua atrapada

long long trappedWater(const int *height, int size) {
    if (height == NULL || size < 0) {
        return -1;
    }

    if (size == 0) {
        return 0;
    }

    int *leftMax = malloc(size * sizeof(int));
    int *rightMax = malloc(size * sizeof(int));

    if (leftMax == NULL || rightMax == NULL) {
        free(leftMax);
        free(rightMax);
        return -1;
    }

    buildLeftMax(height, size, leftMax);
    buildRightMax(height, size, rightMax);

    long long total = 0;

    for (int i = 0; i < size; i++) {
        int nivel;

        if (leftMax[i] < rightMax[i]) {
            nivel = leftMax[i];
        } else {
            nivel = rightMax[i];
        }

        total += nivel - height[i];
    }

    free(leftMax);
    free(rightMax);

    return total;
}


// Mostrar el agua atrapada en cada posicion

int showDetail(const int *height, int size) {
    int *leftMax = malloc(size * sizeof(int));
    int *rightMax = malloc(size * sizeof(int));
    int *agua = malloc(size * sizeof(int));

    if (leftMax == NULL || rightMax == NULL || agua == NULL) {
        free(leftMax);
        free(rightMax);
        free(agua);
        return -1;
    }

    buildLeftMax(height, size, leftMax);
    buildRightMax(height, size, rightMax);

    for (int i = 0; i < size; i++) {
        int nivel;

        if (leftMax[i] < rightMax[i]) {
            nivel = leftMax[i];
        } else {
            nivel = rightMax[i];
        }

        agua[i] = nivel - height[i];
    }

    printArray("Alturas", height, size);
    printArray("leftMax", leftMax, size);
    printArray("rightMax", rightMax, size);
    printArray("Agua", agua, size);

    free(leftMax);
    free(rightMax);
    free(agua);

    return 0;
}


// Comprobar los casos del ejercicio 8

int runCase(const int *height, int size, long long esperado) {
    int *copia = copyArray(height, size);

    if (copia == NULL) {
        printf("Error al reservar memoria\n");
        return 0;
    }

    long long obtenido = trappedWater(height, size);

    int intacto = 1;

    for (int i = 0; i < size; i++) {
        if (height[i] != copia[i]) {
            intacto = 0;
        }
    }

    int correcto = (obtenido == esperado && intacto);

    printf("Esperado: %lld | Obtenido: %lld | Original intacto: %s | %s\n",
           esperado, obtenido,
           intacto ? "si" : "no",
           correcto ? "OK" : "FALLO");

    free(copia);

    return correcto;
}


// Programa principal

int main(void) {

    // Ejercicio 1
    printf("EJERCICIO 1\n");

    int a = 8;
    int b = -3;

    printf("Antes: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("Despues: a = %d, b = %d\n", a, b);


    // Ejercicio 2
    printf("\nEJERCICIO 2\n");

    int numeros[] = {4, -2, 0, 7, -5};
    int tamano = sizeof(numeros) / sizeof(numeros[0]);

    printf("Suma: %d\n", sumarArreglo(numeros, tamano));
    printf("Minimo: %d\n", buscarMinimo(numeros, tamano));
    printf("Maximo: %d\n", buscarMaximo(numeros, tamano));
    printf("Negativos: %d\n", contarNegativos(numeros, tamano));

    printf("Inverso: ");
    imprimirInverso(numeros, tamano);


    // Ejercicio 3
    printf("\nEJERCICIO 3\n");

    int *copia = copyArray(numeros, tamano);

    if (copia == NULL) {
        printf("Error al crear la copia\n");
        return 1;
    }

    copia[0] = 99;

    printArray("Original", numeros, tamano);
    printArray("Copia", copia, tamano);

    free(copia);


    // Ejercicio 4
    printf("\nEJERCICIO 4\n");

    int *ordenado = copyArray(numeros, tamano);

    if (ordenado == NULL) {
        printf("Error al crear la copia\n");
        return 1;
    }

    sortAscending(ordenado, tamano);

    printArray("Original", numeros, tamano);
    printArray("Ordenado", ordenado, tamano);

    free(ordenado);


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

    int cantidadTernas;

    printf("Caso 1:\n");
    cantidadTernas = threeSum(caso1, 6);
    printf("Cantidad: %d\n", cantidadTernas);

    printf("Caso 2:\n");
    cantidadTernas = threeSum(caso2, 3);
    printf("Cantidad: %d\n", cantidadTernas);

    printf("Caso 3:\n");
    cantidadTernas = threeSum(caso3, 3);
    printf("Cantidad: %d\n", cantidadTernas);

    printf("Caso 4:\n");
    cantidadTernas = threeSum(caso4, 4);
    printf("Cantidad: %d\n", cantidadTernas);

    printf("Caso 5:\n");
    cantidadTernas = threeSum(caso5, 5);
    printf("Cantidad: %d\n", cantidadTernas);


    // Ejercicio 7
    printf("\nEJERCICIO 7\n");

    int alturas[] = {3, 0, 2, 0, 4};
    int leftMax[5];
    int rightMax[5];

    buildLeftMax(alturas, 5, leftMax);
    buildRightMax(alturas, 5, rightMax);

    printArray("Alturas", alturas, 5);
    printArray("leftMax", leftMax, 5);
    printArray("rightMax", rightMax, 5);


    // Ejercicio 8
    printf("\nEJERCICIO 8\n");

    const int c1[] = {5};
    const int c2[] = {0, 1, 2, 3};
    const int c3[] = {3, 2, 1, 0};
    const int c4[] = {2, 2, 2};
    const int c5[] = {3, 0, 3};
    const int c6[] = {3, 0, 2, 0, 4};
    const int c7[] = {4, 2, 0, 3, 2, 5};
    const int c8[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    const int c9[] = {5, 1, 2, 1, 4, 0, 3};

    int correctos = 0;

    printf("Caso 1: ");
    correctos += runCase(c1, 1, 0);

    printf("Caso 2: ");
    correctos += runCase(c2, 4, 0);

    printf("Caso 3: ");
    correctos += runCase(c3, 4, 0);

    printf("Caso 4: ");
    correctos += runCase(c4, 3, 0);

    printf("Caso 5: ");
    correctos += runCase(c5, 3, 3);

    printf("Caso 6: ");
    correctos += runCase(c6, 5, 7);

    printf("Caso 7: ");
    correctos += runCase(c7, 6, 9);

    printf("Caso 8: ");
    correctos += runCase(c8, 12, 6);

    printf("Caso 9 (propio): ");
    correctos += runCase(c9, 7, 11);

    printf("\nResultado: %d/9 casos correctos\n", correctos);


    // Detalle del agua en cada posicion
    printf("\nDetalle de [4, 2, 0, 3, 2, 5]:\n");

    if (showDetail(c7, 6) == -1) {
        printf("Error de memoria\n");
        return 1;
    }

    printf("\nDetalle del caso propio:\n");

    if (showDetail(c9, 7) == -1) {
        printf("Error de memoria\n");
        return 1;
    }

    if (correctos != 9) {
        return 1;
    }

    return 0;
}
