#include "utils_io.h"
#include <stdio.h>
#include <string.h>

static void limpar_buffer_ate_fim_de_linha(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void ler_linha(char *destino, int tamanho)
{
    if (fgets(destino, tamanho, stdin))
    {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n')
        {
            destino[len - 1] = '\0';
        }
    }
    else
    {
        destino[0] = '\0';
    }
}

int ler_inteiro()
{
    int valor = 0;
    if (scanf("%d", &valor) != 1)
    {
        valor = 0;
    }
    limpar_buffer_ate_fim_de_linha();
    return valor;
}

float ler_float()
{
    float valor = 0.0f;
    if (scanf("%f", &valor) != 1)
    {
        valor = 0.0f;
    }
    limpar_buffer_ate_fim_de_linha();
    return valor;
}
