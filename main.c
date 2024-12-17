#include "registro.c"
#include <stdio.h>
#include <locale.h>

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
            return 0;
        default:
            printf(RED "Opção inválida! Tente novamente.\n" RESET);
            system("pause");
        }
    }

    return 0;
}

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
