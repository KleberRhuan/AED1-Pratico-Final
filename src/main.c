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

static void menu_atualizar_cliente(DataStore *store)
{
    printf("Codigo do cliente: ");
    int codigo = ler_inteiro();
    char nome[64];
    char endereco[128];
    char telefone[20];
    printf("Novo nome: ");
    ler_linha(nome, sizeof(nome));
    printf("Novo endereco: ");
    ler_linha(endereco, sizeof(endereco));
    printf("Novo telefone: ");
    ler_linha(telefone, sizeof(telefone));
    if (cliente_atualizar(store, codigo, nome, endereco, telefone))
    {
        printf("Cliente atualizado.\n");
    }
    else
    {
        printf("Cliente nao encontrado.\n");
    }
}

static void menu_remover_cliente(DataStore *store)
{
    printf("Codigo do cliente: ");
    int codigo = ler_inteiro();
    if (cliente_remover(store, codigo))
    {
        printf("Cliente removido.\n");
    }
    else
    {
        printf("Nao foi possivel remover (codigo invalido ou cliente possui estadias registradas).\n");
    }
}

static void menu_listar_clientes(const DataStore *store)
{
    cliente_listar(store);
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

static void menu_atualizar_funcionario(DataStore *store)
{
    printf("Codigo do funcionario: ");
    int codigo = ler_inteiro();
    char nome[64];
    char telefone[20];
    char cargo[32];
    printf("Novo nome: ");
    ler_linha(nome, sizeof(nome));
    printf("Novo telefone: ");
    ler_linha(telefone, sizeof(telefone));
    printf("Novo cargo: ");
    ler_linha(cargo, sizeof(cargo));
    printf("Novo salario: ");
    float salario = ler_float();
    if (funcionario_atualizar(store, codigo, nome, telefone, cargo, salario))
    {
        printf("Funcionario atualizado.\n");
    }
    else
    {
        printf("Funcionario nao encontrado.\n");
    }
}

static void menu_remover_funcionario(DataStore *store)
{
    printf("Codigo do funcionario: ");
    int codigo = ler_inteiro();
    if (funcionario_remover(store, codigo))
    {
        printf("Funcionario removido.\n");
    }
    else
    {
        printf("Funcionario nao encontrado.\n");
    }
}

static void menu_listar_funcionarios(const DataStore *store)
{
    funcionario_listar(store);
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

static void menu_atualizar_quarto(DataStore *store)
{
    printf("Numero do quarto: ");
    int numero = ler_inteiro();
    printf("Nova capacidade de hospedes: ");
    int capacidade = ler_inteiro();
    printf("Novo valor da diaria: ");
    float diaria = ler_float();
    if (quarto_atualizar(store, numero, capacidade, diaria))
    {
        printf("Quarto atualizado.\n");
    }
    else
    {
        printf("Quarto nao encontrado.\n");
    }
}

static void menu_remover_quarto(DataStore *store)
{
    printf("Numero do quarto: ");
    int numero = ler_inteiro();
    if (quarto_remover(store, numero))
    {
        printf("Quarto removido.\n");
    }
    else
    {
        printf("Nao foi possivel remover (quarto inexistente ou ocupado/possui estadias ativas).\n");
    }
}

static void menu_listar_quartos(const DataStore *store)
{
    quarto_listar(store);
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

static void menu_atualizar_estadia(DataStore *store)
{
    printf("Codigo da estadia: ");
    int codigo = ler_inteiro();
    printf("Nova quantidade de hospedes: ");
    int quantidade = ler_inteiro();
    Data entrada;
    Data saida;
    printf("Nova data de entrada:\n");
    ler_data(&entrada);
    printf("Nova data de saida:\n");
    ler_data(&saida);
    if (estadia_atualizar(store, codigo, quantidade, entrada, saida))
    {
        printf("Estadia atualizada.\n");
    }
    else
    {
        printf("Nao foi possivel atualizar (codigo invalido, estadia encerrada ou sem quarto disponivel).\n");
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

static void menu_cancelar_estadia(DataStore *store)
{
    printf("Codigo da estadia: ");
    int codigo = ler_inteiro();
    if (estadia_cancelar(store, codigo))
    {
        printf("Estadia cancelada/removida.\n");
    }
    else
    {
        printf("Estadia nao encontrada.\n");
    }
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

static void menu_listar_estadias(const DataStore *store)
{
    estadia_listar_todas(store);
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
    printf("1  - Cadastrar cliente\n");
    printf("2  - Atualizar cliente\n");
    printf("3  - Remover cliente\n");
    printf("4  - Listar clientes\n");
    printf("5  - Cadastrar funcionario\n");
    printf("6  - Atualizar funcionario\n");
    printf("7  - Remover funcionario\n");
    printf("8  - Listar funcionarios\n");
    printf("9  - Cadastrar quarto\n");
    printf("10 - Atualizar quarto\n");
    printf("11 - Remover quarto\n");
    printf("12 - Listar quartos\n");
    printf("13 - Cadastrar estadia\n");
    printf("14 - Atualizar estadia\n");
    printf("15 - Cancelar estadia\n");
    printf("16 - Dar baixa em estadia\n");
    printf("17 - Pesquisar cliente/funcionario\n");
    printf("18 - Listar estadias de um cliente\n");
    printf("19 - Listar todas as estadias\n");
    printf("20 - Backup de dados\n");
    printf("21 - Restaurar dados\n");
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
            menu_atualizar_cliente(&store);
            break;
        case 3:
            menu_remover_cliente(&store);
            break;
        case 4:
            menu_listar_clientes(&store);
            break;
        case 5:
            menu_cadastrar_funcionario(&store);
            break;
        case 6:
            menu_atualizar_funcionario(&store);
            break;
        case 7:
            menu_remover_funcionario(&store);
            break;
        case 8:
            menu_listar_funcionarios(&store);
            break;
        case 9:
            menu_cadastrar_quarto(&store);
            break;
        case 10:
            menu_atualizar_quarto(&store);
            break;
        case 11:
            menu_remover_quarto(&store);
            break;
        case 12:
            menu_listar_quartos(&store);
            break;
        case 13:
            menu_cadastrar_estadia(&store);
            break;
        case 14:
            menu_atualizar_estadia(&store);
            break;
        case 15:
            menu_cancelar_estadia(&store);
            break;
        case 16:
            menu_baixa_estadia(&store);
            break;
        case 17:
            menu_pesquisa(&store);
            break;
        case 18:
            menu_estadias_do_cliente(&store);
            break;
        case 19:
            menu_listar_estadias(&store);
            break;
        case 20:
            menu_backup(&store);
            break;
        case 21:
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
