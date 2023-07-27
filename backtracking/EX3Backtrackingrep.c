//Isabella Torres e João Victor Spala
//dado um valor em centavos, imprimir todas as maneiras de representá-lo utilizando moedas de 1, 5, 10, 25 e 50 centavos
#include <stdio.h>
#include <stdlib.h>

int calcularTotal(int *vet) {
  int total = 0;
  for (int i = 0; i <= 4; i++) {
    switch (i) {
    case 0:
      total += 1 * vet[i];
      break;
    case 1:
      total += 5 * vet[i];
      break;
    case 2:
      total += 10 * vet[i];
      break;
    case 3:
      total += 25 * vet[i];
      break;
    case 4:
      total += 50 * vet[i];
      break;
    }
  }
  return total;
}

void imprimirCombinacoes(int *vet, int pos, int valor, int *moedas) {
  int i;
  int total = calcularTotal(vet);
  if (total == valor) {
    for (i = 0; i <= 4; i++) {
      printf("%d ", vet[i]);
    }
    printf("\n");
  } else {
    if (pos <= 4) {
      for (i = 0; i <= (valor - total) / moedas[pos]; i++) {
        vet[pos] = i;
        imprimirCombinacoes(vet, pos + 1, valor, moedas);
        vet[pos] = 0;
      }
    }
  }
}


int main(void) {
  int valor;
  printf("digite o valor em centavos\n");
  scanf("%d", &valor);
  
  int moedas[] = {1, 5, 10, 25, 50};

  int *vetor = (int *)malloc(valor * sizeof(int));
  if (vetor == NULL) {
    puts("erro");
    return 1;
  }

  imprimirCombinacoes(vetor, 0, valor, moedas);
  free(vetor);
  return 0;
}
