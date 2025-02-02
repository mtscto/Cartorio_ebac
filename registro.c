#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SENHA_ADMIN "admin"

// Função para limpar a tela
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função de login com senha
void exibirTelaLogin()
{
    char senha[20];
    int tentativas = 3;

    while (tentativas > 0)
    {
        limparTela();
        printf(CYAN "######################################\n");
        printf("###       Cartório da EBAC        ###\n");
        printf("######################################\n\n" RESET);

        printf(YELLOW "Digite a senha de administrador: " RESET);
        scanf("%s", senha);

        if (strcmp(senha, SENHA_ADMIN) == 0)
        {
            printf(GREEN "Acesso concedido!\n" RESET);
            return;
        }
        else
        {
            tentativas--;
            if (tentativas > 0)
            {
                printf(RED "Senha incorreta, restam %d tentativa(s).\n" RESET, tentativas);
                printf(YELLOW "Pressione qualquer tecla para continuar...\n" RESET);
                getchar();
                getchar();
            }
            else
            {
                printf(RED "Senha incorreta, sistema bloqueado.\n" RESET);
                exit(1);
            }
        }
    }
}

// Funções de Validação
int validarCPF(const char *cpf)
{
    if (strlen(cpf) != 11)
        return 0;
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
            return 0;
    }
    return 1;
}

int validarTexto(const char *texto)
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (!isalpha(texto[i]) && texto[i] != ' ')
            return 0;
    }
    return 1;
}

int validarData(const char *data)
{
    if (strlen(data) != 8)
        return 0;
    for (int i = 0; i < 8; i++)
    {
        if (!isdigit(data[i]))
            return 0;
    }
    return 1;
}

void formatarData(char *data)
{
    char formatada[11];
    snprintf(formatada, sizeof(formatada), "%c%c/%c%c/%c%c%c%c",
             data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
    strcpy(data, formatada);
}

// Função para registrar usuários
void registrarUsuarios()
{
    char continuar = 's';
    FILE *arquivo;

    while (continuar == 's' || continuar == 'S')
    {
        limparTela();
        printf(CYAN "######################################\n");
        printf("###    Registrar Novo Usuário      ###\n");
        printf("######################################\n\n" RESET);

        arquivo = fopen("registros.txt", "a");
        if (arquivo == NULL)
        {
            printf(RED "Erro ao abrir o arquivo.\n" RESET);
            return;
        }

        Usuario usuario;

        do
        {
            printf(YELLOW "Digite o CPF \n(apenas numeros, 11 digitos): " RESET);
            scanf("%s", usuario.cpf);
        } while (!validarCPF(usuario.cpf));

        do
        {
            printf(YELLOW "Digite o Nome \n(apenas letras): " RESET);
            scanf(" %[^\n]s", usuario.nome);
        } while (!validarTexto(usuario.nome));

        do
        {
            printf(YELLOW "Digite o Sobrenome \n(apenas letras): " RESET);
            scanf(" %[^\n]s", usuario.sobrenome);
        } while (!validarTexto(usuario.sobrenome));

        do
        {
            printf(YELLOW "Digite o Cargo \n(apenas letras): " RESET);
            scanf(" %[^\n]s", usuario.cargo);
        } while (!validarTexto(usuario.cargo));

        do
        {
            printf(YELLOW "Digite a Data de Nascimento (DDMMAAAA)\n(apenas numeros, 11 digitos): " RESET);
            scanf("%s", usuario.dataNascimento);
        } while (!validarData(usuario.dataNascimento));

        formatarData(usuario.dataNascimento);

        fprintf(arquivo, "%s|%s|%s|%s|%s\n", usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo, usuario.dataNascimento);
        fclose(arquivo);

        printf(GREEN "\nUsuário registrado com sucesso!\n" RESET);
        printf(YELLOW "Deseja registrar outro usuário? (s/n): " RESET);
        scanf(" %c", &continuar);
    }
}

// Função para consultar usuários
void consultarUsuarios()
{
    FILE *arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL)
    {
        printf(RED "Nenhum registro encontrado.\n" RESET);
        return;
    }

    limparTela();
    Usuario usuario;
    int contador = 0;

    printf(CYAN "### Consultar Usuários ###\n\n" RESET);

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo, usuario.dataNascimento) != EOF)
    {
        printf("%d. CPF: %s | Nome: %s %s | Cargo: %s | Nascimento: %s\n",
               ++contador, usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo, usuario.dataNascimento);
    }

    if (contador == 0)
    {
        printf(YELLOW "Nenhum registro disponível.\n" RESET);
    }

    fclose(arquivo);
    printf(YELLOW "\nPressione qualquer tecla para continuar...\n" RESET);
    getchar();
    getchar();
}

// Função para deletar usuários
void deletarUsuarios()
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
    printf(CYAN "### Deletar Usuário ###\n\n" RESET);
    printf(YELLOW "Digite o CPF do usuário a ser deletado: " RESET);
    scanf("%s", cpfExcluir);

    Usuario usuario;
    int encontrado = 0;

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo, usuario.dataNascimento) != EOF)
    {
        if (strcmp(cpfExcluir, usuario.cpf) != 0)
        {
            fprintf(temp, "%s|%s|%s|%s|%s\n",
                    usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo, usuario.dataNascimento);
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
        printf(GREEN "Usuário deletado com sucesso!\n" RESET);
    else
        printf(RED "Usuário não encontrado.\n" RESET);

    printf(YELLOW "\nPressione qualquer tecla para continuar...\n" RESET);
    getchar();
    getchar();
}
