#ifndef DATASTORE_H
#define DATASTORE_H

#include "domain/domain.h"

typedef struct
{
    Cliente clientes[MAX_CLIENTES];
    int totalClientes;
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int totalFuncionarios;
    Quarto quartos[MAX_QUARTOS];
    int totalQuartos;
    Estadia estadias[MAX_ESTADIAS];
    int totalEstadias;
    int proximoCodigoCliente;
    int proximoCodigoFuncionario;
    int proximoCodigoEstadia;
} DataStore;

void datastore_init(DataStore *store);
int datastore_proximo_cliente(DataStore *store);
int datastore_proximo_funcionario(DataStore *store);
int datastore_proximo_estadia(DataStore *store);
int datastore_atualizar_codigos(DataStore *store);

#endif
