#include <stdio.h>

int es_palindromo(int num) {
    if (num < 0) return 0; // Los números negativos no son palíndromos
    
    int original = num;
    int invertido = 0;

    while (num > 0) {
        int digito = num % 10; // Extrae el último dígito
        invertido = invertido * 10 + digito; // Construye el número invertido
        num /= 10; // Elimina el último dígito
    }

    return original == invertido;
}

int main() {
    int num;
    printf("Ingresa un número: ");
    scanf("%d", &num);

    if (es_palindromo(num)) {
        printf("%d es un número palíndromo.\n", num);
    } else {
        printf("%d no es un número palíndromo.\n", num);
    }

    return 0;
}
