#include <stdio.h>
#include <stdlib.h>

int fibonacci (int n){
	if (n == 1 || n == 0) return n;

	return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("No se encontro ningun valor valido");
		return -1;
	}
	int n = atoi(argv[1]);
	int resultado = fibonacci(n);
	printf ("\n\tResltado: Fibonacci(%d) = %d\n", n, resultado);
}
