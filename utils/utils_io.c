#include "utils_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buffer[32];
    ler_linha(buffer, sizeof(buffer));
    return atoi(buffer);
}

float ler_float()
{
    char buffer[32];
    ler_linha(buffer, sizeof(buffer));
    return (float)atof(buffer);
}
