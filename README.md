# Registro de Agentes de IA

Projeto desenvolvido em linguagem C para o cadastro e gerenciamento de agentes de Inteligência Artificial.

O sistema permite cadastrar agentes, consultar os registros e armazenar suas informações em um arquivo de texto, mantendo os dados salvos mesmo após o encerramento do programa.

## Funcionalidades

- Cadastro de agentes;
- Listagem dos agentes cadastrados;
- Busca por ID;
- Busca por nome;
- Armazenamento de nome, instruções e nota;
- Salvamento dos dados em arquivo de texto.

## Tecnologias utilizadas

- Linguagem C;
- Arrays;
- Funções;
- Manipulação de arquivos.

## Estrutura do projeto

```text
AI-Agent-Registry/
└── src/
    ├── dados/
    │   └── agentes.txt
    └── main.c
```

## Como executar

É necessário ter um compilador C, como o GCC, instalado.

Entre na pasta `src`:

```bash
cd src
```

Compile o programa:

```bash
gcc main.c -o registro-agentes
```

Execute:

**Linux:**
```bash
./registro-agentes
```

**Windows:**
```bash
registro-agentes.exe
```

## Integrantes

- Juliano Ferreira
- David
- Alisson
- Luana
- Guilherme
- Juan
