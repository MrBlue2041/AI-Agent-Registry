
#include <stdio.h>
#include <conio.h>

#define MAX_AGENTES 50
#define TAM_NOME 80
#define TAM_INSTRUCAO 1000

#define PATH_DADOS "dados/agentes.txt"

int sistemaOn = 1;

int ids[MAX_AGENTES];
char nomes[MAX_AGENTES][TAM_NOME + 1];
char instrucoes[MAX_AGENTES][TAM_INSTRUCAO + 1];
int notas[MAX_AGENTES];

int totalAgentes = 0;
int proximoId = 1;

char *categorias[] = {
    "Cadastrar Agente",
    "Listar Agentes",
    "Buscar Agente por ID",
    "Buscar Agente por nome",
    "Sair"
};

#define MAX_CATEGORIAS (sizeof(categorias) / sizeof(categorias[0]))

void iniciar_sistema(void);
void carregar_menu(void);
void apagar_console(void);
void limpar_buffer(void);
int ler_opcao(void);
int ler_texto(char destino[], int max);
int validar_scanf(char texto[]);
void copiar_texto(char destino[], char origem[]);
void pagina_continuar();

void cadastrar_agente(void);
void buscar_agentes(void);
void buscar_por_id(void);
void buscar_por_nome(void);
void menu_agente(int pos);
void exibir_agente(int pos);
void editar_agente(int pos);
void excluir_agente(int pos);
int encontrar_posicao_por_id(int id);
int nome_contem(int pos, char busca[]);

void carregar_dados(void);
int salvar_dados(void);

int main(void) {

    carregar_dados();

    iniciar_sistema();

    return 0;
}

void iniciar_sistema(void) {

    int sessao = 0;

    while (sistemaOn == 1) {

        printf("\n");
        printf("==================================================\n");
        printf("                                                  \n");
        printf("             REGISTRO DE AGENTES DE IA            \n");
        printf("                                                  \n");
        printf("==================================================\n");
        printf("                                                  \n");
        printf("                  PAGINA INICIAL                  \n");
        printf("                                                  \n");
        printf("                    1 - Entrar                    \n");
        printf("                    2 - Sair                      \n");
        printf("                                                  \n");
        printf("==================================================\n");
        printf("                                                  \n");
        printf("                                                  \n");
        printf("==================================================\n");
        printf("\n");
        printf("Selecione uma opcao: ");

        sessao = ler_opcao();

        switch (sessao) {

            case 1:
                apagar_console();
                carregar_menu();
                break;

            case 2:
                apagar_console();
                sistemaOn = 0;
                printf("Voce foi desconectado do programa.\n");
                break;

            default:
                apagar_console();
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void carregar_menu(void) {

    int sessao = 0;
    int menuOn = 1;

    do {

        printf("\n");
        printf("=============== MENU PRINCIPAL ===============\n");

        for (int i = 0; i < (int) MAX_CATEGORIAS; i++) {
            printf("[%d] %s\n", i + 1, categorias[i]);
        }

        printf("\nDigite o numero da opcao desejada: ");

        sessao = ler_opcao();

        switch (sessao) {

            case 1:
                apagar_console();
                cadastrar_agente();
                pagina_continuar();
                break;

            case 2:
                apagar_console();
                buscar_agentes();
                pagina_continuar();
                break;

            case 3:
                apagar_console();
                buscar_por_id();
                pagina_continuar();
                break;

            case 4:
                apagar_console();
                buscar_por_nome();
                pagina_continuar();
                break;

            case 5:
                menuOn = 0;
                sistemaOn = 0;
                apagar_console();
                printf("Voce foi desconectado do programa.\n");
                break;

            default:
                apagar_console();
                printf("Opcao invalida!\n");
                break;
        }

    } while (menuOn == 1);
}

void limpar_buffer(void) {
    int c;

    c = getchar();

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int ler_opcao() {
    int opcao;

    if (scanf("%d", &opcao) == 1) {
        limpar_buffer();
        return opcao;
    }

    limpar_buffer();

    return -1;
}

int ler_texto(char destino[], int max) {
    char texto[TAM_INSTRUCAO + 2];
    int tamanho = 0;

    if (scanf(" %1001[^\n]", texto) != 1) {
        limpar_buffer();
        return 0;
    }

    limpar_buffer();

    while (texto[tamanho] != '\0') {
        tamanho++;
    }

    if (tamanho > max) {
        printf("O texto pode ter no maximo %d caracteres!\n", max);
        return 0;
    }

    if (!validar_scanf(texto)) {
        printf("Nao utilize ';' no texto!\n");
        return 0;
    }

    copiar_texto(destino, texto);

    return 1;
}

void apagar_console(void) {

    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

int validar_scanf(char texto[]){
    int valido = 1;

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ';') {
            valido = 0;
            break;
        }
    }
    return valido;
}

void copiar_texto(char destino[], char origem[]) {
    int i = 0;

    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}

void pagina_continuar(){
    printf("Pressione qualquer tecla para continuar...");

    _getch();

    apagar_console();
}

void carregar_dados(void) {
    char linha[1200];
    char nome[TAM_NOME + 1], instrucao[TAM_INSTRUCAO + 1];
    int id, nota;

    FILE *arquivo = fopen(PATH_DADOS, "r");

    if (arquivo == NULL) {
        return;
    }

    while (totalAgentes < MAX_AGENTES && fgets(linha, sizeof(linha), arquivo) != NULL) {

        if (sscanf(linha, "%d;%80[^;];%1000[^;];%d", &id, nome, instrucao, &nota) == 4) {
            ids[totalAgentes] = id;
            copiar_texto(nomes[totalAgentes], nome);
            copiar_texto(instrucoes[totalAgentes], instrucao);
            notas[totalAgentes] = nota;

            if (id >= proximoId) {
                proximoId = id + 1;
            }

            totalAgentes++;
        }
    }

    fclose(arquivo);
}

int salvar_dados(void) {
    int i;

    FILE *arquivo = fopen(PATH_DADOS, "w");

    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel salvar os dados.\n");
        return 0;
    }

    for (i = 0; i < totalAgentes; i++) {
        fprintf(arquivo, "%d;%s;%s;%d\n", ids[i], nomes[i], instrucoes[i], notas[i]);
    }

    fclose(arquivo);

    return 1;
}

int encontrar_posicao_por_id(int id) {
    int i;

    for (i = 0; i < totalAgentes; i++) {
        if (ids[i] == id) {
            return i;
        }
    }

    return -1;
}

void exibir_agente(int pos) {
    printf("\nID: %d\n", ids[pos]);
    printf("Nome: %s\n", nomes[pos]);
    printf("Instrucao: %s\n", instrucoes[pos]);
    printf("Nota: %d\n", notas[pos]);
}

int nome_contem(int pos, char busca[]) {
    int i, j;

    for (i = 0; nomes[pos][i] != '\0'; i++) {
        j = 0;

        while (busca[j] != '\0' && nomes[pos][i + j] == busca[j]) {
            j++;
        }

        if (busca[j] == '\0') {
            return 1;
        }
    }

    return 0;
}

void cadastrar_agente(){
    char nome[TAM_NOME + 1], instrucao[TAM_INSTRUCAO + 1];
    int nota, sessao = 1, cadastro_ativo = 1;

    if (totalAgentes >= MAX_AGENTES) {
        printf("------CADASTRO DE AGENTE------\n");
        printf("Limite de %d agentes atingido. Exclua um agente para cadastrar outro.\n", MAX_AGENTES);
        return;
    }

    do {
        switch(sessao){
            case 1: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira um nome para seu novo agente (ate %d caracteres):\n", TAM_NOME);

                if(!ler_texto(nome, TAM_NOME)){
                    sessao = 1;
                    break;
                }
                sessao++;
                break;
            }
            case 2: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira uma instrucao para seu novo agente (ate %d caracteres):\n", TAM_INSTRUCAO);
                printf("Lembrete: escreva instrucoes respeitosas, sem conteudo ofensivo ou discriminatorio.\n");

                if(!ler_texto(instrucao, TAM_INSTRUCAO)){
                    sessao = 2;
                    break;
                }
                sessao++;
                break;
            }
            case 3: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira uma nota (0 a 5) para seu novo agente:\n");
                nota = ler_opcao();

                if(nota < 0 || nota > 5){
                    printf("A nota deve ser um numero inteiro entre 0 e 5!\n");
                    sessao = 3;
                    break;
                }

                ids[totalAgentes] = proximoId;
                copiar_texto(nomes[totalAgentes], nome);
                copiar_texto(instrucoes[totalAgentes], instrucao);
                notas[totalAgentes] = nota;
                totalAgentes++;
                proximoId++;

                if(!salvar_dados()){
                    totalAgentes--;
                    proximoId--;
                    printf("Infelizmente houve um problema ao fazer o salvamento dos dados.\n");
                    sessao = 0;
                    break;
                }

                printf("Agente %s inserido com sucesso em nossa base de dados.\n", nome);
                sessao = 0;
                break;
            }
            default: {
                sessao = 0;
                cadastro_ativo = 0;
                break;
            }
        }

    } while(cadastro_ativo == 1);
}

void buscar_agentes(){
    int ordem[MAX_AGENTES];
    int i, j, aux, opcao;

    printf("------AGENTES CADASTRADOS------\n");

    if (totalAgentes == 0) {
        printf("\nNenhum agente cadastrado.\n");
        return;
    }

    printf("[1] Listar por ID\n");
    printf("[2] Listar por nota (da maior para a menor)\n");
    printf("Digite a opcao desejada: ");
    opcao = ler_opcao();

    for (i = 0; i < totalAgentes; i++) {
        ordem[i] = i;
    }

    if (opcao == 2) {
        for (i = 0; i < totalAgentes - 1; i++) {
            for (j = 0; j < totalAgentes - 1 - i; j++) {
                if (notas[ordem[j]] < notas[ordem[j + 1]]) {
                    aux = ordem[j];
                    ordem[j] = ordem[j + 1];
                    ordem[j + 1] = aux;
                }
            }
        }
    }

    for (i = 0; i < totalAgentes; i++) {
        exibir_agente(ordem[i]);
    }

    printf("\nTotal de agentes: %d de %d\n", totalAgentes, MAX_AGENTES);
}

void buscar_por_id(){
    int idBusca, pos;

    printf("------BUSCAR AGENTE POR ID------\n");
    printf("Digite o ID do agente:\n");
    idBusca = ler_opcao();

    pos = encontrar_posicao_por_id(idBusca);

    if (pos == -1) {
        printf("\nAgente nao encontrado.\n");
        return;
    }

    menu_agente(pos);
}

void buscar_por_nome(){
    char nomeBusca[TAM_NOME + 1];
    int i, pos, idEscolhido;
    int achou = 0;

    printf("------BUSCAR AGENTE POR NOME------\n");
    printf("Digite o nome (ou parte dele):\n");

    if (!ler_texto(nomeBusca, TAM_NOME)) {
        return;
    }

    for (i = 0; i < totalAgentes; i++) {
        if (nome_contem(i, nomeBusca)) {
            exibir_agente(i);
            achou++;
        }
    }

    if (achou == 0) {
        printf("\nNenhum agente encontrado com esse nome.\n");
        return;
    }

    printf("\nDigite o ID do agente para editar ou excluir (0 para voltar): ");
    idEscolhido = ler_opcao();

    if (idEscolhido == 0) {
        return;
    }

    pos = encontrar_posicao_por_id(idEscolhido);

    if (pos == -1 || !nome_contem(pos, nomeBusca)) {
        printf("\nID invalido para essa busca.\n");
        return;
    }

    menu_agente(pos);
}

void menu_agente(int pos) {
    int opcao;
    int ativo = 1;

    do {
        exibir_agente(pos);

        printf("\n[1] Editar\n");
        printf("[2] Excluir\n");
        printf("[3] Voltar ao menu anterior\n");
        printf("Digite a opcao desejada: ");

        opcao = ler_opcao();

        switch (opcao) {

            case 1:
                editar_agente(pos);
                break;

            case 2:
                excluir_agente(pos);
                ativo = 0;
                break;

            case 3:
                ativo = 0;
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (ativo == 1);
}

void editar_agente(int pos) {
    char novoNome[TAM_NOME + 1], novaInstrucao[TAM_INSTRUCAO + 1];
    int novaNota;

    printf("\n------EDITAR AGENTE------\n");

    do {
        printf("Digite o novo nome (ate %d caracteres):\n", TAM_NOME);
    } while (!ler_texto(novoNome, TAM_NOME));

    do {
        printf("Digite a nova instrucao (ate %d caracteres):\n", TAM_INSTRUCAO);
    } while (!ler_texto(novaInstrucao, TAM_INSTRUCAO));

    do {
        printf("Digite a nova nota (0 a 5):\n");
        novaNota = ler_opcao();

        if (novaNota < 0 || novaNota > 5) {
            printf("A nota deve ser um numero inteiro entre 0 e 5!\n");
        }
    } while (novaNota < 0 || novaNota > 5);

    copiar_texto(nomes[pos], novoNome);
    copiar_texto(instrucoes[pos], novaInstrucao);
    notas[pos] = novaNota;

    if (salvar_dados()) {
        printf("\nAgente editado com sucesso!\n");
    }
}

void excluir_agente(int pos) {
    int i, confirmar;

    printf("\n------EXCLUIR AGENTE------\n");
    printf("Tem certeza que deseja excluir o agente %s?\n", nomes[pos]);
    printf("[1] Sim\n");
    printf("[2] Nao\n");

    confirmar = ler_opcao();

    if (confirmar != 1) {
        printf("\nExclusao cancelada.\n");
        return;
    }

    for (i = pos; i < totalAgentes - 1; i++) {
        ids[i] = ids[i + 1];
        copiar_texto(nomes[i], nomes[i + 1]);
        copiar_texto(instrucoes[i], instrucoes[i + 1]);
        notas[i] = notas[i + 1];
    }

    totalAgentes--;

    if (salvar_dados()) {
        printf("\nAgente excluido com sucesso!\n");
    }
}
