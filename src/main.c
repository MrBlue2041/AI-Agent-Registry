
#include <stdio.h>

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

// Funcoes gerais
void iniciar_sistema(void);
void carregar_menu(void);
void apagar_console(void);
int ler_opcao(void);

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

int main(void) {

    if (!iniciar_db("dados/agente.txt", "a+")) {
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
                //cadastrar_agente();
                break;

            case 2:
                apagar_console();
                //buscar_agentes();
                break;

            case 3:
                apagar_console();
                //buscar_por_id();
                break;

            case 4:
                apagar_console();
                //buscar_por_nome();
                break;

            case 5:
                apagar_console();
                //editar_agente();
                break;

            case 6:
                apagar_console();
                //excluir_agente();
                break;

            case 7:
                apagar_console();
                menuOn = 0;
                sistemaOn = 0;
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

// Funcoes de armazenamento
int iniciar_db(char path[], char mode[]) {

    dados = fopen(path, mode);

    if (dados == NULL) {
        printf("ERRO: Nao foi possivel carregar os dados.\n");
        return 0;
    }

    return 1;
}

void fechar_db(void) {

    if (dados != NULL) {
        fclose(dados);
        dados = NULL;
    }
}

// Funcoes do agente
// Implementacao pendente pelos integrantes
