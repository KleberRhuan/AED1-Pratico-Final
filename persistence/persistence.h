#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "data/datastore.h"

int backup_salvar(const DataStore *store);
int backup_restaurar(DataStore *store);

#endif
