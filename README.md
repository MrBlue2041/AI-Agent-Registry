# Registro de Agentes de IA

Projeto desenvolvido em linguagem C para cadastrar e organizar agentes de Inteligência Artificial. O sistema permite armazenar informações sobre cada agente, consultar os registros e manter os dados salvos em um arquivo de texto.

## Funcionalidades

- Cadastrar agentes de IA;
- Listar os agentes cadastrados;
- Buscar agentes pelo ID;
- Buscar agentes pelo nome;
- Armazenar nome, instruções e nota de cada agente;
- Salvar os dados em arquivo para que permaneçam disponíveis ao iniciar o programa novamente.

## Tecnologias utilizadas

- Linguagem C;
- Manipulação de arquivos (`fopen`, `fgets`, `fprintf` e `fclose`);
- Arrays e funções;
- Arquivo de texto para armazenamento dos dados.

## Como executar

É necessário ter um compilador C instalado, como o GCC.

No terminal, dentro da pasta do projeto, execute:

```bash
gcc main.c -o registro-agentes
```

Depois, execute o programa:

```bash
./registro-agentes
```

No Windows, pode ser utilizado:

```bash
registro-agentes.exe
```

## Armazenamento

Os registros são armazenados no arquivo `dados/agentes.txt`. Dessa forma, as informações cadastradas não são perdidas quando o programa é encerrado.

## Integrantes

- Juliano Ferreira
- David
- Alisson
- Luana
- Guilherme
- Juan
