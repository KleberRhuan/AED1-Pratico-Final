#include "room_service.h"
#include <stddef.h>
#include <stdio.h>

static int quarto_tem_estadia_ativa(const DataStore *store, int numeroQuarto)
{
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        if (e->numeroQuarto == numeroQuarto && e->ativa)
        {
            return 1;
        }
    }
    return 0;
}

int quarto_cadastrar(DataStore *store, int numero, int capacidade, float valorDiaria)
{
    if (store->totalQuartos >= MAX_QUARTOS)
    {
        return 0;
    }
    for (int i = 0; i < store->totalQuartos; i++)
    {
        if (store->quartos[i].numero == numero)
        {
            return 0;
        }
    }
    Quarto quarto;
    quarto.numero = numero;
    quarto.capacidade = capacidade;
    quarto.valorDiaria = valorDiaria;
    quarto.status = STATUS_DESOCUPADO;
    store->quartos[store->totalQuartos++] = quarto;
    return 1;
}

Quarto *quarto_buscar(DataStore *store, int numero)
{
    for (int i = 0; i < store->totalQuartos; i++)
    {
        if (store->quartos[i].numero == numero)
        {
            return &store->quartos[i];
        }
    }
    return NULL;
}

const Quarto *quarto_buscar_const(const DataStore *store, int numero)
{
    for (int i = 0; i < store->totalQuartos; i++)
    {
        if (store->quartos[i].numero == numero)
        {
            return &store->quartos[i];
        }
    }
    return NULL;
}

void quarto_alterar_status(Quarto *quarto, int status)
{
    if (quarto)
    {
        quarto->status = status;
    }
}

void quarto_listar(const DataStore *store)
{
    if (store->totalQuartos == 0)
    {
        printf("Nenhum quarto cadastrado.\n");
        return;
    }
    for (int i = 0; i < store->totalQuartos; i++)
    {
        const Quarto *q = &store->quartos[i];
        printf("Quarto %d | Capacidade: %d | Diaria: %.2f | Status: %s\n", q->numero, q->capacidade, q->valorDiaria, q->status == STATUS_OCUPADO ? "Ocupado" : "Livre");
    }
}

int quarto_atualizar(DataStore *store, int numero, int capacidade, float valorDiaria)
{
    Quarto *quarto = quarto_buscar(store, numero);
    if (!quarto)
    {
        return 0;
    }
    quarto->capacidade = capacidade;
    quarto->valorDiaria = valorDiaria;
    return 1;
}

int quarto_remover(DataStore *store, int numero)
{
    int indice = -1;
    for (int i = 0; i < store->totalQuartos; i++)
    {
        if (store->quartos[i].numero == numero)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        return 0;
    }
    if (store->quartos[indice].status == STATUS_OCUPADO || quarto_tem_estadia_ativa(store, numero))
    {
        return 0;
    }
    for (int i = indice; i < store->totalQuartos - 1; i++)
    {
        store->quartos[i] = store->quartos[i + 1];
    }
    store->totalQuartos--;
    return 1;
}
