#ifndef UTILS_DATE_H
#define UTILS_DATE_H

#include "domain/domain.h"

int data_comparar(Data a, Data b);
int data_calcular_diarias(Data entrada, Data saida);
int datas_sobrepostas(Data inicioA, Data fimA, Data inicioB, Data fimB);

#endif
