#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// João Vitor Spala e Isabella Torres

typedef struct arvore {
  int info;
  int FB;
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
int existeABB(arvore *a, int x) {
  if (a == NULL || a->info == x)
    return a != NULL;
  if (a->info < x)
    return existeABB(a->dir, x);
  return existeABB(a->esq, x);
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

void ajustarFB(arvore *a) {
  if (a != NULL) {
    int alturaEsq = altura(a->esq);
    int alturaDir = altura(a->dir);
    a->FB = alturaDir - alturaEsq;

    ajustarFB(a->esq);
    ajustarFB(a->dir);
  }
}

arvore *ler_avl(FILE *arq) {

  arvore *a = ler_arvore(arq);
  ajustarFB(a);

  return a;
}

arvore *RotacaoEsqSimples(arvore *arvoreR) {
  arvore *a = arvoreR;
  arvore *b = a->dir;
  a->dir = b->esq;
  b->esq = a;
  if (b->FB == 1) {
    a->FB = 0;
    b->FB = 0;
  } else {
    a->FB = 1;
    b->FB = -1;
  }
  arvoreR = b;
  return arvoreR;
}

arvore *RotacaoEsqDupla(arvore *arvoreR) {
  arvore *a = arvoreR;
  arvore *c = a->dir;
  arvore *b = c->esq; // O nó b será a nova raiz
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;
  // Setando os valores dos FBs de acordo
  // com FB da nova raiz.
  switch (b->FB) {
  case -1:
    a->FB = 0;
    c->FB = 1;
    break;
  case 0:
    a->FB = 0;
    c->FB = 0;
    break;
  case +1:
    a->FB = -1;
    c->FB = 0;
    break;
  }
  b->FB = 0;
  arvoreR = b;
  return arvoreR;
}

// Rotação a esquerda geral
arvore *RotacaoEsq(arvore *arvoreR) {
  if (arvoreR->dir->FB == -1)
    arvoreR = RotacaoEsqDupla(arvoreR);
  else
    arvoreR = RotacaoEsqSimples(arvoreR);
  return arvoreR;
}

// Rotação a direita simples
arvore *RotacaoDirSimples(arvore *arvoreR) {
  // Os nós a e b serão aqueles com FB modificados.
  arvore *a = arvoreR->esq;
  arvore *b = arvoreR;
  b->esq = a->dir;
  a->dir = b;
  if (a->FB == -1) {
    a->FB = 0;
    b->FB = 0;
  } else {
    a->FB = 1;
    b->FB = -1;
  }
  arvoreR = a;
  return arvoreR;
}

arvore *RotacaoDirDupla(arvore *arvoreR) {
  // Os nós a, b, c serão aqueles com FBs modificados
  arvore *c = arvoreR;
  arvore *a = c->esq;
  arvore *b = a->dir;
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;
  // Setando os valores dos FBs de
  // acordo
  // com FB da nova raiz.
  switch (b->FB) {
  case -1:
    a->FB = 0;
    c->FB = 1;
    break;
  case 0:
    a->FB = 0;
    c->FB = 0;
    break;
  case +1:
    a->FB = -1;
    c->FB = 0;
    break;
  }
  b->FB = 0;
  arvoreR = b;
  return arvoreR;
}

// Rotação a direita geral
arvore *RotacaoDir(arvore *arvoreR) {
  if (arvoreR->esq->FB == 1)
    arvoreR = RotacaoDirDupla(arvoreR);
  else
    arvoreR = RotacaoDirSimples(arvoreR);
  return arvoreR;
}

arvore *inserirAVL(arvore *arvoreR, int x, int *hMudou) {
  if (arvoreR == NULL) {
    arvoreR = (arvore *)malloc(sizeof(arvore));
    arvoreR->info = x;
    arvoreR->esq = NULL;
    arvoreR->dir = NULL;
    arvoreR->FB = 0;
    *hMudou = 1;
  } else {
    if (x <= arvoreR->info) {
      arvoreR->esq = inserirAVL(arvoreR->esq, x, hMudou);
      if (*hMudou == 1) {
        switch (arvoreR->FB) {
        case -1:
          arvoreR = RotacaoDir(arvoreR);
          *hMudou = 0;
          break;
        case 0:
          arvoreR->FB = -1;
          *hMudou = 1;
          break;
        case +1:
          arvoreR->FB = 0;
          *hMudou = 0;
          break;
        }
      }
    } else {
      arvoreR->dir = inserirAVL(arvoreR->dir, x, hMudou);
      if (*hMudou == 1) {
        switch (arvoreR->FB) {
        case -1:
          arvoreR->FB = 0;
          *hMudou = 0;
          break;
        case 0:
          arvoreR->FB = +1;
          *hMudou = 1;
          break;
        case +1:
          arvoreR = RotacaoEsq(arvoreR);
          *hMudou = 0;
          break;
        }
      }
    }
  }
  return arvoreR;
}

arvore *removerAVL(arvore *r, int x, int *hMudou) {
  if (r != NULL) {
    if (r->info == x) {
      // Verificar se é folha
      if (r->esq == NULL && r->dir == NULL) {
        free(r);
        *hMudou = 1;
        return NULL;
      }
      // Verificar se um dos filhos é nulo
      else if (r->esq == NULL || r->dir == NULL) {
        arvore *aux;
        if (r->esq == NULL)
          aux = r->dir;
        else
          aux = r->esq;
        free(r);
        *hMudou = 1;
        return aux;
      }
      // Nenhum filho nulo
      else {
        arvore *maiorEsq = r->esq;
        while (maiorEsq->dir != NULL)
          maiorEsq = maiorEsq->dir;

        r->info = maiorEsq->info;
        r->esq = removerAVL(r->esq, r->info, hMudou);
        if (*hMudou == 1) {
          switch (r->FB) {
          case -1:
            r->FB = 0;
            *hMudou = 1;
            break;
          case 0:
            r->FB = 1;
            *hMudou = 0;
            break;
          case +1: {
            int aux = r->dir->FB;
            r = RotacaoEsq(r);
            if (aux == 0)
              *hMudou = 0;
            else
              *hMudou = 1;
            break;
          }
          }
        }
      }
    } else if (x < r->info) {
      r->esq = removerAVL(r->esq, x, hMudou);
      if (*hMudou == 1) {
        switch (r->FB) {
        case -1:
          r->FB = 0;
          *hMudou = 1;
          break;
        case 0:
          r->FB = 1;
          *hMudou = 0;
          break;
        case +1: {
          int aux = r->dir->FB;
          r = RotacaoEsq(r);
          if (aux == 0)
            *hMudou = 0;
          else
            *hMudou = 1;
          break;
        }
        }
      }
    } else {
      r->dir = removerAVL(r->dir, x, hMudou);
      if (*hMudou == 1) {
        switch (r->FB) {
        case +1:
          r->FB = 0;
          *hMudou = 1;
          break;
        case 0:
          r->FB = -1;
          *hMudou = 0;
          break;
        case -1: {
          int aux = r->esq->FB;
          r = RotacaoDir(r);
          if (aux == 0)
            *hMudou = 0;
          else
            *hMudou = 1;
          break;
        }
        }
      }
    }
  }
  return r;
}

int noNivelABB(arvore *a, int x) {
  int nivel = 0;
  if (a != NULL) {
    if (a->info == x)
      return 0;
    else {
      if (x < a->info)
        nivel = noNivelABB(a->esq, x);
      else
        nivel = noNivelABB(a->dir, x);
      if (nivel != -1)
        return nivel + 1;
    }
  }
  return -1;
}

void imprimeFolhasMenoresABB(arvore *a, int x) {
  if (a != NULL) {
    if (a->esq == NULL && a->dir == NULL) {
      if (a->info < x)
        printf("%d ", a->info);
    } else {
      imprimeFolhasMenoresABB(a->esq, x);
      if (a->info <
          x) { // se o nó atual for maior ou igual ao x, não precisamos olhar a
               // direita pois sabemos que serão todos maiores.
        imprimeFolhasMenoresABB(a->dir, x);
      }
    }
  }
}

void imprimeMenuAVL() {
  char nomeArquivo[144];
  FILE *filePointer;
  arvore *arvorePointer = NULL;
  int balanceada;
  int elementoNivel;
  int whileBreak = 0;
  int elementoSelecionado;
  int hMudou = 0;
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
    printf("7 - Sair\n");
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
      if (existeABB(arvorePointer, elementoSelecionado))
        printf("\nA árvore possui o elemento\n");
      else
        printf("\nA árvore não possui o elemento\n");
      break;

    case 3: // imprimir o nível de um nó x *feito*
      printf("Qual o número do nó que você deseja verificar?\n");
      int noParaVerNivel;
      scanf("%d", &noParaVerNivel);
      elementoNivel = noNivelABB(arvorePointer, noParaVerNivel);
      printf("%d", elementoNivel);
      break;

    case 4: // imprimir as folhas menores de um nó. *feito*
      printf("Escolha um elemento:\n");
      scanf("%d", &elementoSelecionado);
      imprimeFolhasMenoresABB(arvorePointer, elementoSelecionado);
      break;

    case 5: // inserir um no x na arvore
      printf("Qual elemento deseja inserir?\n");
      scanf("%d", &elementoSelecionado);
      arvorePointer = inserirAVL(arvorePointer, elementoSelecionado, &hMudou);
      break;

    case 6: // remover um no x da arvore
      printf("Qual elemento deseja remover?\n");
      scanf("%d", &elementoSelecionado);
      arvorePointer = removerAVL(arvorePointer, elementoSelecionado, &hMudou);
      break;
    case 7:
      whileBreak = 1;
      break;
    }
  }
}

int main() {
  imprimeMenuAVL();
  return 0;
}
