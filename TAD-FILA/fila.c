#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 50

struct fila {
	int *vet;
	int inicio;
	int fim;
	int tam;
};

Fila inicializar() {
	Fila f = (Fila)malloc(sizeof(struct fila));
	f->vet = (int *)malloc(N * sizeof(int)); 
	f->inicio = 0;
	f->fim = -1;
	f->tam = 0;
	return f;
}

Fila destruir(Fila f) {
	free(f->vet); 
	free(f);
	return NULL;
}

int cheia(Fila f) {
	return (f->tam == N - 1);
}

int push(Fila f, int x) {
	if (cheia(f))
		return 0;
	f->fim++;
	f->vet[f->fim] = x;
	f->tam++;
	return 1;
}

int vazia(Fila f) {
	return (f->tam == 0);
}

int pop(Fila f, int *x) {
	if (vazia(f))
		return 0;
	
	*x = f->vet[f->inicio];
	f->inicio++;
	
	if (f->inicio == N)
		f->inicio = 0;
	f->tam--;
	return 1;
}

void imprimir(Fila f) {
	printf("\nElementos: ");
	for (int i = f->inicio; i <= f->fim; i++)
		printf("%d ", f->vet[i]);
}

void imprimeMenu() {
    
    int whileBreak = 0;
    int elemento;
    Fila f = inicializar();
    while (whileBreak == 0) {
        printf("\nEscolha uma das opções abaixo:\n");
        printf("1 - Inserir na fila\n");
        printf("2 - Remover da fila\n");
        printf("3 - Imprimir a fila\n");
        printf("4 - Sair\n");

        int opcaoSelecionada;
        scanf("%d", &opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 1:
                if (cheia(f))
					printf("Fila cheia!!\n");
				else {
					printf("Digite o elemento a ser inserido: ");
					scanf("%d", &elemento);
					push(f, elemento);
				}
                break;

            case 2:{
				int x;
				if (vazia(f))
					printf("Fila vazia!!\n");
				else if (pop(f, &x))
					printf("O item removido foi: %d\n", x);
				break;
			}
            case 3:
                imprimir(f);
                break;

            case 4:{
				destruir(f);
                whileBreak = 1;
              break;
            }
        }
    }
}
