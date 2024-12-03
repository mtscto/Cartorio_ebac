#include <stdio.h>  // Biblioteca de comunicação com o usuário
#include <stdlib.h> // Biblioteca de alocação de espaço
#include <locale.h> // Biblioteca de alocações de texto por região
// corrigindo saida de caracteres
#ifdef _WIN32
#include <windows.h>
#endif

// Definições de cores ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"

// Declaração de funções
void registrarNomes();
void consultarNomes();
void deletarNomes();

int main()
{
    int opcao = 0;

    setlocale(LC_ALL, "Portuguese");

#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    while (1)
    {
// Limpa a tela no início do loop
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // Título do programa com destaque
        printf(CYAN "######################################\n");
        printf("###       Cartorio da EBAC         ###\n");
        printf("######################################\n\n" RESET);

        // Menu de opções
        printf(GREEN "Escolha a opcao desejada no menu:\n\n" RESET);
        printf(YELLOW "\t1 - Registrar Nomes\n" RESET);
        printf(YELLOW "\t2 - Consultar Nomes\n" RESET);
        printf(YELLOW "\t3 - Deletar Nomes\n" RESET);
        printf(YELLOW "\t4 - Sair\n\n" RESET);

        printf(GREEN "Digite sua opcao: " RESET);
        scanf("%d", &opcao);

        // Processa a opção selecionada
        switch (opcao)
        {
        case 1:
            registrarNomes();
            break;
        case 2:
            consultarNomes();
            break;
        case 3:
            deletarNomes();
            break;
        case 4:
            printf(RED "Saindo do programa...\n" RESET);
            exit(0);
        default:
            printf(RED "Opção inválida! Tente novamente.\n" RESET);
            system("pause"); // Pausa para o usuário ver a mensagem
        }
    }

    return 0;
}

// Implementações das funções
void registrarNomes()
{
    printf(GREEN "### Registrar Nomes ###\n" RESET);
    // Lógica para registrar nomes
    printf("Funcao de registro de nomes ainda nao implementada.\n\n");
    system("pause");
}

void consultarNomes()
{
    printf(GREEN "### Consultar Nomes ###\n" RESET);
    // Lógica para consultar nomes
    printf("Funcao de consulta de nomes ainda nao implementada.\n\n");
    system("pause");
}

void deletarNomes()
{
    printf(GREEN "### Deletar Nomes ###\n" RESET);
    // Lógica para deletar nomes
    printf("Funcao de exclusao de nomes ainda nao implementada.\n\n");
    system("pause");
}
