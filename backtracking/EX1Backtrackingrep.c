//Isabella Torres e João Victor Spala
//todas as combinações de {a, e, i, o, u}, de tamanho n, que o numero de a's é maior que a soma totais de e's e i's.
#include <stdio.h>
#include <stdlib.h>

void imprimirCombinacoes(char *vet, int pos, int n, char *vetAux) {
  int i;
  if (pos == n) {
    int contA = 0, contI = 0, contE = 0;
    for (i = 0; i < n; i++) {
      switch (vet[i]) {
      case 'a':
        contA++;
        break;
      case 'i':
        contI++;
        break;
      case 'e':
        contE++;
        break;
      }
    }
    for (i = 0; i < n; i++) {
      if (contA > contI && contA > contE) {
        printf("%c", vet[i]);
        if (i == n - 1)
          printf("\n");
      }
    }
  } else {
    for (i = 0; i <= 2; i++) {
      vet[pos] = vetAux[i];
      imprimirCombinacoes(vet, pos + 1, n, vetAux);
    }
  }
}

int main(void) {
  int n;
  char vetAux[] = {'a', 'e', 'i'};
  printf("digite o tamanho do vetor\n");
  scanf("%d", &n);

  char *vetor = (char *)malloc(n * sizeof(char));
  if (vetor == NULL) {
    puts("erro");
    return 1;
  }

  imprimirCombinacoes(vetor, 0, n, vetAux);
  free(vetor);
  return 0;
}
