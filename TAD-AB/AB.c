#include "arvoreBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item
{
  int chave;
  void *obj;
} Item;

struct arvoreBinaria
{
  struct arvoreBinaria *esq;
  struct arvoreBinaria *dir;
  Item *item;
};

ArvoreBinaria Inicializar()
{
  ArvoreBinaria arvore = (ArvoreBinaria)malloc(sizeof(struct arvoreBinaria));
  arvore->esq = NULL;
  arvore->dir = NULL;
  arvore->item = (struct item *)malloc(sizeof(struct item));
  arvore->item->chave = -1;
  arvore->item->obj = NULL;
  return arvore;
};

ArvoreBinaria Destruir(ArvoreBinaria arvore)
{
  if (arvore == NULL)
  {
    return NULL;
  }
  Destruir(arvore->esq);
  Destruir(arvore->dir);
  free(arvore->item);
  free(arvore);
  return NULL;
};

void *Buscar(ArvoreBinaria arvore, int chaveElemento)
{
  if (arvore == NULL)
    return NULL;
  if (arvore->item->chave == chaveElemento)
    return arvore->item->obj;
  else
  {
    ArvoreBinaria esq = Buscar(arvore->esq, chaveElemento);
    if (esq != NULL)
      return esq;
    else
      return Buscar(arvore->dir, chaveElemento);
  }
}

ArvoreBinaria BuscarNo(ArvoreBinaria arvore, int chaveElemento)
{
  if (arvore == NULL)
    return NULL;
  if (arvore->item->chave == chaveElemento)
    return arvore;
  else
  {
    ArvoreBinaria esq = BuscarNo(arvore->esq, chaveElemento);
    if (esq != NULL)
      return esq;
    else
      return BuscarNo(arvore->dir, chaveElemento);
  }
}

int Inserir(ArvoreBinaria arvore, int chaveElemento, void *objeto, int chavePai, char posicao, int sizeObj)
{
  if (chavePai == -1)
  {
    if (arvore->item->chave == -1 && arvore->item->obj == NULL)
    {
      arvore->item->chave = chaveElemento;
      arvore->item->obj = malloc(sizeObj);
      memcpy(arvore->item->obj, objeto, sizeObj);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  ArvoreBinaria pai = BuscarNo(arvore, chavePai);
  if (pai == NULL)
    return 0;
  ArvoreBinaria filho = Inicializar();
  filho->item->chave = chaveElemento;
  filho->item->obj = malloc(sizeObj);
  memcpy(filho->item->obj, objeto, sizeObj);
  switch (posicao)
  {
  case 'e':
    if (pai->esq == NULL)
    {
      pai->esq = filho;
      return 1;
    }
    else
    {
      free(filho);
      return 0;
    }
    break;
  case 'd':
    if (pai->dir == NULL)
    {
      pai->dir = filho;
      return 1;
    }
    else
    {
      free(filho);
      return 0;
    }
    break;
  default:
    free(filho);
    return 0;
    break;
  }
}

int Existe(ArvoreBinaria arvore, int chaveElemento)
{
  if (arvore == NULL)
  {
    return 0;
  }
  if (arvore->item->chave == chaveElemento)
  {
    return 1;
  }
  if (Existe(arvore->esq, chaveElemento))
  {
    return 1;
  }
  if (Existe(arvore->dir, chaveElemento))
  {
    return 1;
  }
  return 0;
}

int Balanceada(ArvoreBinaria arvore)
{
  if (arvore == NULL)
  {
    return 1;
  }
  if (Balanceada(arvore->esq) && Balanceada(arvore->dir) && (Altura(arvore->esq) - Altura(arvore->dir) <= 1))
  {
    return 1;
  }
  return 0;
}

int Altura(ArvoreBinaria arvore)
{
  if (arvore == NULL)
  {
    return 0;
  }
  int alturaEsq = Altura(arvore->esq);
  int alturaDir = Altura(arvore->dir);
  if (alturaEsq > alturaDir)
  {
    return alturaEsq + 1;
  }
  else
  {
    return alturaDir + 1;
  }
}

void Imprime_nivel(ArvoreBinaria arvore, int nivel, int nivelAtual)
{
  if (arvore != NULL)
  {
    if (nivel == nivelAtual)
      printf("%d ", arvore->item->chave);
    else
    {
      Imprime_nivel(arvore->esq, nivel, nivelAtual + 1);
      Imprime_nivel(arvore->dir, nivel, nivelAtual + 1);
    }
  }
}

void ImprimirEmLargura(ArvoreBinaria arvore)
{
  for (int i = 0; i < Altura(arvore); i++)
  {
    printf("\n");
    Imprime_nivel(arvore, i, 0);
  }
  printf("\n");
}
