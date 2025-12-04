#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include "data/datastore.h"

int cliente_cadastrar(DataStore *store, const char *nome, const char *endereco, const char *telefone);
const Cliente *cliente_buscar_codigo(const DataStore *store, int codigo);
const Cliente *cliente_buscar_nome(const DataStore *store, const char *nome);
void cliente_imprimir(const Cliente *cliente);
void cliente_listar(const DataStore *store);
int cliente_atualizar(DataStore *store, int codigo, const char *nome, const char *endereco, const char *telefone);
int cliente_remover(DataStore *store, int codigo);

#endif
