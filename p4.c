#include <stdio.h>

// Esta función ordena el arreglo de habilidades usando el método de burbuja
void ordenar(int arreglo[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Compara los elementos del arreglo de dos en dos
        for (int j = 0; j < n - i - 1; j++) {
            // Si el elemento actual es mayor que el siguiente, los intercambia
            if (arreglo[j] > arreglo[j + 1]) {
                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

// Aquí es donde se dividen los jugadores en dos equipos
int dividirJugadores(int skills[], int n) {
    // Primero, ordenamos las habilidades para hacer los emparejamientos
    ordenar(skills, n);
    
    // Usamos dos punteros: uno al principio y otro al final del arreglo
    int izquierda = 0, derecha = n - 1;
    
    // Sumamos las habilidades del jugador más bajo y el más alto
    int suma_total = skills[izquierda] + skills[derecha];
    int quimica_total = 0;
    
    printf("Equipos formados:\n");
    
    // Mientras los punteros no se crucen, formamos parejas
    while (izquierda < derecha) {
        printf("(%d, %d) = %d + %d = %d\n", skills[izquierda], skills[derecha], skills[izquierda], skills[derecha], skills[izquierda] + skills[derecha]);
        
        // Si las sumas no son iguales, entonces no podemos formar equipos balanceados
        if (skills[izquierda] + skills[derecha] != suma_total) {
            printf("No es posible formar equipos con la misma suma de habilidades.\n");
            return -1;
        }
        
        // Sumamos la "química" (multiplicación de habilidades)
        quimica_total += skills[izquierda] * skills[derecha];
        
        // Movemos los punteros
        izquierda++;
        derecha--;
    }
    
    // Imprimimos cómo se calculó la química total
    printf("Cálculo de química total: ");
    izquierda = 0;
    derecha = n - 1;
    int primer_termino = 1;
    
    // Aquí imprimimos las multiplicaciones para el cálculo de la química
    while (izquierda < derecha) {
        if (!primer_termino) {
            printf(" + ");
        }
        printf("(%d * %d)", skills[izquierda], skills[derecha]);
        primer_termino = 0;
        izquierda++;
        derecha--;
    }
    
    // Mostramos el resultado final
    printf(" = %d\n", quimica_total);
    
    return quimica_total;
}

int main() {
    int n;
    // Le pedimos al usuario que ingrese el número de jugadores (que debe ser par)
    printf("Ingrese la cantidad de jugadores (debe ser un número par): ");
    scanf("%d", &n);
    
    // Si el número de jugadores no es par, terminamos el programa
    if (n % 2 != 0) {
        printf("El número de jugadores debe ser par.\n");
        return 1;
    }
    
    // Creamos un arreglo para guardar las habilidades de los jugadores
    int skills[n];
    
    // Pedimos al usuario que ingrese las habilidades de cada jugador
    for (int i = 0; i < n; i++) {
        printf("Ingrese la habilidad del jugador %d: ", i + 1);
        scanf("%d", &skills[i]);
    }
    
    // Llamamos a la función para dividir los jugadores y calculamos la química total
    int resultado = dividirJugadores(skills, n);
    
    // Imprimimos la química total de los equipos
    printf("La química total de los equipos es: %d\n", resultado);
    
    return 0;
}
