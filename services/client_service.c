#include "client_service.h"
#include <stdio.h>
#include <string.h>

static void copiar_texto(char *destino, const char *origem, int tamanho)
{
    strncpy(destino, origem, tamanho - 1);
    destino[tamanho - 1] = '\0';
}

int cliente_cadastrar(DataStore *store, const char *nome, const char *endereco, const char *telefone)
{
    if (store->totalClientes >= MAX_CLIENTES)
    {
        return -1;
    }
    Cliente cliente;
    cliente.codigo = datastore_proximo_cliente(store);
    copiar_texto(cliente.nome, nome, sizeof(cliente.nome));
    copiar_texto(cliente.endereco, endereco, sizeof(cliente.endereco));
    copiar_texto(cliente.telefone, telefone, sizeof(cliente.telefone));
    store->clientes[store->totalClientes++] = cliente;
    return cliente.codigo;
}

const Cliente *cliente_buscar_codigo(const DataStore *store, int codigo)
{
    for (int i = 0; i < store->totalClientes; i++)
    {
        if (store->clientes[i].codigo == codigo)
        {
            return &store->clientes[i];
        }
    }
    return NULL;
}

const Cliente *cliente_buscar_nome(const DataStore *store, const char *nome)
{
    for (int i = 0; i < store->totalClientes; i++)
    {
        if (strcmp(store->clientes[i].nome, nome) == 0)
        {
            return &store->clientes[i];
        }
    }
    return NULL;
}

void cliente_imprimir(const Cliente *cliente)
{
    if (!cliente)
    {
        return;
    }
    printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n", cliente->codigo, cliente->nome, cliente->endereco, cliente->telefone);
}
