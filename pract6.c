#include <stdio.h>
#include <stdbool.h>

// Alumno:Olmedo Garduño Alexandra

#define MAX_TERMS 1000

// Función para verificar si un número es primo
bool esPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Genera la secuencia de Fibonacci modificada (sin posiciones primas)
int generarFibonacciFiltrado(int fib[], int K) {
    int a = 0, b = 1, c;
    int index = 1, count = 0;
    while (a <= K) {
        if (!esPrimo(index)) {
            fib[count++] = a;
        }
        c = a + b;
        a = b;
        b = c;
        index++;
    }
    return count;
}

// Algoritmo para obtener el mínimo número de términos de Fibonacci que suman K
int obtenerMinimoFibonacci(int fib[], int size, int K, int resultado[]) {
    int count = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (fib[i] <= K) {
            K -= fib[i];
            resultado[count++] = fib[i];
        }
        if (K == 0) break;
    }
    return count;
}

int main() {
    int dia, mes, anio;
    int K, opcion;

    printf("Calculadora de Mínimos Términos de Fibonacci\n");
    printf("¿Cómo deseas ingresar K?\n");
    printf("1. Calcular a partir de fecha de nacimiento\n");
    printf("2. Ingresar K manualmente\n");
    printf("Opción (1 o 2): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Ingresa tu día de nacimiento (DD): ");
        scanf("%d", &dia);
        printf("Ingresa tu mes de nacimiento (MM): ");
        scanf("%d", &mes);
        printf("Ingresa tu año de nacimiento (YYYY): ");
        scanf("%d", &anio);

        K = dia * 100 + mes * 10 + (anio % 100);
        printf("K calculado: %d\n", K);
    } else if (opcion == 2) {
        printf("Ingresa el valor de K: ");
        scanf("%d", &K);
    } else {
        printf("Opción inválida.\n");
        return 1;
    }

    int fib[MAX_TERMS], resultado[MAX_TERMS];
    int tamFib = generarFibonacciFiltrado(fib, K);

    printf("\nSecuencia de Fibonacci filtrada (sin posiciones primas):\n");
    for (int i = 0; i < tamFib; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n\n");

    int cantidad = obtenerMinimoFibonacci(fib, tamFib, K, resultado);

    printf("Mínimo número de términos que suman %d:\n", K);
    for (int i = 0; i < cantidad; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\nCantidad de términos: %d\n", cantidad);

    return 0;
}
