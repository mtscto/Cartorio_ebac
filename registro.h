#ifndef REGISTRO_H
#define REGISTRO_H

// Definições de cores ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"

// Constantes
#define TAM_CPF 15
#define TAM_NOME 100
#define TAM_CARGO 50
#define TAM_DATA 15
#define MAX_REGISTROS 100

// Estrutura de registro
typedef struct
{
    char cpf[TAM_CPF];
    char nome[TAM_NOME];
    char sobrenome[TAM_NOME];
    char cargo[TAM_CARGO];
    char dataNascimento[TAM_DATA];
} Registro;

// Protótipos
void exibirMenu();
void registrarNomes();
void consultarNomes();
void deletarNomes();
char validarContinuacao(const char *mensagem);
void limparTela();

#endif
