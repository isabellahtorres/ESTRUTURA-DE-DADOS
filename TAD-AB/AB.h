#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct arvoreBinaria *ArvoreBinaria;
ArvoreBinaria Inicializar(void);
ArvoreBinaria Destruir(ArvoreBinaria arvore);
int Inserir(ArvoreBinaria arvore, int chaveElemento, void *obj, int chavePai, char posicao, int sizeObj);
int Existe(ArvoreBinaria arvore, int chaveElemento);
void *Buscar(ArvoreBinaria arvore, int chaveElemento);
int Balanceada(ArvoreBinaria arvore);
int Altura(ArvoreBinaria arvore);
void ImprimirEmLargura(ArvoreBinaria arvore);

#endif