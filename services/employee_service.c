#include "employee_service.h"
#include <stdio.h>
#include <string.h>

static void copiar_texto(char *destino, const char *origem, int tamanho)
{
    strncpy(destino, origem, tamanho - 1);
    destino[tamanho - 1] = '\0';
}

int funcionario_cadastrar(DataStore *store, const char *nome, const char *telefone, const char *cargo, float salario)
{
    if (store->totalFuncionarios >= MAX_FUNCIONARIOS)
    {
        return -1;
    }
    Funcionario funcionario;
    funcionario.codigo = datastore_proximo_funcionario(store);
    copiar_texto(funcionario.nome, nome, sizeof(funcionario.nome));
    copiar_texto(funcionario.telefone, telefone, sizeof(funcionario.telefone));
    copiar_texto(funcionario.cargo, cargo, sizeof(funcionario.cargo));
    funcionario.salario = salario;
    store->funcionarios[store->totalFuncionarios++] = funcionario;
    return funcionario.codigo;
}

const Funcionario *funcionario_buscar_codigo(const DataStore *store, int codigo)
{
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        if (store->funcionarios[i].codigo == codigo)
        {
            return &store->funcionarios[i];
        }
    }
    return NULL;
}

const Funcionario *funcionario_buscar_nome(const DataStore *store, const char *nome)
{
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        if (strcmp(store->funcionarios[i].nome, nome) == 0)
        {
            return &store->funcionarios[i];
        }
    }
    return NULL;
}

void funcionario_imprimir(const Funcionario *funcionario)
{
    if (!funcionario)
    {
        return;
    }
    printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n", funcionario->codigo, funcionario->nome, funcionario->telefone, funcionario->cargo, funcionario->salario);
}
