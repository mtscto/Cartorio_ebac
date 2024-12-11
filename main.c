#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

// Prototipos de funções
void exibirMenu();
void registrarNomes();
void consultarNomes();
void consultarDetalhes(Registro registros[], int totalRegistros);
void deletarNomes();
char validarContinuacao(const char *mensagem);
void limparTela();

// Função principal
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while (1)
    {
        limparTela();
        exibirMenu();
        printf("Digite sua opção: ");
        scanf("%d", &opcao);

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
            printf(CYAN "Saindo do programa...\n" RESET);
            exit(0);
        default:
            printf(RED "Opção inválida! Tente novamente.\n" RESET);
            system("pause");
        }
    }

    return 0;
}

// Função para exibir o menu principal
void exibirMenu()
{
    printf(CYAN "######################################\n");
    printf("###       Cartório da EBAC        ###\n");
    printf("######################################\n\n" RESET);
    printf(GREEN "Escolha a opção desejada no menu:\n\n" RESET);
    printf(YELLOW "\t1 - Registrar Nomes\n" RESET);
    printf(YELLOW "\t2 - Consultar Nomes\n" RESET);
    printf(YELLOW "\t3 - Deletar Nomes\n" RESET);
    printf(YELLOW "\t4 - Sair\n\n" RESET);
}

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

// Função para registrar Nomes
void registrarNomes()
{
    char continuar = 's';
    FILE *arquivo;
    Registro reg;

    while (continuar == 's' || continuar == 'S')
    {
        limparTela();
        arquivo = fopen("registros.txt", "a");
        if (arquivo == NULL)
        {
            printf(RED "Erro ao abrir o arquivo para escrita.\n" RESET);
            return;
        }

        printf(CYAN "######################################\n");
        printf("###         Registrar Nomes        ###\n");
        printf("######################################\n\n" RESET);

        printf("Digite o CPF: ");
        getchar(); // Limpa o buffer
        fgets(reg.cpf, TAM_CPF, stdin);
        reg.cpf[strcspn(reg.cpf, "\n")] = '\0';

        if (strlen(reg.cpf) == 0 || strcmp(reg.cpf, "0") == 0)
        {
            printf(RED "Campo CPF é obrigatório!\n" RESET);
            system("pause");
            continue;
        }

        printf("Digite o Nome: ");
        fgets(reg.nome, TAM_NOME, stdin);
        reg.nome[strcspn(reg.nome, "\n")] = '\0';
        if (strlen(reg.nome) == 0)
        {
            printf(RED "Campo Nome é obrigatório!\n" RESET);
            system("pause");
            continue;
        }

        printf("Digite o Sobrenome: ");
        fgets(reg.sobrenome, TAM_NOME, stdin);
        reg.sobrenome[strcspn(reg.sobrenome, "\n")] = '\0';
        if (strlen(reg.sobrenome) == 0)
        {
            printf(RED "Campo Sobrenome é obrigatório!\n" RESET);
            system("pause");
            continue;
        }

        printf("Digite o Cargo: ");
        fgets(reg.cargo, TAM_CARGO, stdin);
        reg.cargo[strcspn(reg.cargo, "\n")] = '\0';
        if (strlen(reg.cargo) == 0)
        {
            printf(RED "Campo Cargo é obrigatório!\n" RESET);
            system("pause");
            continue;
        }

        printf("Digite a Data de Nascimento (dd/mm/aaaa): ");
        fgets(reg.dataNascimento, TAM_DATA, stdin);
        reg.dataNascimento[strcspn(reg.dataNascimento, "\n")] = '\0';
        if (strlen(reg.dataNascimento) == 0)
        {
            printf(RED "Campo Data de Nascimento é obrigatório!\n" RESET);
            system("pause");
            continue;
        }

        fprintf(arquivo, "%s|%s|%s|%s|%s\n", reg.cpf, reg.nome, reg.sobrenome, reg.cargo, reg.dataNascimento);
        fclose(arquivo);

        printf(GREEN "\nRegistro salvo com sucesso!\n\n" RESET);
        continuar = validarContinuacao(YELLOW "Deseja registrar outro nome?" RESET);
    }

    printf(CYAN "Saindo do registro de nomes...\n" RESET);
    system("pause");
}

// Função para consultar Nomes
void consultarNomes()
{
    FILE *arquivo;
    Registro registros[MAX_REGISTROS];
    int totalRegistros = 0;

    limparTela();
    arquivo = fopen("registros.txt", "r");
    if (arquivo == NULL)
    {
        printf(RED "Nenhum registro encontrado.\n" RESET);
        system("pause");
        return;
    }

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  registros[totalRegistros].cpf,
                  registros[totalRegistros].nome,
                  registros[totalRegistros].sobrenome,
                  registros[totalRegistros].cargo,
                  registros[totalRegistros].dataNascimento) != EOF)
    {
        totalRegistros++;
    }
    fclose(arquivo);

    if (totalRegistros == 0)
    {
        printf(RED "Nenhum registro encontrado.\n" RESET);
        system("pause");
        return;
    }

    printf(CYAN "######################################\n");
    printf("###         Consultar Registros     ###\n");
    printf("######################################\n\n" RESET);

    printf("Nomes e CPFs:\n");
    for (int i = 0; i < totalRegistros; i++)
    {
        printf("CPF: %s\n", registros[i].cpf);
        printf("Nome: %s\n", registros[i].nome);
        printf("--------------------\n");
    }

    int escolha;
    printf("\nDeseja consultar informações detalhadas de algum registro? (1 - Sim, 0 - Não): ");
    scanf("%d", &escolha);

    if (escolha == 1)
    {
        consultarDetalhes(registros, totalRegistros);
    }

    system("pause");
}

// Função para consultar detalhes de um registro específico
void consultarDetalhes(Registro registros[], int totalRegistros)
{
    char cpfBusca[TAM_CPF];
    int indexEncontrado = -1;

    printf("\nDigite o CPF do registro detalhado que deseja consultar: ");
    getchar(); // Limpa o buffer
    fgets(cpfBusca, TAM_CPF, stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

    for (int i = 0; i < totalRegistros; i++)
    {
        if (strcmp(registros[i].cpf, cpfBusca) == 0)
        {
            indexEncontrado = i;
            break;
        }
    }

    if (indexEncontrado != -1)
    {
        printf(CYAN "Detalhes do Registro:\n" RESET);
        printf("CPF: %s\n", registros[indexEncontrado].cpf);
        printf("Nome: %s\n", registros[indexEncontrado].nome);
        printf("Sobrenome: %s\n", registros[indexEncontrado].sobrenome);
        printf("Cargo: %s\n", registros[indexEncontrado].cargo);
        printf("Data de Nascimento: %s\n", registros[indexEncontrado].dataNascimento);
    }
    else
    {
        printf(RED "Registro não encontrado.\n" RESET);
    }

    system("pause");
}

// Função para deletar Nomes
void deletarNomes()
{
    char continuar = 's';

    while (continuar == 's' || continuar == 'S')
    {
        FILE *arquivo = fopen("registros.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (arquivo == NULL || temp == NULL)
        {
            printf(RED "Erro ao abrir os arquivos.\n" RESET);
            return;
        }

        Registro registros[MAX_REGISTROS];
        int totalRegistros = 0;

        while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                      registros[totalRegistros].cpf,
                      registros[totalRegistros].nome,
                      registros[totalRegistros].sobrenome,
                      registros[totalRegistros].cargo,
                      registros[totalRegistros].dataNascimento) != EOF)
        {
            totalRegistros++;
        }
        fclose(arquivo);

        printf(CYAN "######################################\n");
        printf("###         Deletar Registros       ###\n");
        printf("######################################\n\n" RESET);

        char cpfBusca[TAM_CPF];
        int indexEncontrado = -1;

        printf("Digite o CPF que deseja excluir: ");
        getchar(); // Limpa o buffer
        fgets(cpfBusca, TAM_CPF, stdin);
        cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

        for (int i = 0; i < totalRegistros; i++)
        {
            if (strcmp(registros[i].cpf, cpfBusca) == 0)
            {
                indexEncontrado = i;
                break;
            }
        }

        if (indexEncontrado != -1)
        {
            for (int i = 0; i < totalRegistros; i++)
            {
                if (i != indexEncontrado)
                {
                    fprintf(temp, "%s|%s|%s|%s|%s\n",
                            registros[i].cpf, registros[i].nome, registros[i].sobrenome, registros[i].cargo, registros[i].dataNascimento);
                }
            }
            printf(GREEN "Registro excluído com sucesso!\n" RESET);
        }
        else
        {
            printf(RED "Registro não encontrado.\n" RESET);
        }

        fclose(temp);
        remove("registros.txt");
        rename("temp.txt", "registros.txt");

        continuar = validarContinuacao(YELLOW "Deseja excluir outro registro?" RESET);
    }

    printf(CYAN "Saindo da exclusão de registros...\n" RESET);
    system("pause");
}
