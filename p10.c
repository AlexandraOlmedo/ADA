#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 4
#define MAX_WEIGHT 4

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    // Datos de los objetos
    char *items[MAX_ITEMS] = {"Guitarra", "Estéreo", "Laptop", "iPhone"};
    int weights[MAX_ITEMS] = {1, 4, 3, 1};
    int values[MAX_ITEMS] = {1500, 3000, 2000, 2000};

    int dp[MAX_ITEMS + 1][MAX_WEIGHT + 1];

    // Llenado de la tabla con explicación paso a paso
    printf("Llenado paso a paso de la tabla DP:\n\n");
    for (int i = 0; i <= MAX_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                int incluir = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int excluir = dp[i - 1][w];
                dp[i][w] = max(incluir, excluir);

                printf("dp[%d][%d] -> máx(incluir %s = $%d + dp[%d][%d] = $%d, excluir = $%d) = $%d\n",
                       i, w,
                       items[i - 1], values[i - 1], i - 1, w - weights[i - 1], dp[i - 1][w - weights[i - 1]],
                       excluir, dp[i][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
                printf("dp[%d][%d] -> %s no cabe (peso %d > %d), se queda $%d\n",
                       i, w, items[i - 1], weights[i - 1], w, dp[i][w]);
            }
        }
    }

    // Imprimir la tabla completa al final
    printf("\nTabla final DP (valores máximos por subproblema):\n\n");

    printf("     ");
    for (int w = 0; w <= MAX_WEIGHT; w++) {
        printf("%4d", w);
    }
    printf("  <-- capacidad\n");

    for (int i = 0; i <= MAX_ITEMS; i++) {
        if (i == 0)
            printf("  0 ");
        else
            printf("%3d ", i);
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            printf("%4d", dp[i][w]);
        }
        if (i > 0) printf("  <-- %s", items[i - 1]);
        printf("\n");
    }

    // Mostrar valor máximo
    printf("\nValor máximo: $%d\n", dp[MAX_ITEMS][MAX_WEIGHT]);

    // Recuperar los objetos seleccionados
    printf("Objetos seleccionados:\n");
    int w = MAX_WEIGHT;
    for (int i = MAX_ITEMS; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("- %s (valor: $%d, peso: %dlb)\n", items[i - 1], values[i - 1], weights[i - 1]);
            w -= weights[i - 1];
        }
    }

    return 0;
}