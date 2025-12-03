#include "datastore.h"

static int maior_codigo_cliente(const DataStore *store)
{
    int maior = 0;
    for (int i = 0; i < store->totalClientes; i++)
    {
        if (store->clientes[i].codigo > maior)
        {
            maior = store->clientes[i].codigo;
        }
    }
    return maior;
}

static int maior_codigo_funcionario(const DataStore *store)
{
    int maior = 0;
    for (int i = 0; i < store->totalFuncionarios; i++)
    {
        if (store->funcionarios[i].codigo > maior)
        {
            maior = store->funcionarios[i].codigo;
        }
    }
    return maior;
}

static int maior_codigo_estadia(const DataStore *store)
{
    int maior = 0;
    for (int i = 0; i < store->totalEstadias; i++)
    {
        if (store->estadias[i].codigo > maior)
        {
            maior = store->estadias[i].codigo;
        }
    }
    return maior;
}

void datastore_init(DataStore *store)
{
    store->totalClientes = 0;
    store->totalFuncionarios = 0;
    store->totalQuartos = 0;
    store->totalEstadias = 0;
    store->proximoCodigoCliente = 1;
    store->proximoCodigoFuncionario = 1;
    store->proximoCodigoEstadia = 1;
}

int datastore_proximo_cliente(DataStore *store)
{
    return store->proximoCodigoCliente++;
}

int datastore_proximo_funcionario(DataStore *store)
{
    return store->proximoCodigoFuncionario++;
}

int datastore_proximo_estadia(DataStore *store)
{
    return store->proximoCodigoEstadia++;
}

int datastore_atualizar_codigos(DataStore *store)
{
    store->proximoCodigoCliente = maior_codigo_cliente(store) + 1;
    store->proximoCodigoFuncionario = maior_codigo_funcionario(store) + 1;
    store->proximoCodigoEstadia = maior_codigo_estadia(store) + 1;
    return 1;
}
