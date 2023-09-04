#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int info;
    struct lista *prox;
} lista;

int existe(lista *l, int x)
{
    if (l == NULL)
        return 0;
    else if (l->info == x)
        return 1;
    else
        return existe(l->prox, x);
}

lista *insereFinal(lista *l, int x)
{
    if (l == NULL)
    {
        lista *no = (lista *)malloc(sizeof(lista));
        no->info = x;
        no->prox = NULL;
        return no;
    }
    else
    {
        l->prox = insereFinal(l->prox, x);
        return l;
    }
}

// somar todos os elementos da lista
int somaLista(lista *l)
{
    if (l == NULL)
        return 0;
    else
        return l->info + somaLista(l->prox);
}

// contar o numero de ocorrencias de um elemento na lista
int contaOcorrencias(lista *l, int x)
{
    if (l == NULL)
        return 0;
    else
    {
        if (l->info == x)
        {
            return 1 + contaOcorrencias(l->prox, x);
        }
        else
        {
            return contaOcorrencias(l->prox, x);
        }
    }
}

// remover um elemento x da lista
lista *remover(lista *l, int x)
{
    if (l != NULL)
    {
        if (l->info == x)
        {
            lista *aux = l->prox;
            free(l);
            printf("elemento %d removido da lista.\n", x);
            return aux;
        }
        else
        {
            l->prox = remover(l->prox, x);
        }
    }
    return l;
}

int imprimeLista(lista *l)
{
    if (l != NULL)
    {
        printf("[%d] ", l->info);
        return imprimeLista(l->prox);
    }
    else
        return 0;
}

int main()
{
    lista *l = NULL;
    l = insereFinal(l, 2);
    l = insereFinal(l, 2);
    l = insereFinal(l, 2);
    l = insereFinal(l, 4);
    l = insereFinal(l, 6);

    printf("lista: ");
    imprimeLista(l);
    printf("\n");

    int elemento = 6;
    int ocorrencias = contaOcorrencias(l, elemento);
    printf("o elemento %d aparece %d vezes na lista.\n", elemento, ocorrencias);
    l = remover(l, elemento);
    printf("lista: ");
    imprimeLista(l);
    printf("\n");

    return 0;
}
