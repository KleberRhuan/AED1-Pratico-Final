#include "persistence.h"
#include <stdio.h>

int backup_salvar(const DataStore *store)
{
    FILE *fClientes = fopen("clientes.dat", "wb");
    FILE *fFuncionarios = fopen("funcionarios.dat", "wb");
    FILE *fQuartos = fopen("quartos.dat", "wb");
    FILE *fEstadias = fopen("estadias.dat", "wb");
    if (!fClientes || !fFuncionarios || !fQuartos || !fEstadias)
    {
        if (fClientes)
            fclose(fClientes);
        if (fFuncionarios)
            fclose(fFuncionarios);
        if (fQuartos)
            fclose(fQuartos);
        if (fEstadias)
            fclose(fEstadias);
        return 0;
    }

    fwrite(&store->totalClientes, sizeof(int), 1, fClientes);
    fwrite(store->clientes, sizeof(Cliente), store->totalClientes, fClientes);
    fwrite(&store->totalFuncionarios, sizeof(int), 1, fFuncionarios);
    fwrite(store->funcionarios, sizeof(Funcionario), store->totalFuncionarios, fFuncionarios);
    fwrite(&store->totalQuartos, sizeof(int), 1, fQuartos);
    fwrite(store->quartos, sizeof(Quarto), store->totalQuartos, fQuartos);
    fwrite(&store->totalEstadias, sizeof(int), 1, fEstadias);
    fwrite(store->estadias, sizeof(Estadia), store->totalEstadias, fEstadias);

    fclose(fClientes);
    fclose(fFuncionarios);
    fclose(fQuartos);
    fclose(fEstadias);
    return 1;
}

int backup_restaurar(DataStore *store)
{
    FILE *fClientes = fopen("clientes.dat", "rb");
    FILE *fFuncionarios = fopen("funcionarios.dat", "rb");
    FILE *fQuartos = fopen("quartos.dat", "rb");
    FILE *fEstadias = fopen("estadias.dat", "rb");
    if (!fClientes || !fFuncionarios || !fQuartos || !fEstadias)
    {
        if (fClientes)
            fclose(fClientes);
        if (fFuncionarios)
            fclose(fFuncionarios);
        if (fQuartos)
            fclose(fQuartos);
        if (fEstadias)
            fclose(fEstadias);
        return 0;
    }

    fread(&store->totalClientes, sizeof(int), 1, fClientes);
    fread(store->clientes, sizeof(Cliente), store->totalClientes, fClientes);
    fread(&store->totalFuncionarios, sizeof(int), 1, fFuncionarios);
    fread(store->funcionarios, sizeof(Funcionario), store->totalFuncionarios, fFuncionarios);
    fread(&store->totalQuartos, sizeof(int), 1, fQuartos);
    fread(store->quartos, sizeof(Quarto), store->totalQuartos, fQuartos);
    fread(&store->totalEstadias, sizeof(int), 1, fEstadias);
    fread(store->estadias, sizeof(Estadia), store->totalEstadias, fEstadias);

    fclose(fClientes);
    fclose(fFuncionarios);
    fclose(fQuartos);
    fclose(fEstadias);

    datastore_atualizar_codigos(store);
    return 1;
}
