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

int existe(arvore *a, int x) {
  if (a == NULL || a->info == x)
    return a != NULL;
  if (a->info < x)
    return existe(a->dir, x);
  return existe(a->esq, x);
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

int no_nivel(arvore *a, int x) {
  int nivel = 0;
  if (a != NULL) {
    if (a->info == x)
      return 0;
    else {
      if (x < a->info)
        nivel = no_nivel(a->esq, x);
      else
        nivel = no_nivel(a->dir, x);
      if (nivel != -1)
        return nivel + 1;
    }
  }
  return -1;
}

void imprime_folhas_menores(arvore *a, int x) {
  if (a != NULL) {
    if (a->esq == NULL && a->dir == NULL) {
      if (a->info < x)
        printf("%d ", a->info);
    } else {
      imprime_folhas_menores(a->esq, x);
      if (a->info <
          x) { // se o nó atual for maior ou igual ao x, não precisamos olhar a
               // direita pois sabemos que serão todos maiores.
        imprime_folhas_menores(a->dir, x);
      }
    }
  }
}

arvore *inserir(arvore *a, int x) {
  if (a == NULL) {
    a = (arvore *)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
  } else if (x <= a->info)
    a->esq = inserir(a->esq, x);
  else
    a->dir = inserir(a->dir, x);
  return a;
}

arvore *remover(arvore *a, int x) {
  if (a != NULL)
    if (a->info == x)
      if (a->esq == NULL && a->dir == NULL) {
        free(a);
        return NULL;
      } else if (a->esq == NULL) {
        arvore *aux = a->dir;
        free(a);
        return aux;
      } else if (a->dir == NULL) {
        arvore *aux = a->esq;
        free(a);
        return aux;
      } else {
        arvore *aux = a->esq;
        while (aux->dir != NULL)
          aux = aux->dir;
        a->info = aux->info;
        a->esq = remover(a->esq, aux->info);
      }
    else if (x < a->info)
      a->esq = remover(a->esq, x);
    else
      a->dir = remover(a->dir, x);
  return a;
}

void imprimeMenu() {
  char nomeArquivo[144];
  FILE *filePointer;
  arvore *arvorePointer = NULL;
  int count;
  int balanceada;
  int elementoNivel;
  int whileBreak = 0;
  int elementoSelecionado;
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
    printf("3 - Imprimir o nível de um nó x\n");
    printf("4 - Imprimir as folhas que são menores que um elemento x\n");
    printf("5 - Inserir um nó x na árvore\n");
    printf("6 - Remover um nó x na árvore\n");
    printf("7 - Sair\n\n");
    int opcaoSelecionada;
    scanf("%d", &opcaoSelecionada);
    switch (opcaoSelecionada) {

    case 1: // imprimir a arvore *feito*
      imprimir(arvorePointer);
      break;

    case 2: // procurar se um elemento x existe na arvore *feito*
      printf("\nQual o número do elemento que você deseja verificar?\n");
      scanf("%d", &elementoSelecionado);
      // printf("%d\n", elementoSelecionado);
      if (existe(arvorePointer, elementoSelecionado))
        printf("\nA árvore possui o elemento\n");
      else
        printf("\nA árvore não possui o elemento\n");
      break;

    case 3: // imprimir o nível de um nó x *feito*
      printf("Qual o número do nó que você deseja verificar?\n");
      int noParaVerNivel;
      scanf("%d", &noParaVerNivel);
      elementoNivel = no_nivel(arvorePointer, noParaVerNivel);
      printf("%d", elementoNivel);
      break;

    case 4: // imprimir as folhas menores de um nó. *feito*
      printf("Escolha um elemento:\n");
      scanf("%d", &elementoSelecionado);
      imprime_folhas_menores(arvorePointer, elementoSelecionado);
      break;

    case 5: // inserir um no x na arvore
      printf("Qual elemento deseja inserir?\n");
      scanf("%d", &elementoSelecionado);
      arvorePointer = inserir(arvorePointer, elementoSelecionado);
      break;

    case 6: // remover um no x da arvore
      printf("Qual elemento deseja remover?\n");
      scanf("%d", &elementoSelecionado);
      arvorePointer = remover(arvorePointer, elementoSelecionado);
      break;

    case 7:
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
