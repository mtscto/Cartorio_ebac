#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para limpar a tela
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para validar continuação
char validarContinuacao(const char *mensagem)
{
    char continuar;
    while (1)
    {
        printf("%s (s/n): ", mensagem);
        scanf(" %c", &continuar);

        if (continuar == 's' || continuar == 'S' || continuar == 'n' || continuar == 'N')
        {
            return continuar;
        }
        printf(RED "Opção inválida! Digite 's' para sim ou 'n' para não.\n" RESET);
    }
}

// Função para registrar nomes
void registrarNomes()
{
    char continuar = 's';
    FILE *arquivo;

    while (continuar == 's' || continuar == 'S')
    {
        limparTela();
        arquivo = fopen("registros.txt", "a");
        if (arquivo == NULL)
        {
            printf(RED "Erro ao abrir o arquivo.\n" RESET);
            return;
        }

        Registro reg;

        printf(CYAN "### Registrar Nomes ###\n" RESET);
        printf(YELLOW "Digite 'm' a qualquer momento para voltar ao menu.\n\n" RESET);

        printf("Digite o CPF: ");
        getchar();
        fgets(reg.cpf, TAM_CPF, stdin);
        if (strcmp(reg.cpf, "m\n") == 0)
        {
            fclose(arquivo);
            return;
        }
        reg.cpf[strcspn(reg.cpf, "\n")] = '\0';

        printf("Digite o Nome: ");
        fgets(reg.nome, TAM_NOME, stdin);
        if (strcmp(reg.nome, "m\n") == 0)
        {
            fclose(arquivo);
            return;
        }
        reg.nome[strcspn(reg.nome, "\n")] = '\0';

        printf("Digite o Sobrenome: ");
        fgets(reg.sobrenome, TAM_NOME, stdin);
        if (strcmp(reg.sobrenome, "m\n") == 0)
        {
            fclose(arquivo);
            return;
        }
        reg.sobrenome[strcspn(reg.sobrenome, "\n")] = '\0';

        fprintf(arquivo, "%s|%s|%s\n", reg.cpf, reg.nome, reg.sobrenome);
        fclose(arquivo);

        printf(GREEN "\nRegistro salvo com sucesso!\n" RESET);
        continuar = validarContinuacao("Deseja registrar outro nome?");
    }
}

// Função para consultar nomes
void consultarNomes()
{
    FILE *arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL)
    {
        printf(RED "Nenhum registro encontrado.\n" RESET);
        return;
    }

    limparTela();
    Registro reg;
    int contador = 0;

    printf(CYAN "### Consultar Nomes ###\n" RESET);
    printf(YELLOW "Digite 'm' a qualquer momento para voltar ao menu.\n\n" RESET);

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^\n]\n", reg.cpf, reg.nome, reg.sobrenome) != EOF)
    {
        printf("%d. CPF: %s | Nome: %s %s\n", ++contador, reg.cpf, reg.nome, reg.sobrenome);
    }

    if (contador == 0)
    {
        printf(YELLOW "Nenhum registro disponível.\n" RESET);
    }

    fclose(arquivo);
    system("pause");
}

// Função para deletar registros
void deletarNomes()
{
    char cpfExcluir[TAM_CPF];
    FILE *arquivo = fopen("registros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf(RED "Erro ao abrir os arquivos.\n" RESET);
        return;
    }

    limparTela();
    printf(CYAN "### Deletar Nomes ###\n" RESET);
    printf(YELLOW "Digite 'm' a qualquer momento para voltar ao menu.\n\n" RESET);

    printf("Digite o CPF do registro a ser deletado: ");
    scanf("%s", cpfExcluir);

    Registro reg;
    int encontrado = 0;

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^\n]\n", reg.cpf, reg.nome, reg.sobrenome) != EOF)
    {
        if (strcmp(cpfExcluir, "m") == 0)
        {
            fclose(arquivo);
            fclose(temp);
            remove("temp.txt");
            return;
        }

        if (strcmp(cpfExcluir, reg.cpf) != 0)
        {
            fprintf(temp, "%s|%s|%s\n", reg.cpf, reg.nome, reg.sobrenome);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("registros.txt");
    rename("temp.txt", "registros.txt");

    if (encontrado)
        printf(GREEN "Registro deletado com sucesso!\n" RESET);
    else
        printf(RED "Registro não encontrado.\n" RESET);

    system("pause");
}