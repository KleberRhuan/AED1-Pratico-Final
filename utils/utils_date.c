#include "utils_date.h"

static int data_para_dias(Data data)
{
    int a = (14 - data.mes) / 12;
    int y = data.ano + 4800 - a;
    int m = data.mes + 12 * a - 3;
    return data.dia + ((153 * m + 2) / 5) + 365 * y + y / 4 - y / 100 + y / 400;
}

int data_comparar(Data a, Data b)
{
    if (a.ano != b.ano)
    {
        return (a.ano < b.ano) ? -1 : 1;
    }
    if (a.mes != b.mes)
    {
        return (a.mes < b.mes) ? -1 : 1;
    }
    if (a.dia != b.dia)
    {
        return (a.dia < b.dia) ? -1 : 1;
    }
    return 0;
}

int data_calcular_diarias(Data entrada, Data saida)
{
    int inicio = data_para_dias(entrada);
    int fim = data_para_dias(saida);
    if (fim <= inicio)
    {
        return 0;
    }
    return fim - inicio;
}

int datas_sobrepostas(Data inicioA, Data fimA, Data inicioB, Data fimB)
{
    int cmpInicioFim = data_comparar(inicioA, fimB);
    int cmpFimInicio = data_comparar(fimA, inicioB);
    return cmpInicioFim < 0 && cmpFimInicio > 0;
}
