#include "stay_service.h"
#include "client_service.h"
#include "room_service.h"
#include "utils/utils_date.h"
#include <stdio.h>

static int quarto_disponivel(const DataStore *store, const Quarto *quarto, Data entrada, Data saida, int ignorarCodigoEstadia)
{
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        if (e->ativa && e->numeroQuarto == quarto->numero && e->codigo != ignorarCodigoEstadia && datas_sobrepostas(entrada, saida, e->entrada, e->saida))
        {
            return 0;
        }
    }
    return 1;
}

static int existe_outra_estadia_ativa_no_quarto(const DataStore *store, int numeroQuarto, int ignorarCodigoEstadia)
{
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        if (e->ativa && e->numeroQuarto == numeroQuarto && e->codigo != ignorarCodigoEstadia)
        {
            return 1;
        }
    }
    return 0;
}

static Quarto *escolher_quarto(DataStore *store, int quantidadeHospedes, Data entrada, Data saida, int ignorarCodigoEstadia, int numeroAtual)
{
    for (int i = 0; i < store->totalQuartos; i++)
    {
        Quarto *quarto = &store->quartos[i];
        if (quarto->capacidade >= quantidadeHospedes &&
            (quarto->status == STATUS_DESOCUPADO || quarto->numero == numeroAtual) &&
            quarto_disponivel(store, quarto, entrada, saida, ignorarCodigoEstadia))
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
    Quarto *quarto = escolher_quarto(store, quantidadeHospedes, entrada, saida, -1, -1);
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
                if (!existe_outra_estadia_ativa_no_quarto(store, quarto->numero, e->codigo))
                {
                    quarto_alterar_status(quarto, STATUS_DESOCUPADO);
                }
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

void estadia_listar_todas(const DataStore *store)
{
    if (store->totalEstadias == 0)
    {
        printf("Nenhuma estadia cadastrada.\n");
        return;
    }
    for (int i = 0; i < store->totalEstadias; i++)
    {
        const Estadia *e = &store->estadias[i];
        printf("Estadia %d | Cliente %d | Quarto %d | Entrada: %02d/%02d/%04d | Saida: %02d/%02d/%04d | Hospedes: %d | Status: %s\n",
               e->codigo, e->codigoCliente, e->numeroQuarto, e->entrada.dia, e->entrada.mes, e->entrada.ano, e->saida.dia, e->saida.mes, e->saida.ano, e->quantidadeHospedes, e->ativa ? "Ativa" : "Encerrada");
    }
}

int estadia_atualizar(DataStore *store, int codigoEstadia, int quantidadeHospedes, Data entrada, Data saida)
{
    Estadia *estadia = NULL;
    for (int i = 0; i < store->totalEstadias; i++)
    {
        if (store->estadias[i].codigo == codigoEstadia)
        {
            estadia = &store->estadias[i];
            break;
        }
    }
    if (!estadia || !estadia->ativa)
    {
        return 0;
    }

    int diarias = data_calcular_diarias(entrada, saida);
    if (diarias <= 0)
    {
        return 0;
    }

    Quarto *quartoAtual = quarto_buscar(store, estadia->numeroQuarto);
    Quarto *quartoEscolhido = escolher_quarto(store, quantidadeHospedes, entrada, saida, codigoEstadia, quartoAtual ? quartoAtual->numero : -1);
    if (!quartoEscolhido)
    {
        return 0;
    }

    if (quartoAtual && quartoEscolhido->numero != quartoAtual->numero)
    {
        if (!existe_outra_estadia_ativa_no_quarto(store, quartoAtual->numero, estadia->codigo))
        {
            quarto_alterar_status(quartoAtual, STATUS_DESOCUPADO);
        }
        quarto_alterar_status(quartoEscolhido, STATUS_OCUPADO);
    }

    estadia->numeroQuarto = quartoEscolhido->numero;
    estadia->entrada = entrada;
    estadia->saida = saida;
    estadia->diarias = diarias;
    estadia->quantidadeHospedes = quantidadeHospedes;
    return 1;
}

int estadia_cancelar(DataStore *store, int codigoEstadia)
{
    int indice = -1;
    for (int i = 0; i < store->totalEstadias; i++)
    {
        if (store->estadias[i].codigo == codigoEstadia)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        return 0;
    }

    Estadia *estadia = &store->estadias[indice];
    if (estadia->ativa)
    {
        Quarto *quarto = quarto_buscar(store, estadia->numeroQuarto);
        if (quarto && !existe_outra_estadia_ativa_no_quarto(store, quarto->numero, estadia->codigo))
        {
            quarto_alterar_status(quarto, STATUS_DESOCUPADO);
        }
    }

    for (int i = indice; i < store->totalEstadias - 1; i++)
    {
        store->estadias[i] = store->estadias[i + 1];
    }
    store->totalEstadias--;
    return 1;
}
