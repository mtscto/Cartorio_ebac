#include <stdio.h>  // Biblioteca de comunicação com o usuário
#include <stdlib.h> // Biblioteca de alocação de espaço
#include <locale.h> // Biblioteca de alocações de texto por região

int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("###  Cartorio da EBAC  ###\n\n");
    printf("Escolha a opção desejada no menu;\n\n");
    printf("\t1 - Registrar Nomes\n");
    printf("\t2 - Consultar Nomes\n");
    printf("\t3 - Deletar Nomes\n\n");
    printf("Esse Software pertence ao Matheus Tavares");
}