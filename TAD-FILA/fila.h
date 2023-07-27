#ifndef Fila_H
#define Fila_H

typedef struct fila *Fila;
int push(Fila f, int x);
int pop(Fila f, int *x);
void imprimir(Fila p);
Fila inicializar();
Fila destruir(Fila f);
#endif
