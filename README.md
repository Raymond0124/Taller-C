# Taller de C

## Integrantes
Iván Ignacio Brito Medina, Raymond Janfreed Araya Elizondo

Lenguaje: C

## Instrucciones de ejecución
Compilar y correr main.c

# Resultados de las pruebas
```
EJERCICIO 1
Antes: a = 8, b = -3
Despues: a = -3, b = 8

EJERCICIO 2
Suma: 4
Minimo: -5
Maximo: 7
Negativos: 2
Inverso: -5 7 0 -2 4

EJERCICIO 3
Original: [4, -2, 0, 7, -5]
Copia: [99, -2, 0, 7, -5]

EJERCICIO 4
Original: [4, -2, 0, 7, -5]
Ordenado: [-5, -2, 0, 4, 7]

EJERCICIO 5
Un par valido es (-4, 5)
No existe un par
Un par valido es (0, 0)
No existe un par

EJERCICIO 6
Caso 1:
(-1, -1, 2)
(-1, 0, 1)
Cantidad: 2
Caso 2:
Cantidad: 0
Caso 3:
(0, 0, 0)
Cantidad: 1
Caso 4:
(0, 0, 0)
Cantidad: 1
Caso 5:
(-2, 0, 2)
Cantidad: 1

EJERCICIO 7
Alturas: [3, 0, 2, 0, 4]
leftMax: [3, 3, 3, 3, 4]
rightMax: [4, 4, 4, 4, 4]

EJERCICIO 8
Caso 1: Esperado: 0 | Obtenido: 0 | Original intacto: si | OK
Caso 2: Esperado: 0 | Obtenido: 0 | Original intacto: si | OK
Caso 3: Esperado: 0 | Obtenido: 0 | Original intacto: si | OK
Caso 4: Esperado: 0 | Obtenido: 0 | Original intacto: si | OK
Caso 5: Esperado: 3 | Obtenido: 3 | Original intacto: si | OK
Caso 6: Esperado: 7 | Obtenido: 7 | Original intacto: si | OK
Caso 7: Esperado: 9 | Obtenido: 9 | Original intacto: si | OK
Caso 8: Esperado: 6 | Obtenido: 6 | Original intacto: si | OK
Caso 9 (propio): Esperado: 11 | Obtenido: 11 | Original intacto: si | OK

Resultado: 9/9 casos correctos

Detalle de [4, 2, 0, 3, 2, 5]:
Alturas: [4, 2, 0, 3, 2, 5]
leftMax: [4, 4, 4, 4, 4, 5]
rightMax: [5, 5, 5, 5, 5, 5]
Agua: [0, 2, 4, 1, 2, 0]

Detalle del caso propio:
Alturas: [5, 1, 2, 1, 4, 0, 3]
leftMax: [5, 5, 5, 5, 5, 5, 5]
rightMax: [5, 4, 4, 4, 4, 3, 3]
Agua: [0, 3, 2, 3, 0, 3, 0]

Process finished with exit code 0
```


# Explicaciones
## Ejercicio 1 - Punteros y alcance
Se utilizan punteros porque necesitamos modificar directamente los valores de las variables originales. Si modificamos a, solamente cambiamos la dirección que guarda el puntero dentro de la función, mientras que al modificar *a cambiamos el valor que está almacenado en esa dirección. La variable temporal es local, por lo que únicamente puede utilizarse dentro de swap.
## Ejercicio 3 - Copia independiete
Asignarle un puntero a otro no copia los elementos porque estos solo copian el valor de la dirección. Para hacer una copia real, falta reservar un nuevo bloque de memoria, recorrer el arreglo copiando cada elemento, y liberar los bloques de memoria previos.
## Ejercicio 5 - Búsqueda de pares
Como el arreglo está ordenado, podemos comenzar con un índice a cada extremo. Si la suma es menor que el objetivo, movemos el índice izquierdo para buscar un número más grande. Si la suma es mayor, movemos el derecho para buscar uno más pequeño. Así evitamos revisar todas las combinaciones posibles.
## Ejercicio 6 - 3Sum
Primero se crea una copia del arreglo y se ordena. Después se toma un número fijo y se buscan otros dos que permitan completar la suma cero. Para evitar resultados repetidos, se saltan los valores iguales tanto al seleccionar el primer número como después de encontrar una terna. De esta manera, cada combinación se imprime una sola vez.
## Ejercicios 7 y 8 - Agua atrapada
El agua depende del menor de los 2 máxmimos porque el agua se derramaría por el menor de los extremos, que sería analogo a la pared más baja de un recipiente que contiene el agua. Ambas condiciones son necesarias porque para que el agua pueda existir en un nivel, deben estar ambas paredes que lleguen al menos a ese nivel.

# Comparación entre el manejo de memoria de C y de Go
En C, el programador debe decidir cuando debe liberar la memoria manualmente, usando la función free(), mientras que en Go existe un Garbage Collector (GC), que libera la memoria automáticamente. 
Esto hace que las fugas de memoria sean mucho más difíciles de encontrar en Go, al costo de un mayor uso de memoria por el GC.
El programador reserva memoria con malloc() o calloc() en C, si estas funciones fallan, retornan NULL. En Go, se usan make y new, que si fallan, todo el programa aborta.
El programador puede eligir dónde vive la memoria en C (stack, heap, o estático), en Go, el compilador decide dónde van a estar las variables en la memoria.
En C, uno puede desbordarse del tamaño de los arreglos, lo cuál causa comportamiento indefinido, mientras que en Go, provoca un panic.
