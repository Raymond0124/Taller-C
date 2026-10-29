#include <stdio.h>
#include <stdlib.h>

/* leftMax[i] = mayor altura en height[0..i] */
void buildLeftMax(const int *height, int size, int *leftMax)
{
    if (height == NULL || leftMax == NULL || size <= 0) {
        return;
    }

    leftMax[0] = height[0];
    for (int i = 1; i < size; i++) {
        leftMax[i] = (height[i] > leftMax[i - 1]) ? height[i] : leftMax[i - 1];
    }
}

/* rightMax[i] = mayor altura en height[i..size-1] */
void buildRightMax(const int *height, int size, int *rightMax)
{
    if (height == NULL || rightMax == NULL || size <= 0) {
        return;
    }

    rightMax[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        rightMax[i] = (height[i] > rightMax[i + 1]) ? height[i] : rightMax[i + 1];
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

long long trappedWater(const int *height, int size)
{
    if (height == NULL || size < 0) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }

    int *leftMax  = malloc((size_t)size * sizeof *leftMax);
    int *rightMax = malloc((size_t)size * sizeof *rightMax);

    if (leftMax == NULL || rightMax == NULL) {
        free(leftMax);               /* free(NULL) es seguro */
        free(rightMax);
        return -1;
    }

    buildLeftMax(height, size, leftMax);
    buildRightMax(height, size, rightMax);

    long long total = 0;
    for (int i = 0; i < size; i++) {
        int level = (leftMax[i] < rightMax[i]) ? leftMax[i] : rightMax[i];
        total += (long long)(level - height[i]);
    }

    free(leftMax);
    free(rightMax);
    return total;
}

static void printArray(const char *label, const int *a, int size)
{
    printf("%-9s [", label);
    for (int i = 0; i < size; i++) {
        printf("%d%s", a[i], (i < size - 1) ? ", " : "");
    }
    printf("]\n");
}

/* Muestra alturas, máximos y agua por posición (para revisión). */
static int showDetail(const int *height, int size)
{
    int *leftMax  = malloc((size_t)size * sizeof *leftMax);
    int *rightMax = malloc((size_t)size * sizeof *rightMax);
    int *water    = malloc((size_t)size * sizeof *water);

    if (leftMax == NULL || rightMax == NULL || water == NULL) {
        free(leftMax);
        free(rightMax);
        free(water);
        return -1;
    }

    buildLeftMax(height, size, leftMax);
    buildRightMax(height, size, rightMax);

    for (int i = 0; i < size; i++) {
        int level = (leftMax[i] < rightMax[i]) ? leftMax[i] : rightMax[i];
        water[i] = level - height[i];
    }

    printArray("height",   height,   size);
    printArray("leftMax",  leftMax,  size);
    printArray("rightMax", rightMax, size);
    printArray("water",    water,    size);

    free(leftMax);
    free(rightMax);
    free(water);
    return 0;
}

static int runCase(const int *height, int size, long long expected)
{
    int copy[32];
    for (int i = 0; i < size; i++) copy[i] = height[i];

    long long got = trappedWater(height, size);

    /* Las alturas originales deben conservarse */
    int intact = 1;
    for (int i = 0; i < size; i++) {
        if (height[i] != copy[i]) intact = 0;
    }

    int ok = (got == expected) && intact;
    printf("  esperado=%lld  obtenido=%lld  originales intactas=%s  -> %s\n",
           expected, got, intact ? "si" : "no", ok ? "OK" : "FALLO");
    return ok;
}

int main(void)
{
    const int c1[] = {5};
    const int c2[] = {0, 1, 2, 3};
    const int c3[] = {3, 2, 1, 0};
    const int c4[] = {2, 2, 2};
    const int c5[] = {3, 0, 3};
    const int c6[] = {3, 0, 2, 0, 4};
    const int c7[] = {4, 2, 0, 3, 2, 5};
    const int c8[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    const int c9[] = {5, 1, 2, 1, 4, 0, 3};   /* caso propio */

    struct { const int *h; int n; long long exp; const char *name; } tests[] = {
        { c1, 1,  0, "[5]" },
        { c2, 4,  0, "[0, 1, 2, 3]" },
        { c3, 4,  0, "[3, 2, 1, 0]" },
        { c4, 3,  0, "[2, 2, 2]" },
        { c5, 3,  3, "[3, 0, 3]" },
        { c6, 5,  7, "[3, 0, 2, 0, 4]" },
        { c7, 6,  9, "[4, 2, 0, 3, 2, 5]" },
        { c8, 12, 6, "[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]" },
        { c9, 7, 12, "[5, 1, 2, 1, 4, 0, 3]  (caso propio)" },
    };
    const int ntests = (int)(sizeof tests / sizeof tests[0]);

    int passed = 0;
    for (int t = 0; t < ntests; t++) {
        printf("Caso %d: %s\n", t + 1, tests[t].name);
        passed += runCase(tests[t].h, tests[t].n, tests[t].exp);
    }
    printf("\nResultado: %d/%d casos correctos\n", passed, ntests);

    printf("\n===== Detalle por posicion: [4, 2, 0, 3, 2, 5] =====\n");
    if (showDetail(c7, 6) != 0) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return EXIT_FAILURE;
    }

    printf("\n===== Detalle por posicion: caso propio =====\n");
    if (showDetail(c9, 7) != 0) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return EXIT_FAILURE;
    }

    return (passed == ntests) ? EXIT_SUCCESS : EXIT_FAILURE;
}

