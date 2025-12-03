#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include "data/datastore.h"

int funcionario_cadastrar(DataStore *store, const char *nome, const char *telefone, const char *cargo, float salario);
const Funcionario *funcionario_buscar_codigo(const DataStore *store, int codigo);
const Funcionario *funcionario_buscar_nome(const DataStore *store, const char *nome);
void funcionario_imprimir(const Funcionario *funcionario);

#endif
