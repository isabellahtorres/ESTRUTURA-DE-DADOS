//Isabella Torres e João Vitor Spala
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct registro {
  int matricula;
  char *nome;
  char *curso;
  int disponibilidade;
} registro;

int hash(int key) {
  return key % N;
}

void inicializar(char *nomeArquivo) {
  FILE *arq = fopen(nomeArquivo, "wb");
  registro a;
  int i;
  a.disponibilidade = 1;
  for (i = 0; i < N; i++) {
    fwrite(&a, sizeof(registro), 1, arq);
  }
  fclose(arq);
}

int acharPosicao(char *nomeArquivo, int mat) {
  int pos = hash(mat);
  registro a;
  FILE *arq = fopen(nomeArquivo, "rb");
  fseek(arq, pos * sizeof(registro), SEEK_SET);
  fread(&a, sizeof(registro), 1, arq);
  while (a.disponibilidade == 0) {
    pos = (pos + 1) % N;
    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
  }
  fclose(arq);
  return pos;
}

void inserir(char *nomeArquivo, int matricula, char nome[200], char curso[50]) {
  int pos = acharPosicao(nomeArquivo, matricula);
  FILE *arq = fopen(nomeArquivo, "r+b");
  registro a;
  a.matricula = matricula;
  a.nome = malloc(strlen(nome) + 1);
  strcpy(a.nome, nome);
  a.curso = malloc(strlen(curso) + 1);
  strcpy(a.curso, curso);
  a.disponibilidade = 0;
  fseek(arq, pos * sizeof(registro), SEEK_SET);
  fwrite(&a, sizeof(registro), 1, arq);
  fclose(arq);
}

int buscar(char *nomeArquivo, int mat) {
  int pos = hash(mat);
  registro a;
  FILE *arq = fopen(nomeArquivo, "rb");
  fseek(arq, pos * sizeof(registro), SEEK_SET);
  fread(&a, sizeof(registro), 1, arq);
  while (a.matricula != mat && a.disponibilidade != 1) {
    pos = (pos + 1) % N;
    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
  }
  fclose(arq);
  return pos;
}

void imprimirInfo(char *nomeArquivo, int mat) {
  int pos = buscar(nomeArquivo, mat);
  FILE *arq = fopen(nomeArquivo, "rb");
  registro a;
  fseek(arq, pos * sizeof(registro), SEEK_SET);
  fread(&a, sizeof(registro), 1, arq);
  printf("\nAluno: %s\n", a.nome);
  printf("Matrícula: %d\n", a.matricula);
  printf("Curso: %s\n\n", a.curso);
  fclose(arq);
}

void imprimirTabela(char *nomeArquivo) {
  FILE *arq = fopen(nomeArquivo, "rb");
  registro a;

  printf("%-8s %-15s %-20s %-20s\n", "Posição", "Matrícula", "Nome", "Curso");
  for (int pos = 0; pos < N; pos++) {
    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);

    if (a.disponibilidade == 0) {
      printf("%-8d %-15d %-20s %-20s\n", pos, a.matricula, a.nome, a.curso);
    } else {
      printf("%-8d %-15s %-20s %-20s\n", pos, "--", "--", "--");
    }
  }

  fclose(arq);
}


void imprimeMenu() {
  int whileBreak = 0;
  char nomeArquivo[50] = "teste.bin";
  inicializar(nomeArquivo);
  while (whileBreak == 0) {
    printf("\nEscolha uma das opções abaixo:\n");
    printf("1 - Inserir um novo aluno\n");
    printf("2 - Imprimir informações de um aluno\n");
    printf("3 - Imprimir a tabela de dispersão\n");
    printf("4 - Sair\n");

    int opcaoSelecionada;
    scanf("%d", &opcaoSelecionada);

    switch (opcaoSelecionada) {
      case 1: {
        int matricula;
        char nome[200], curso[50];
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]", nome);
        printf("Digite o curso do aluno: ");
        scanf(" %[^\n]", curso);
        printf("Digite a matrícula do aluno: ");
        scanf("%d", &matricula);
        inserir(nomeArquivo, matricula, nome, curso);
        break;
      }
      case 2: {
        int matricula;
        printf("Digite a matrícula do aluno: ");
        scanf("%d", &matricula);
        imprimirInfo(nomeArquivo, matricula);
        break;
      }
      case 3:
        imprimirTabela(nomeArquivo);
        break;

      case 4:
        whileBreak = 1;
        break;
    }
  }
}

int main() {
  imprimeMenu();
  return 0;
}

