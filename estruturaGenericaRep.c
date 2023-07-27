#include <stdio.h>
#include <stdlib.h>
#define TAM 20

//Isabella Torres e João Vitor Spala

typedef struct Pessoa {
  int tipo;
  void* pessoa;
} Pessoa;

typedef struct Professor {
  char nome[20];
  int matricula;
  int salario;
} Professor;

typedef struct Aluno {
  char nome[20];
  int matricula;
  int anoDeIngresso;
  int curso;
} Aluno;

void inicializar(Pessoa *vet, int tam) {
  for (int i = 0; i < tam; i++) {
    vet[i].tipo = 0;
    vet[i].pessoa = NULL;
  }
};

Pessoa* inserePessoa(Pessoa *vet, int pos) {
  printf("Digite o tipo de pessoa que deseja inserir (1 - Professor, 2 - Aluno): ");
  int tipo;
  scanf("%d", &tipo);
  if (tipo == 1) {
    Professor *professor = (Professor*) malloc(sizeof(Professor));
    printf("Digite o nome do professor: ");
    scanf("%s", professor->nome);
    printf("Digite a matricula do professor: ");
    scanf("%d", &professor->matricula);
    printf("Digite o salario do professor: ");
    scanf("%d", &professor->salario);
    vet[pos].tipo = 1;
    vet[pos].pessoa = professor;
  } else if (tipo == 2) {
    Aluno *aluno = (Aluno*) malloc(sizeof(Aluno));
    printf("Digite o nome do aluno: ");
    scanf("%s", aluno->nome);
    printf("Digite a matricula do aluno: ");
    scanf("%d", &aluno->matricula);
    printf("Digite o ano de ingresso do aluno: ");
    scanf("%d", &aluno->anoDeIngresso);
    printf("Digite o curso do aluno: ");
    scanf("%d", &aluno->curso);
    vet[pos].tipo = 2;
    vet[pos].pessoa = aluno;
  } else {
    printf("Tipo invalido!\n");
    return NULL;
  }
};

void removerPorMatricula(Pessoa *vet, int matricula, int tam) {
  int achou = 0;
  for (int i = 0; i < tam; i++) {
    if (vet[i].tipo == 1) {
      Professor *professor = (Professor*) vet[i].pessoa;
      if (professor->matricula == matricula) {
        achou = 1;
        vet[i].tipo = 0;
        vet[i].pessoa = NULL;
        free(professor);
      }
    }
    if (vet[i].tipo == 2) {
      Aluno *aluno = (Aluno*) vet[i].pessoa;
      if (aluno->matricula == matricula) {
        achou = 1;
        vet[i].tipo = 0;
        vet[i].pessoa = NULL;
        free(aluno);
      }
    }
  }
  
  if(achou == 0) {
    printf("Matricula não encontrada!\n");
  }
}

void buscaPorMatricula(Pessoa *vet, int matricula, int tam) {
  int achou = 0;
  for (int i = 0; i < tam; i++) {
    if (vet[i].tipo == 1) {
      Professor *professor = (Professor*) vet[i].pessoa;
      if (professor->matricula == matricula) {
        achou = 1;
        printf("Nome: %s\n", professor->nome);
        printf("Matricula: %d\n", professor->matricula);
        printf("Salario: %d\n", professor->salario);
      }
    }
    if (vet[i].tipo == 2) {
      achou = 1;
      Aluno *aluno = (Aluno*) vet[i].pessoa;
      printf("Matricula: %d\n", aluno->matricula);
      if (aluno->matricula == matricula) {
        printf("Nome: %s\n", aluno->nome);
        printf("Matricula: %d\n", aluno->matricula);
        printf("Ano de ingresso: %d\n", aluno->anoDeIngresso);
        printf("Curso: %d\n", aluno->curso);
      }
    }
  }

  if(achou == 0) {
    printf("Matricula não encontrada!\n");
  }
}

void contarAlunosPorCurso(Pessoa *vet, int tam, int curso) {
  int count = 0;
  for (int i = 0; i < tam; i++) {
    if (vet[i].tipo == 2) {
      Aluno *aluno = (Aluno*) vet[i].pessoa;
      if (aluno->curso == curso) {
        count++;
      }
    }
  }
  printf("Quantidade de alunos no curso %d: %d\n", curso, count);
}

void buscarMaiorSalario(Pessoa *vet, int tam) {
  Professor vetProfessores[tam];
  int maiorSalario = 0;
  int count = 0;
  for (int i = 0; i < tam; i++) {
    if (vet[i].tipo == 1) {
      Professor *professor = (Professor*) vet[i].pessoa;
      if (professor->salario > maiorSalario) {
        maiorSalario = professor->salario;
        vetProfessores[i] = *professor;
        count++;
      }
    }
  }

  printf("Maior salário: %d\n", maiorSalario);
  for (int i = 0; i < count; i++) {
    printf("Nome: %s\n", vetProfessores[i].nome);
    printf("Matricula: %d\n", vetProfessores[i].matricula);
    printf("Salario: %d\n", vetProfessores[i].salario);
  }
}

void imprimeMenu() {
  int whileBreak = 0;
  Pessoa *vet;
  int pos = 0;
  int matricula, curso;
  inicializar(vet, TAM);
  while (whileBreak == 0) {
    printf("\nEscolha uma das opções abaixo:\n");
    printf("1 - Inserir uma pessoa na lista\n");
    printf("2 - Remover uma pessoa pela matrícula\n");
    printf("3 - Buscar uma pessoa pela matrícula\n");
    printf("4 - Contar o número de alunos de determinado curso\n");
    printf("5 - Imprimir os professores de maior salário\n");
    printf("6 - Sair\n");

    int opcaoSelecionada;
    scanf("%d", &opcaoSelecionada);

    switch (opcaoSelecionada) {
      case 1:
        if(pos >= TAM) {
          printf("Lista cheia!\n");
        } else {
          inserePessoa(vet, pos);
          pos++;
        }
        break;

      case 2:{
        printf("Digite a matrícula: ");
        scanf("%d", &matricula);
        removerPorMatricula(vet, matricula, TAM);
				break;
			}
      case 3:
        printf("Digite a matrícula: ");
        scanf("%d", &matricula);
        buscaPorMatricula(vet, matricula, TAM);
        break;

      case 4:
        printf("Digite o curso: ");
        scanf("%d", &curso);
        contarAlunosPorCurso(vet, TAM, curso);
        break;
      case 5:
        buscarMaiorSalario(vet, TAM);
        break;
      case 6:
        whileBreak = 1;
        free(vet);
        break;
    }
  }
}

int main () {
  imprimeMenu();
  return 0;
};