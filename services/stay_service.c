#include "stay_service.h"
#include "client_service.h"
#include "room_service.h"
#include "utils/utils_date.h"
#include <stdio.h>

static int quarto_disponivel(const DataStore *store, const Quarto *quarto, Data entrada, Data saida)
{
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        if (e->ativa && e->numeroQuarto == quarto->numero && datas_sobrepostas(entrada, saida, e->entrada, e->saida))
        {
            return 0;
        }
    }
    return 1;
}

static Quarto *escolher_quarto(DataStore *store, int quantidadeHospedes, Data entrada, Data saida)
{
    for (int i = 0; i < store->totalQuartos; i++)
    {
        Quarto *quarto = &store->quartos[i];
        if (quarto->capacidade >= quantidadeHospedes && quarto->status == STATUS_DESOCUPADO && quarto_disponivel(store, quarto, entrada, saida))
        {
            return quarto;
        }
    }
    return NULL;
}

int estadia_cadastrar(DataStore *store, int codigoCliente, int quantidadeHospedes, Data entrada, Data saida)
{
    if (store->totalEstadias >= MAX_ESTADIAS || !cliente_buscar_codigo(store, codigoCliente))
    {
        return -1;
    }
    int diarias = data_calcular_diarias(entrada, saida);
    if (diarias <= 0)
    {
        return -1;
    }
    Quarto *quarto = escolher_quarto(store, quantidadeHospedes, entrada, saida);
    if (!quarto)
    {
        return -1;
    }

    Estadia estadia;
    estadia.codigo = datastore_proximo_estadia(store);
    estadia.codigoCliente = codigoCliente;
    estadia.numeroQuarto = quarto->numero;
    estadia.entrada = entrada;
    estadia.saida = saida;
    estadia.diarias = diarias;
    estadia.quantidadeHospedes = quantidadeHospedes;
    estadia.ativa = 1;
    store->estadias[store->totalEstadias++] = estadia;
    quarto_alterar_status(quarto, STATUS_OCUPADO);
    return estadia.codigo;
}

float estadia_dar_baixa(DataStore *store, int codigoEstadia, int *encontrada)
{
    *encontrada = 0;
    for (int i = 0; i < store->totalEstadias; i++)
    {
        Estadia *e = &store->estadias[i];
        if (e->codigo == codigoEstadia && e->ativa)
        {
            *encontrada = 1;
            e->ativa = 0;
            Quarto *quarto = quarto_buscar(store, e->numeroQuarto);
            if (quarto)
            {
                quarto_alterar_status(quarto, STATUS_DESOCUPADO);
                return e->diarias * quarto->valorDiaria;
            }
            return 0.0f;
        }
    }
    return 0.0f;
}

void estadia_listar_do_cliente(const DataStore *store, int codigoCliente)
{
    int encontrou = 0;
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        if (e->codigoCliente == codigoCliente)
        {
            encontrou = 1;
            printf("Estadia %d | Quarto %d | Entrada: %02d/%02d/%04d | Saida: %02d/%02d/%04d | Diarias: %d | Status: %s\n",
                   e->codigo, e->numeroQuarto, e->entrada.dia, e->entrada.mes, e->entrada.ano, e->saida.dia, e->saida.mes, e->saida.ano, e->diarias, e->ativa ? "Ativa" : "Encerrada");
        }
    }
    if (!encontrou)
    {
        printf("Nenhuma estadia encontrada para o cliente informado.\n");
    }
}
