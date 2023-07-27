// Isabella Torres e João Vitor Spala
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int totalElementos = 0;
int *heap;

int indiceFilhoEsq(int x) {
  int indice = (2 * x) + 1;
  if (x >= totalElementos || indice >= totalElementos)
    return -1;
  else
    return indice;
}

int indiceFilhoDir(int x) {
  int indice = (2 * x) + 2;
  if (x >= totalElementos || indice >= totalElementos)
    return -1;
  else
    return indice;
}

int indicePai(int x) {
  int indice = (x - 1) / 2;
  if (x <= 0 || x >= totalElementos)
    return -1;
  else
    return indice;
}

void ajustarSubindo(int *heap, int pos) {
  if (pos != -1) {
    int pai = indicePai(pos);
    if (pai != -1) {
      if (heap[pos] < heap[pai]) {
        int aux = heap[pos];
        heap[pos] = heap[pai];
        heap[pai] = aux;
        ajustarSubindo(heap, pai);
      }
    }
  }
}

void inserir(int *heap, int x) {
  heap[totalElementos] = x;
  totalElementos++;

  ajustarSubindo(heap, totalElementos - 1);
}

void ajustarDescendo(int *heap, int pos) {
  int menor = pos;
  int esquerda = indiceFilhoEsq(pos);
  int direita = indiceFilhoDir(pos);
  if (esquerda != -1 && heap[esquerda] < heap[menor])
    menor = esquerda;
  if (direita != -1 && heap[direita] < heap[menor])
    menor = direita;
  if (menor != pos) {
    int aux = heap[pos];
    heap[pos] = heap[menor];
    heap[menor] = aux;
    ajustarDescendo(heap, menor);
  }
}

int remover(int *heap) {
  if (totalElementos == 0)
    return -1;
  int heapAux = heap[0];
  printf("O item removido foi: %d\n", heap[0]);
  heap[0] = heap[totalElementos - 1];
  totalElementos--;
  ajustarDescendo(heap, 0);
  return heapAux;
}

void imprimeHeap(int *heap) {
  for (int i = 0; i < totalElementos; i++)
    printf("[%d] ", heap[i]);
}

void imprimeMenu() {

  int whileBreak = 0;
  int elemento;
  int heap[N];
  while (whileBreak == 0) {
    printf("\nEscolha uma das opções abaixo:\n");
    printf("1 - Inserir na heap\n");
    printf("2 - Remover da heap\n");
    printf("3 - Imprimir a heap\n");
    printf("4 - Sair\n");

    int opcaoSelecionada;
    scanf("%d", &opcaoSelecionada);

    switch (opcaoSelecionada) {
    case 1:
      printf("Digite o elemento a ser inserido: ");
      scanf("%d", &elemento);
      inserir(heap, elemento);
      break;

    case 2:
      remover(heap);
      break;

    case 3:
      imprimeHeap(heap);
      break;

    case 4: {
      whileBreak = 1;
      break;
    }
    }
  }
}

int main() {
  imprimeMenu();
  return 0;
}
