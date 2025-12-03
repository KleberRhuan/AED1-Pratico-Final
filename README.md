# Hotel Descanso Garantido (AED1)

Aplicação em C (linha de comando) para gerenciar um pequeno hotel: cadastro de clientes, funcionários e quartos, abertura/baixa de estadias e backup/restauração de dados em arquivos locais.

## Estrutura
- `src/main.c`: menu principal e fluxo da interface.
- `domain/` e `data/`: estruturas e armazenamento em memória (DataStore).
- `services/`: regras de negócio para clientes, funcionários, quartos e estadias.
- `utils/`: utilitários de entrada e manipulação de datas.
- `persistence/`: gravação/leitura dos snapshots binários (`*.dat`).
- `documentacao-hotel-descanso.docx`: documentação preenchida do sistema (com base no template fornecido).

## Requisitos
- Compilador C com suporte a C11 (ex.: `cc`, `clang` ou `gcc`).

## Como compilar e executar
```bash
make          # compila em ./main
./main        # executa o sistema
make clean    # remove objetos e binário
```

## Notas de uso
- Os cadastros são mantidos em memória; use as opções de backup/restauração para persistir os dados em `clientes.dat`, `funcionarios.dat`, `quartos.dat` e `estadias.dat`.
- O programa não faz validação profunda de entrada (menu textual), portanto digite apenas números onde solicitado.

## Documentação
- Consulte `documentacao-hotel-descanso.docx` para descrição das seções do sistema, arquitetura, principais funções e casos de teste sugeridos.
