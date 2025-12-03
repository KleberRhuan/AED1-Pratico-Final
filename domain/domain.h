#ifndef DOMAIN_H
#define DOMAIN_H

#define MAX_CLIENTES 200
#define MAX_FUNCIONARIOS 200
#define MAX_QUARTOS 120
#define MAX_ESTADIAS 400

#define STATUS_DESOCUPADO 0
#define STATUS_OCUPADO 1

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int codigo;
    char nome[64];
    char endereco[128];
    char telefone[20];
} Cliente;

typedef struct
{
    int codigo;
    char nome[64];
    char telefone[20];
    char cargo[32];
    float salario;
} Funcionario;

typedef struct
{
    int numero;
    int capacidade;
    float valorDiaria;
    int status;
} Quarto;

typedef struct
{
    int codigo;
    int codigoCliente;
    int numeroQuarto;
    Data entrada;
    Data saida;
    int diarias;
    int quantidadeHospedes;
    int ativa;
} Estadia;

#endif
