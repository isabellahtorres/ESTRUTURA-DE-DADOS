#include <stdio.h>
#include "fila.h"

int main() {
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
	return 0;
}
