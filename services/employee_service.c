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

void funcionario_listar(const DataStore *store)
{
    if (store->totalFuncionarios == 0)
    {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        const Funcionario *f = &store->funcionarios[i];
        printf("[%d] %s | %s | %s | %.2f\n", f->codigo, f->nome, f->telefone, f->cargo, f->salario);
    }
}

int funcionario_atualizar(DataStore *store, int codigo, const char *nome, const char *telefone, const char *cargo, float salario)
{
    Funcionario *funcionario = NULL;
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        if (store->funcionarios[i].codigo == codigo)
        {
            funcionario = &store->funcionarios[i];
            break;
        }
    }
    if (!funcionario)
    {
        return 0;
    }
    copiar_texto(funcionario->nome, nome, sizeof(funcionario->nome));
    copiar_texto(funcionario->telefone, telefone, sizeof(funcionario->telefone));
    copiar_texto(funcionario->cargo, cargo, sizeof(funcionario->cargo));
    funcionario->salario = salario;
    return 1;
}

int funcionario_remover(DataStore *store, int codigo)
{
    int indice = -1;
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        if (store->funcionarios[i].codigo == codigo)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        return 0;
    }
    for (int i = indice; i < store->totalFuncionarios - 1; i++)
    {
        store->funcionarios[i] = store->funcionarios[i + 1];
    }
    store->totalFuncionarios--;
    return 1;
}
