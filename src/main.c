
#include <stdio.h>
#include <conio.h>

FILE *dados;
int sistemaOn = 1;

char *categorias[] = {
    "Cadastrar Agente",
    "Buscar Agentes",
    "Buscar Agente por ID",
    "Buscar Agente por nome",
    "Editar Agente",
    "Excluir Agente",
    "Sair"
};

#define MAX_CATEGORIAS (sizeof(categorias) / sizeof(categorias[0]))
#define PATH_DADOS "dados/agente.txt"

// Funcoes gerais
void iniciar_sistema(void);
void carregar_menu(void);
void apagar_console(void);
int ler_opcao(void);
int validar_scanf(char texto[]);
void pagina_continuar();

// Funcoes para o agente
// OBS: falta implementar
void cadastrar_agente(void);
void buscar_agentes(void);
void buscar_por_id(void);
void buscar_por_nome(void);
void editar_agente(void);
void excluir_agente(void);

// Funcoes de armazenamento
int iniciar_db(char path[], char mode[]);
void fechar_db(void);
int contar_linhas();

int main(void) {

    if (!iniciar_db(PATH_DADOS, "a+")) {
        return 1;
    }

    iniciar_sistema();

    fechar_db();

    return 0;
}

// Funcoes gerais
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

        for (int i = 0; i < MAX_CATEGORIAS; i++) {
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
                apagar_console();
                //editar_agente();
                break;

            case 6:
                apagar_console();
                excluir_agente();
                pagina_continuar();
                break;

            case 7:
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

int ler_opcao() {
    int opcao;

    if (scanf("%d", &opcao) == 1) {
        return opcao;
    }

    while (getchar() != '\n');

    return -1;
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

//ajustar bug do enter nao funcionar
void pagina_continuar(){
    printf("Pressione qualquer tecla para continuar...");

    _getch();

    apagar_console();
}

// Funcoes de armazenamento
int iniciar_db(char path[], char mode[]) {

    dados = fopen(path, mode);

    if (dados == NULL) {
        printf("ERRO: Nao foi possivel carregar os dados.\n");
        return 0;
    }

    return 1;
}

int inserir_db(char nome[80], char instrucao[1000], int nota) {

    if (dados == NULL || nome == NULL || instrucao == NULL) {
        return -1;
    }

    if (nota < 0 || nota > 5) {
        return -1;
    }

    int quantidade = contar_linhas();

    if (quantidade < 0) {
        return -1;
    }

    int id = quantidade;

    if (fprintf(dados, "%d;%s;%s;%d\n", id, nome, instrucao, nota) < 0) {
        return -1;
    }

    if (fflush(dados) != 0) {
        return -1;
    }

    return id;
}

void fechar_db(void) {

    if (dados != NULL) {
        fclose(dados);
        dados = NULL;
    }
}

int contar_linhas() {
    int id = 0;

    FILE *c = fopen("dados/contador.txt", "r");

    if (c != NULL) {
        fscanf(c, "%d", &id);
        fclose(c);
    }

    id++;

    c = fopen("dados/contador.txt", "w");

    if (c != NULL) {
        fprintf(c, "%d", id);
        fclose(c);
    }

    return id;
}

// Funcoes do agente
void cadastrar_agente(){
    char nome[80], instrucao[1000];
    int nota, sessao = 1, cadastro_ativo = 1;

    do {
        switch(sessao){
            case 1: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira um nome para seu novo agente:\n");
                scanf(" %79[^\n]", nome);

                if(!validar_scanf(nome)){
                    printf("Nao utilize ';' no texto!\n");
                    sessao = 1;
                    break;
                }      
                sessao++;
                break;
            }
            case 2: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira uma instrucao para seu novo agente:\n");
                scanf(" %999[^\n]", instrucao);

                if(validar_scanf(instrucao) != 1){
                    printf("Nao utilize ';' no texto!\n");
                    sessao = 2;
                    break;
                }      
                sessao++;
                break;
            }
            case 3: {
                printf("------CADASTRO DE AGENTE------\n");
                printf("Por favor insira uma nota para seu novo agente:\n");
                nota = ler_opcao();

                if(nota == -1 || nota < 0 || nota > 5){
                    sessao = 3;
                    break;
                }

                if(inserir_db(nome, instrucao, nota) == -1){
                    sessao = 3;
                    break;
                    printf("Infelizmente houve um problema ao fazer o salvamento dos dados.\n");
                }

                printf("Agente %s inserido com sucesso em nossa base de dados.\n", nome);
                sessao = 0;
                break;
            }
            default: {
                sessao = 0;
                cadastro_ativo = 0;
                pagina_continuar();
                break;
            }
        }
 
    } while(cadastro_ativo == 1);
}

void buscar_agentes(){
    char linha[1200];
    char nome[80], instrucao[1000];
    int id, nota;
    int total = 0;

    printf("------AGENTES CADASTRADOS------\n");

    // volta pro comeco do arquivo, senao a leitura pode comecar do final
    rewind(dados);

    // le o arquivo linha por linha, e para quando o arquivo acabar (NULL)
    while (fgets(linha, sizeof(linha), dados) != NULL) {
        // separa a linha em 4 partes: id, nome, instrucao e nota
        // o %[^;] significa "leia ate achar um ;"
        sscanf(linha, "%d;%79[^;];%999[^;];%d", &id, nome, instrucao, &nota);

        printf("\nID: %d\n", id);
        printf("Nome: %s\n", nome);
        printf("Instrucao: %s\n", instrucao);
        printf("Nota: %d\n", nota);
        
        // soma 1 no contador
        total++;
    }

    if (total == 0) {
        printf("\nNenhum agente cadastrado.\n");
    }
}

void buscar_por_id(){
    char linha[1200];
    char nome[80], instrucao[1000];
    int id, nota;
    int idBusca;
    int achou = 0;

    printf("------BUSCAR AGENTE POR ID------\n");
    printf("Digite o ID do agente:\n");
    idBusca = ler_opcao();

    rewind(dados);

    while (fgets(linha, sizeof(linha), dados) != NULL) {
        sscanf(linha, "%d;%79[^;];%999[^;];%d", &id, nome, instrucao, &nota);

        
        if (id == idBusca) {
            printf("\nID: %d\n", id);
            printf("Nome: %s\n", nome);
            printf("Instrucao: %s\n", instrucao);
            printf("Nota: %d\n", nota);
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("\nAgente nao encontrado.\n");
    }
}

void buscar_por_nome(){
    char linha[1200];
    char nome[80], instrucao[1000];
    // guarda o texto que o usuario digitou para procurar
    char nomeBusca[80];
    int id, nota;
    int achou = 0;
    // i anda pelas letras do nome do agente
    // j anda pelas letras do texto digitado
    int i, j;
    int encontrou;

    printf("------BUSCAR AGENTE POR NOME------\n");
    printf("Digite o nome (ou parte dele):\n");
    scanf(" %79[^\n]", nomeBusca);

    rewind(dados);

    while (fgets(linha, sizeof(linha), dados) != NULL) {
        sscanf(linha, "%d;%79[^;];%999[^;];%d", &id, nome, instrucao, &nota);

        // zera antes de testar cada agente novo
        encontrou = 0;


        // testa cada posicao do nome como possivel comeco do texto digitado
        // '\0' marca o fim do texto
        for (i = 0; nome[i] != '\0'; i++) {
            j = 0;

            // compara letra por letra, enquanto forem iguais
            // e o texto digitado nao tiver acabado
            while (nomeBusca[j] != '\0' && nome[i + j] == nomeBusca[j]) {
                j++;
            }

            
            if (nomeBusca[j] == '\0') {
                encontrou = 1;
            }
        }

        if (encontrou == 1) {
            printf("\nID: %d\n", id);
            printf("Nome: %s\n", nome);
            printf("Instrucao: %s\n", instrucao);
            printf("Nota: %d\n", nota);
            // marca que achou pelo menos um
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("\nNenhum agente encontrado com esse nome.\n");
    }
}

void excluir_agente() {
    char linha[1200];
    int id, idExcluir;
    int achou = 0;

    FILE *temp = fopen("dados/temp.txt", "w");

    printf("------EXCLUIR AGENTE------\n");
    printf("Digite o ID do agente que deseja excluir:\n");

    idExcluir = ler_opcao();

    if (idExcluir < 1 || temp == NULL) {
        printf("ID invalido ou erro ao abrir arquivo.\n");
        fclose(temp);
        return;
    }

    rewind(dados);

    while (fgets(linha, sizeof(linha), dados) != NULL) {

        sscanf(linha, "%d;", &id);

        if (id != idExcluir) {
            fprintf(temp, "%s", linha);
        } else {
            achou = 1;
        }
    }

    fclose(temp);

    if (achou == 1) {
        fclose(dados);

        remove(PATH_DADOS);
        rename("dados/temp.txt", PATH_DADOS);

        dados = fopen(PATH_DADOS, "a+");

        printf("\nAgente excluido com sucesso!\n");
    } else {
        remove("dados/temp.txt");
        printf("\nAgente nao encontrado.\n");
    }
}

// Implementacao pendente pelos integrantes
