#ifndef STAY_SERVICE_H
#define STAY_SERVICE_H

#include "data/datastore.h"

int estadia_cadastrar(DataStore *store, int codigoCliente, int quantidadeHospedes, Data entrada, Data saida);
float estadia_dar_baixa(DataStore *store, int codigoEstadia, int *encontrada);
void estadia_listar_do_cliente(const DataStore *store, int codigoCliente);

#endif
