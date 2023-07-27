//Isabella Torres e João Vitor Spala
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista* prox;
} lista;

void inicializar(lista** g, int n) {
    int i;
    for (i = 1; i <= n; i++)
        g[i] = NULL;
}

lista* inserirLista(lista* l, int d, int c) {
    lista* no = (lista*)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;
    return no;
}

void inserirAresta(lista** g, int origem, int destino, int custo) {
    g[origem] = inserirLista(g[origem], destino, custo);
}

void imprimirLista(lista* l) {
    if (l != NULL) {
        printf("-(%d, %d)", l->destino, l->custo);
        imprimirLista(l->prox);
    }
}

void imprimirGrafo(lista** g, int n) {
    int i;
    printf("Grafo:\n");
    for (i = 1; i <= n; i++) {
        printf("%d", i);
        imprimirLista(g[i]);
        printf("\n");
    }
}

lista* removerLista(lista* l, int destino) {
    if (l == NULL) {
        return NULL;
    }

    if (l->destino == destino) {
        lista* temp = l->prox;
        free(l);
        return temp;
    }

    l->prox = removerLista(l->prox, destino);
    return l;
}

void removerAresta(lista** g, int origem, int destino) {
    if (g[origem] == NULL) {
        return;
    }

    g[origem] = removerLista(g[origem], destino);
}

int existe(int *vet, int valor,int n){
    int i;
    for(i=0;i<n;i++){
        if(vet[i]==valor){
        return 1;
        }
    }
    return 0;
}

void caminhos(lista** g, int verticeDestino, int* vet, int pos) {
    if (vet[pos - 1] == verticeDestino) {
        for (int i = 0; i < pos; i++)
            printf("%d ", vet[i]);
        printf("\n");
        return;
    }
  
  lista* p = g[vet[pos - 1]];
  while (p!= NULL) {
    if (!existe(vet, p->destino, pos)) {
      vet[pos] = p->destino;
      caminhos(g, verticeDestino, vet, pos + 1);
    }
    p = p->prox;
  }
}

int* menorCaminho(lista **g, int verticeDestino, int n, int *vet, int pos, int contArestas, int *menorC, int *vetaux) {
    if (vet[pos - 1] == verticeDestino) {
        if (contArestas < *menorC) {
            *menorC = contArestas;
            for (int i = 0; i < pos; i++) {
                vetaux[i] = vet[i];
            }
        }
    } else {
        lista *p = g[vet[pos - 1]];
        while (p != NULL) {
            if (!existe(vet, p->destino, pos)) {
                vet[pos] = p->destino;
                menorCaminho(g, verticeDestino, n, vet, pos + 1, contArestas + 1, menorC, vetaux);
            }
            p = p->prox;
        }
    }
    return vetaux;
}

int procuraDestino(lista *g, int d){
  if(g==NULL){
    return 0;
  }
  else if(g->destino==d){
    return 1;
  }
  return procuraDestino(g->prox,d);
}

int grauEntrada(lista **g, int d, int n) {
  int grau = 0;
  for(int i = 0; i < n; i++) {
    grau = grau + procuraDestino(g[i], d);
  }
  return grau;
}

int grauSaida(lista *g){
  if(g==NULL){
    return 0;
  }
  return 1 + grauSaida(g->prox);
}

int ehCompleto(lista **g, int n) {
  int soma = 0;
  for (int i = 1; i <= n; i++) {
    soma = soma + grauSaida(g[i]);
  }
  if (soma == n * (n - 1)) {
    return 1;
  }
  return 0;
}

int* MenorCusto(lista **g, int b,int n, int *vet, int pos, int c1, int *c2, int *vetaux){
  if (vet[pos-1]==b) {
    int i;
    if(c1<*c2){
      *c2 = c1;
      for(i=0;i<pos;i++){
        vetaux[i] = vet[i];
      }
    }
  } else {
    lista *p = g[vet[pos-1]];
    while (p!=NULL) {
      if (!existe(vet, p->destino, pos)) {
        vet[pos] = p->destino;
        c1 = c1 + p->custo;
        MenorCusto(g, b, n, vet, pos+1, c1, c2, vetaux);
        c1 =0;
      }
      p = p->prox;
    }
  }
  return vetaux;
}


void imprimeMenuAVL() {
    
    int whileBreak = 0;
    int origem, destino, custo, n, custo_total=0, x;
    int *vet;
    printf("Digite o número total de vértices do grafo: ");
    scanf("%d", &n);

    lista** g = (lista**)malloc((n + 1) * sizeof(lista*));
    inicializar(g, n);

    vet = (int *)malloc(n*sizeof(int));

    while (whileBreak == 0) {
        printf("\nEscolha uma das opções abaixo:\n");
        printf("1 - Inserir uma aresta no grafo\n");
        printf("2 - Remover uma aresta no grafo\n");
        printf("3 - Imprimir o grafo\n");
        printf("4 - Imprimir graus de entrada e saída de um vertice de um grafo\n");
        printf("5 - Verificar se um grafo é completo\n");
        printf("6 - Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7 - Imprimir o menor caminho\n");
        printf("8 - Imprimir o caminho com menos custo\n");
        printf("9 - sair\n\n");

        int opcaoSelecionada;
        scanf("%d", &opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 1:
                printf("Digite a origem, destino e custo da aresta: ");
                scanf("%d %d %d", &origem, &destino, &custo);
                inserirAresta(g, origem, destino, custo);
                break;

            case 2:
                printf("Digite a origem e destino da aresta a ser removida: ");
                scanf("%d %d", &origem, &destino);
                removerAresta(g, origem, destino);
                break;

            case 3:
                imprimirGrafo(g, n);
                break;

            case 4:{
              int b;
              printf("Digite o vértice: ");
              scanf("%d", &b);
              printf("Grau de saida: %d\n", grauSaida(g[b]));
              printf("Grau de entrada: %d", grauEntrada(g,b,n));
              printf("\n");
              break;
            }


            case 5:{
              int x;
              x = ehCompleto(g, n);
              if(x==1)
                printf("Grafo é completo\n");
              else
                printf("Grafo não é completo\n");
              break;
            }
            
            case 6:{
              int elementoF, origem;
              printf("Digite a origem: ");
              scanf("%d", &origem);
              vet[0] = origem;
              printf("Digite o elemento final: ");
              scanf("%d", &elementoF);
              printf("\n");
              caminhos(g, elementoF, vet, 1);
              break;
            }

            case 7:{
              int elementoF, contArestas=0, menorC=n, *vetaux, origem;
              vetaux = (int*)malloc(n*sizeof(int));
              printf("Digite a origem: ");
              scanf("%d", &origem);
              vet[0] = origem;
              for(int i=0;i<n;i++){
              vetaux[i] = origem;
              }
              printf("Digite o elemento final: ");
              scanf("%d", &elementoF);
              printf("\n");
              vetaux = menorCaminho(g, elementoF, n, vet, 1, contArestas,&menorC, vetaux);
              for(int i = 0; i<=menorC;i++)
                printf("%d ", vetaux[i]);
              printf("\n");
              break;
            }
            
            case 8:{
              int b, c1=0,c2 = custo_total, *vetaux,i;
              vetaux = (int*)malloc(n*sizeof(int));
              printf("Digite a origem: ");
              scanf("%d", &x);
              vet[0] = x;
              for(i=0;i<n;i++){
                vetaux[i] = x;
              }
              printf("Digite o elemento final: ");
              scanf("%d", &b);
              printf("\n");
              vetaux = MenorCusto(g, b, n, vet, 1, c1 ,&c2, vetaux);
              for(i = 0; i<n;i++){
                printf("%d ", vetaux[i]);
                if(vetaux[i]==3){
                  break;
                }
              }
              printf("\n");
              break;}
                    
            
            case 9:
                whileBreak = 1;
                break;

            default:
                printf("Opção inválida. Digite novamente.\n");
                break;
            }
        }
    for (int i = 1; i <= n; i++) {
        lista* atual = g[i];
        while (atual != NULL) {
            lista* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(g);
}

int main() {
    imprimeMenuAVL();
    return 0;
}
