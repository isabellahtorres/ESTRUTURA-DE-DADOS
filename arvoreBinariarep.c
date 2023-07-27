#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// João Vitor Spala e Isabella Torres

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore *ler_arvore(FILE *arq) {
  char c;
  int num;

  fscanf(arq, "%c", &c);
  fscanf(arq, "%d", &num);

  if (num == -1) {
    fscanf(arq, "%c", &c);
    return NULL;
  } else {
    arvore *a = (arvore *)malloc(sizeof(arvore));
    a->info = num;
    a->esq = ler_arvore(arq);
    a->dir = ler_arvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }
}

void imprimir_pre(arvore *a) { // imprime raiz antes
  if (a != NULL) {
    printf("[%d]", a->info);
    imprimir_pre(a->esq);
    imprimir_pre(a->dir);
  }
}

void imprimir_em_ordem(arvore *a) { // imprime raiz entre
  if (a != NULL) {
    imprimir_em_ordem(a->esq);
    printf("[%d]", a->info);
    imprimir_em_ordem(a->dir);
  }
}

void imprimir_pos(arvore *a) { // imprime raiz depois
  if (a != NULL) {
    imprimir_pos(a->esq);
    imprimir_pos(a->dir);
    printf("[%d]", a->info);
  }
}

void imprimir_em_largura(arvore *a) { // imprime por nivel
  if (a == NULL) {
    return;
  }

  arvore *fila[100];
  int ini = 0;
  int fim = 0;
  fila[fim++] = a;

  while (ini < fim) {
    int cont = fim - ini;
    while (cont--) {
      arvore *atual = fila[ini++];
      printf("%d ", atual->info);

      if (atual->esq != NULL) {
        fila[fim++] = atual->esq;
      }
      if (atual->dir != NULL) {
        fila[fim++] = atual->dir;
      }
    }
    printf("\n");
  }
}

int existe(arvore *a, int x) { // verifica se um elemento x existe na arvore
  if (a == NULL)               // retorna 1 ou 0
    return 0;
  else if (a->info == x)
    return 1;
  else {
    int ret = existe(a->esq, x);
    if (ret == 1)
      return 1;
    return existe(a->dir, x);
  }
}

int contar(arvore *a) { // conta quantos elementos a arvore tem
  if (a == NULL) {
    return 0;
  } else {
    return 1 + contar(a->esq) + contar(a->dir);
  }
}

void imprimir(arvore *a) {
  puts("\nEscolha a forma de impressão: \n"
       "1 - Pre-ordem\n"
       "2 - Em ordem\n"
       "3 - Pos-ordem\n"
       "4 - Em largura\n");

  int escolha;

  scanf("%d", &escolha);
  puts("\n");

  if (escolha == 1) {
    puts("Pre-ordem: ");
    imprimir_pre(a);
    puts("\n");
  } else if (escolha == 2) {
    puts("Em ordem: ");
    imprimir_em_ordem(a);
    puts("\n");
  } else if (escolha == 3) {
    puts("Pos-ordem: ");
    imprimir_pos(a);
    puts("\n");
  } else if (escolha == 4) {
    puts("Em largura: ");
    imprimir_em_largura(a);
    puts("\n");
  } else
    puts("Opçao invalida");
}

int altura(arvore *a) {
  int he, hd;
  if (a == NULL) {
    return 0;
  } else {
    he = altura(a->esq);
    hd = altura(a->dir);
  }
  if (he > hd)
    return he + 1;

  else
    puts("\n");
  return hd + 1;
}
int conta_nos(arvore *a) {
  if (a == NULL) {
    return 0;
  }
  int e = conta_nos(a->esq);
  int d = conta_nos(a->dir);

  return e + d + 1;
}

void imprime_folha(arvore *a) {
  if (a == NULL) {
    return;
  }

  if (a->esq == NULL && a->dir == NULL) {
    printf("[%d] ", a->info);
  } else {
    imprime_folha(a->esq);
    imprime_folha(a->dir);
  }
}

void arv_cheia(arvore *a) {
  int numElem = contar(a);
  int h = altura(a);

  if (numElem == pow(2, h) - 1) {
    printf("Essa árvore está cheia.\n");
  } else {
    printf("Essa árvore não está cheia.\n");
  }
}

int arv_balanceada(arvore *a) { // verifica se a arvore esta balanceada
  if (a == NULL) {
    return 1;
  } else {
    int esq_b = arv_balanceada(a->esq);
    int dir_b = arv_balanceada(a->dir);
    int diferenca = abs(altura(a->esq) - altura(a->dir));
    return esq_b && dir_b && diferenca <= 1;
  }
}

int no_nivel(arvore *a, int x) {
  if (a != NULL) {
    if (a->info == x)
      return 0;
    else {
      int r = no_nivel(a->esq, x);
      if (r != -1)
        return r + 1;
      r = no_nivel(a->dir, x);
      if (r != -1)
        return r + 1;
    }
  }
  return -1;
}

void imprimeMenu() {
  char nomeArquivo[144];
  FILE *filePointer;
  arvore *arvorePointer = NULL;
  int count;
  int balanceada;
  int elementoNivel;
  int whileBreak = 0;
  printf("Ler uma árvore de um arquivo fornecido pelo usuário\n");
  printf("Escreva o nome do arquivo a ser lido:\n");
  scanf("%s", nomeArquivo);
  filePointer = fopen(nomeArquivo, "rt");
  arvorePointer = ler_arvore(filePointer);
  fclose(filePointer);

  while (whileBreak == 0) {
    printf("\nEscolha uma das opções abaixo: \n");
    printf("1 - Imprimir a árvore\n");
    printf("2 - Verificar se o elemento x existe na árvore\n");
    printf("3 - Contar o número de elementos da árvore\n");
    printf("4 - Imprimir os nós das folhas da árvore\n");
    printf("5 - Verificar se uma árvore está balenceada\n");
    printf("6 - Verificar se uma árvore está cheia\n");
    printf("7 - Imprimir o nível de um nó x\n");
    printf("8 - Sair\n\n");
    int opcaoSelecionada;
    scanf("%d", &opcaoSelecionada);
    switch (opcaoSelecionada) {

    case 1:
      imprimir(arvorePointer);
      break;

    case 2:
      printf("\nQual o número do elemento que você deseja verificar?\n");
      int elementoSelecionado;
      scanf("%d", &elementoSelecionado);
      int elementoExiste;
      elementoExiste = existe(arvorePointer, elementoSelecionado);
      if(elementoExiste==0){
        printf("\nA árvore não possui o elemento\n");
      }
      else{
        printf("\nA árvore possui o elemento\n");
      }
      break;

    case 3:
      count = contar(arvorePointer);
      printf("\n%d\n", count);
      break;

    case 4:
      imprime_folha(arvorePointer);
      break;

    case 5:
      balanceada = arv_balanceada(arvorePointer);
        if(balanceada==1)
          printf("não está balanceada");
      else
        printf("está balanceada");
      break;

    case 6:
      arv_cheia(arvorePointer);
      break;

    case 7:
      printf("Qual o número do nó que você deseja verificar?\n");
      int noParaVerNivel;
      scanf("%d", &noParaVerNivel);
      elementoNivel = no_nivel(arvorePointer, noParaVerNivel);
      printf("%d", elementoNivel);
      break;

    case 8:
      whileBreak = 1;
      break;
    }
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  imprimeMenu();
  return 0;
}