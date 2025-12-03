#include "room_service.h"
#include <stddef.h>

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
