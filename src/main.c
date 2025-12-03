#include <stdio.h>
#include "data/datastore.h"
#include "services/client_service.h"
#include "services/employee_service.h"
#include "services/room_service.h"
#include "services/stay_service.h"
#include "persistence/persistence.h"
#include "utils/utils_io.h"

static void ler_data(Data *data)
{
    printf("Dia: ");
    data->dia = ler_inteiro();
    printf("Mes: ");
    data->mes = ler_inteiro();
    printf("Ano: ");
    data->ano = ler_inteiro();
}

static void menu_cadastrar_cliente(DataStore *store)
{
    char nome[64];
    char endereco[128];
    char telefone[20];
    printf("Nome do cliente: ");
    ler_linha(nome, sizeof(nome));
    printf("Endereco: ");
    ler_linha(endereco, sizeof(endereco));
    printf("Telefone: ");
    ler_linha(telefone, sizeof(telefone));
    int codigo = cliente_cadastrar(store, nome, endereco, telefone);
    if (codigo > 0)
    {
        printf("Cliente cadastrado com codigo %d\n", codigo);
    }
    else
    {
        printf("Falha ao cadastrar cliente (limite ou dados invalidos).\n");
    }
}

static void menu_cadastrar_funcionario(DataStore *store)
{
    char nome[64];
    char telefone[20];
    char cargo[32];
    printf("Nome do funcionario: ");
    ler_linha(nome, sizeof(nome));
    printf("Telefone: ");
    ler_linha(telefone, sizeof(telefone));
    printf("Cargo: ");
    ler_linha(cargo, sizeof(cargo));
    printf("Salario: ");
    float salario = ler_float();
    int codigo = funcionario_cadastrar(store, nome, telefone, cargo, salario);
    if (codigo > 0)
    {
        printf("Funcionario cadastrado com codigo %d\n", codigo);
    }
    else
    {
        printf("Falha ao cadastrar funcionario.\n");
    }
}

static void menu_cadastrar_quarto(DataStore *store)
{
    printf("Numero do quarto: ");
    int numero = ler_inteiro();
    printf("Capacidade de hospedes: ");
    int capacidade = ler_inteiro();
    printf("Valor da diaria: ");
    float diaria = ler_float();
    if (quarto_cadastrar(store, numero, capacidade, diaria))
    {
        printf("Quarto cadastrado.\n");
    }
    else
    {
        printf("Falha ao cadastrar quarto (numero repetido ou limite atingido).\n");
    }
}

static void menu_cadastrar_estadia(DataStore *store)
{
    printf("Codigo do cliente: ");
    int codigoCliente = ler_inteiro();
    printf("Quantidade de hospedes: ");
    int quantidade = ler_inteiro();
    Data entrada;
    Data saida;
    printf("Data de entrada:\n");
    ler_data(&entrada);
    printf("Data de saida:\n");
    ler_data(&saida);
    int codigo = estadia_cadastrar(store, codigoCliente, quantidade, entrada, saida);
    if (codigo > 0)
    {
        printf("Estadia cadastrada com codigo %d\n", codigo);
    }
    else
    {
        printf("Nao foi possivel cadastrar a estadia.\n");
    }
}

static void menu_baixa_estadia(DataStore *store)
{
    printf("Codigo da estadia: ");
    int codigo = ler_inteiro();
    int encontrada = 0;
    float total = estadia_dar_baixa(store, codigo, &encontrada);
    if (!encontrada)
    {
        printf("Estadia nao encontrada ou ja encerrada.\n");
        return;
    }
    printf("Valor total a pagar: R$ %.2f\n", total);
}

static void menu_pesquisa(DataStore *store)
{
    printf("Pesquisar (1-Cliente, 2-Funcionario): ");
    int tipo = ler_inteiro();
    printf("Buscar por (1-Codigo, 2-Nome): ");
    int modo = ler_inteiro();
    if (tipo == 1)
    {
        if (modo == 1)
        {
            printf("Codigo do cliente: ");
            int codigo = ler_inteiro();
            const Cliente *c = cliente_buscar_codigo(store, codigo);
            c ? cliente_imprimir(c) : printf("Cliente nao encontrado.\n");
        }
        else
        {
            char nome[64];
            printf("Nome do cliente: ");
            ler_linha(nome, sizeof(nome));
            const Cliente *c = cliente_buscar_nome(store, nome);
            c ? cliente_imprimir(c) : printf("Cliente nao encontrado.\n");
        }
    }
    else if (tipo == 2)
    {
        if (modo == 1)
        {
            printf("Codigo do funcionario: ");
            int codigo = ler_inteiro();
            const Funcionario *f = funcionario_buscar_codigo(store, codigo);
            f ? funcionario_imprimir(f) : printf("Funcionario nao encontrado.\n");
        }
        else
        {
            char nome[64];
            printf("Nome do funcionario: ");
            ler_linha(nome, sizeof(nome));
            const Funcionario *f = funcionario_buscar_nome(store, nome);
            f ? funcionario_imprimir(f) : printf("Funcionario nao encontrado.\n");
        }
    }
}

static void menu_estadias_do_cliente(DataStore *store)
{
    printf("Buscar estadias por (1-Codigo do cliente, 2-Nome do cliente): ");
    int modo = ler_inteiro();
    int codigoCliente = -1;
    if (modo == 1)
    {
        printf("Codigo do cliente: ");
        codigoCliente = ler_inteiro();
    }
    else
    {
        char nome[64];
        printf("Nome do cliente: ");
        ler_linha(nome, sizeof(nome));
        const Cliente *c = cliente_buscar_nome(store, nome);
        if (c)
        {
            codigoCliente = c->codigo;
        }
    }
    if (codigoCliente == -1)
    {
        printf("Cliente nao encontrado.\n");
        return;
    }
    estadia_listar_do_cliente(store, codigoCliente);
}

static void menu_backup(DataStore *store)
{
    if (backup_salvar(store))
    {
        printf("Backup salvo.\n");
    }
    else
    {
        printf("Falha ao salvar backup.\n");
    }
}

static void menu_restaurar(DataStore *store)
{
    if (backup_restaurar(store))
    {
        printf("Dados restaurados.\n");
    }
    else
    {
        printf("Falha ao restaurar (arquivos ausentes?).\n");
    }
}

static void exibir_menu()
{
    printf("\n--- Hotel Descanso Garantido ---\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar funcionario\n");
    printf("3 - Cadastrar quarto\n");
    printf("4 - Cadastrar estadia\n");
    printf("5 - Dar baixa em estadia\n");
    printf("6 - Pesquisar cliente/funcionario\n");
    printf("7 - Listar estadias de um cliente\n");
    printf("8 - Backup de dados\n");
    printf("9 - Restaurar dados\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main(void)
{
    DataStore store;
    datastore_init(&store);
    int opcao = -1;

    do
    {
        exibir_menu();
        opcao = ler_inteiro();
        switch (opcao)
        {
        case 1:
            menu_cadastrar_cliente(&store);
            break;
        case 2:
            menu_cadastrar_funcionario(&store);
            break;
        case 3:
            menu_cadastrar_quarto(&store);
            break;
        case 4:
            menu_cadastrar_estadia(&store);
            break;
        case 5:
            menu_baixa_estadia(&store);
            break;
        case 6:
            menu_pesquisa(&store);
            break;
        case 7:
            menu_estadias_do_cliente(&store);
            break;
        case 8:
            menu_backup(&store);
            break;
        case 9:
            menu_restaurar(&store);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
