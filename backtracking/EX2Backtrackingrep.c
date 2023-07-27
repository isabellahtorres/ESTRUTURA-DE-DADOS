//Isabella Torres e João Victor Spala
//todas as combinações de {15, 31, 55, 44}, de tamanho n, cuja a soma dos elementos da combinação é par
#include <stdio.h>
#include <stdlib.h>
void imprimirCombinacoes(int *vet, int pos, int n, int *vetAux) {
  int i;
  if (pos == n) {
    int soma = 0;
    for (i = 0; i < n; i++) {
      soma += vet[i];
    }
    if (soma % 2 == 0) {
      for (i = 0; i < 4; i++) {
        printf("%d ", vet[i]);
      }
      printf("\n");
    }
  } else {
    for (i = 0; i <= 3; i++) {
      vet[pos] = vetAux[i];
      imprimirCombinacoes(vet, pos + 1, n, vetAux);
    }
  }
}

int main(void) {
  int n;
  int vetAux[] = {15, 31, 55, 44};
  printf("digite o tamanho do vetor\n");
  scanf("%d", &n);

  int *vetor = (int *)malloc(n * sizeof(int));
  if (vetor == NULL) {
    puts("erro");
    return 1;
  }

  imprimirCombinacoes(vetor, 0, n, vetAux);
  free(vetor);
  return 0;
}
