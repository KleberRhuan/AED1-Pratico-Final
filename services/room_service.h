#ifndef ROOM_SERVICE_H
#define ROOM_SERVICE_H

#include "data/datastore.h"

int quarto_cadastrar(DataStore *store, int numero, int capacidade, float valorDiaria);
Quarto *quarto_buscar(DataStore *store, int numero);
const Quarto *quarto_buscar_const(const DataStore *store, int numero);
void quarto_alterar_status(Quarto *quarto, int status);

#endif
