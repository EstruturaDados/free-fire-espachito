/*

DISCIPLINA: ESTRUTURA DE DADOS (3o. Período)

DESAFIO NOVATO - TEMA 2 - JOGO FREE FIRE - CÓDIGO DA ILHA

Neste desafio, o objetivo é implementar, com o uso de estruturas de dados compostas (structs) e listas sequenciais, a
representação dos itens do inventário. Este desafio construirá um sistema de inventário que simulará a mochila de loot
inicial do jogador. Para isso, será criarada uma struct chamada Item, que armazenará informações essenciais de cada objeto
coletado. O sistema permitirá que o jogador cadastre, remova, liste e busque por itens dentro da mochila.

Autor: Elder de Souza Pachito - Matrícula: 202505123303

*/

// Inclusão das bibliotecas necessárias para a entrada, exibição de dados e operações com strings:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>   // Para adicionar o recurso de beep sonoro no programa

// Definição das constantes:
#define MAX_ITENS_ESTATICO 10
#define MAX_STRING_NOME 30
#define MAX_STRING_TIPO 20

// Criação do tipo Tipo_mochila_estatica, um vetor de structs, para armazenas os itens coletados: 
typedef struct {
    char nome_item[MAX_ITENS_ESTATICO][MAX_STRING_NOME];        // campo que armazena o nome de cada item
    char tipo_item[MAX_ITENS_ESTATICO][MAX_STRING_TIPO];        // campo que armazena o tipo de cada item
    int quantidade_item[MAX_ITENS_ESTATICO];                    // campo que armazena a quantidade de cada item
    int vagas_ocupadas;                                         // campo de controle que registra a quantidade de vagas ocupadas
} Tipo_mochila_estatica;

// Definições das funções para operações diversas na mochila estática - Implementação das mesmas após bloco main:
void inicializar_mochila_estatica(Tipo_mochila_estatica *mochila);
void inserir_item_mochila_estatica(Tipo_mochila_estatica *mochila);
void remover_item_mochila_estatica(Tipo_mochila_estatica *mochila);
void listar_mochila_estatica(Tipo_mochila_estatica *mochila);
void buscar_item_mochila_estatica(Tipo_mochila_estatica *mochila);

// Definição da função para limpar o buffer do teclado - Implementação da mesma após o bloco main:
void limpa_buffer();

// Definição da função para exibição do menu principal - Implementação da mesma após o bloco main:
void exibir_menu(Tipo_mochila_estatica *mochila);

// ================================================================================================
//
// Programa principal - Bloco main:
//
// ================================================================================================

int main() {

    // Criação da variável de controle do menu:
    int opcao_menu;

    // Criação da mochila estática:
    Tipo_mochila_estatica mochila;

    // inicializa a mochila estática:
    inicializar_mochila_estatica(&mochila);

    do {
        // Exibe o menu principal:
        exibir_menu(&mochila);

        // coleta a opção do usuário:
        printf("Escolha a sua opção entre 1 e 4 (0 para sair): ");
        scanf("%d", &opcao_menu);

        // Limpa o buffer do teclado:
        limpa_buffer();

        // Chama a função correta para cada opção escolhida:
        switch (opcao_menu) {
            case 1:
                // Chama a função para inserir um novo item na mochila estática:
                inserir_item_mochila_estatica(&mochila);
                break;
            case 2:
                // Chama a função para excluir um item da mochila estática:
                remover_item_mochila_estatica(&mochila);
                break;
            case 3:
                // Chama a função para listar os itens da mochila estática:
                listar_mochila_estatica(&mochila);
                break;
            case 4:
                // Chama a função para buscar um item na mochila estática:
                buscar_item_mochila_estatica(&mochila);
                break;
            case 0:
                printf("\nSaindo... Obrigado por jogar Free Fire!\n\n");
                break;
            default:
                printf("\nERRO! - Opção Inválida!\n\n");
                Beep(440, 500);
        }

     } while (opcao_menu != 0);
  
    return 0;
}

// Implementação da função para limpar o buffer de entrada:
void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && (c != EOF));
}

// Implementação da função inicializar_mochila_estatica() - Inicia o vetor da mochila estática, zerando a quantidade de itens:
void inicializar_mochila_estatica(Tipo_mochila_estatica *mochila) {
    mochila->vagas_ocupadas = 0;
}

// Implementação da função exbibir_menu() - Exibe o menu principal:
void exibir_menu(Tipo_mochila_estatica *mochila) {
    printf("\n\n==================== MENU PRINCIPAL =====================\n");
    printf("Ocupação da Mochila: %2d Itens / %d Vagas\n\n", mochila->vagas_ocupadas, MAX_ITENS_ESTATICO - mochila->vagas_ocupadas);
    printf("   1 - Inserir item na mochila\n");
    printf("   2 - Remover item da mochila\n");
    printf("   3 - Listar itens armazenados na mochila\n");
    printf("   4 - Buscar item na mochila\n");
    printf("   0 - Sair\n");
    printf("=========================================================\n");
}

// Implementação da função inserir_item_mochila_estatica() - Insere um item na mochila estática:
void inserir_item_mochila_estatica(Tipo_mochila_estatica *mochila) {

    // Verifica se a quantidade máxima de itens já foi alcançada (mochila cheia):
    if (mochila->vagas_ocupadas == MAX_ITENS_ESTATICO) {
        // No caso da mochila estar cheia, exibir mensagem de erro e retornar:
        printf("\nERRO! - Mochila cheia! Não é possível inserir itens novos.\n\n");
        Beep(440, 500);
        return;
    } else {
        // No caso de ainda existir vagas na mochila, solicitar os dados do nome item e o inserir:
        printf("\nEntre com o nome do item a ser inserido: ");
        fgets(mochila->nome_item[mochila->vagas_ocupadas], MAX_STRING_NOME, stdin);
        printf("Entre com o tipo do item (arma, munição ou cura): ");
        fgets(mochila->tipo_item[mochila->vagas_ocupadas], MAX_STRING_TIPO, stdin);

        mochila->nome_item[mochila->vagas_ocupadas][strcspn(mochila->nome_item[mochila->vagas_ocupadas], "\n")] = '\0';
        mochila->tipo_item[mochila->vagas_ocupadas][strcspn(mochila->tipo_item[mochila->vagas_ocupadas], "\n")] = '\0';

        printf("Entre com a quantidade desse item: ");
        scanf("%d", &mochila->quantidade_item[mochila->vagas_ocupadas]);

        // Incrementar a quantidade de vagas ocupadas em 1 unidade:
        mochila->vagas_ocupadas++;

        // Limpa o buffer do teclado:
        limpa_buffer();

        return;
    }
}

// Implementação da função remover_item_mochila_estatica() - Remove um item da mochila:
void remover_item_mochila_estatica(Tipo_mochila_estatica *mochila) {

    // Cria variável local para armazenar o nome do item que o usuário deseja remover:
    char nome_item_a_ser_removido[MAX_STRING_NOME];

    // Cria as variáveis locais para identificar a posição de varredura na mochila e se o item foi ou nao encontrado:
    int pos;
    int achou;

    // Verifica se existem itens na mochila:
    if (mochila->vagas_ocupadas > 0) {
        // Se a mochila não estiver vazia, solicita o nome do item a ser removido:
        printf("\nEntre com o nome do item a ser removido: ");
        fgets(nome_item_a_ser_removido, MAX_STRING_NOME, stdin);

        nome_item_a_ser_removido[strcspn(nome_item_a_ser_removido, "\n")] = '\0';

        // Percorre a mochila procurando pelo item que o usuário informou:

        pos = 0;     // inicializa a posição de procura para índice 0 da mochila:
        achou = 0;   // inicializa a variável de controle da busca para o status de ainda não encontrado

        do {
            // verifica se o item corrente é o item procurado:
            if (strcmp(mochila->nome_item[pos], nome_item_a_ser_removido) == 0) {
                // Achou um item que coincide exatamente com o nome procurado pelo usuário:
                achou = 1;
            }
            pos++;
        } while ((pos < mochila->vagas_ocupadas) && (achou == 0));

        // Se a busca encontrou:
        if (achou == 1) {
            // Realiza procedimentos para remover o item e arrumar a mochila:

            for (int i = pos; i < mochila->vagas_ocupadas; i++) {
                // Realoca os itens seguintes, após a posição do item encontrado, para arrumar mochila:
                strcpy(mochila->nome_item[i - 1], mochila->nome_item[i]);
                strcpy(mochila->tipo_item[i - 1], mochila->tipo_item[i]);
                mochila->quantidade_item[i - 1] = mochila->quantidade_item[i];
            }

            // Reduz a quantidade de posições ocupadas na mochila em 1 unidade:
            mochila->vagas_ocupadas--;

            // Exibe a mensagem de remoção efetuada:
            printf("\nItem %s removido com sucesso!\n", nome_item_a_ser_removido);
            return;

        } else {
            // Alerta que o item não foi encontrado:
            printf("\nO item %s não foi encontrado na mochila!\n\n", nome_item_a_ser_removido);
            Beep(440, 500);
            return;
        }

        // Limpa o buffer do teclado:
        limpa_buffer();

    } else {
        // Exibe mensagem se a mochila estiver vazia:
        printf("\nA mochila está vazia!\n");
        Beep(440, 500);
        return;
    }

}

// Implementação da função listar_mochila_estatica() - Exibe a lista de itens armazenados na mochila estática:
void listar_mochila_estatica(Tipo_mochila_estatica *mochila) {
    // Cria variáveis locais auxiliares para formatar os textos de saída:
    char txt_nome[MAX_STRING_NOME*2];
    char txt_tipo[MAX_STRING_TIPO*2];

    // Verifica se existem itens na mochila:
    if (mochila->vagas_ocupadas > 0) {
        // Se a mochila não estiver vazia, exibe cabeçalho e continua:
        printf("\nNOME DO ITEM                    TIPO DE ITEM:         QTD\n");
        printf("==============================  ====================  ===\n"); 
        for (int i = 0; i < mochila->vagas_ocupadas; i++) {
            // carrega os dados do tipo texto para formatá-los em variáveis locais:
            strcpy(txt_nome, mochila->nome_item[i]);
            strncat(txt_nome, "                              ", MAX_STRING_NOME - 1);
            txt_nome[MAX_STRING_NOME] = '\0';
            strcpy(txt_tipo, mochila->tipo_item[i]);
            strncat(txt_tipo, "                    ", MAX_STRING_TIPO - 1);
            txt_tipo[MAX_STRING_TIPO] = '\0';

            // Exibe a listagem dos itens:
            printf("%s  %s  %3d\n", txt_nome, txt_tipo, mochila->quantidade_item[i]);
        }
    } else {
        // Exibe mensagem se a mochila estiver vazia:
        printf("\nA mochila está vazia!\n");
        Beep(440, 500);
        return;
    }
}

// Implementação da função buscar_item_mochila() - Busca um item na mochila:
void buscar_item_mochila_estatica(Tipo_mochila_estatica *mochila) {

    // Cria variável local para armazenar o nome do item que o usuário deseja encontrar:
    char nome_item_procurado[MAX_STRING_NOME];

    // Cria as variáveis locais para identificar a posição de varredura na mochila e se o item foi ou nao encontrado:
    int pos;
    int achou;

    // Cria variáveis locais auxiliares para formatar os textos de saída:
    char txt_nome[MAX_STRING_NOME*2];
    char txt_tipo[MAX_STRING_TIPO*2];

    // Verifica se existem itens na mochila:
    if (mochila->vagas_ocupadas > 0) {
        // Se a mochila não estiver vazia, solicita o nome do item procurado:
        printf("\nEntre com o nome do item a ser procurado: ");
        fgets(nome_item_procurado, MAX_STRING_NOME, stdin);

        nome_item_procurado[strcspn(nome_item_procurado, "\n")] = '\0';

        // Percorre a mochila procurando pelo item que o usuário informou:

        pos = 0;     // inicializa a posição de procura para índice 0 da mochila:
        achou = 0;   // inicializa a variável de controle da busca para o status de ainda não encontrado

        do {
            // verifica se o item corrente é o item procurado:
            if (strcmp(mochila->nome_item[pos], nome_item_procurado) == 0) {
                // Achou um item que coincide exatamente com o nome procurado pelo usuário:
                achou = 1;
            }
            pos++;
        } while ((pos < mochila->vagas_ocupadas) && (achou == 0));

        // Se a busca encontrou:
        if (achou == 1) {

            // Limpa o buffer do teclado:
            // limpa_buffer();

            // Realiza procedimentos para exibir o item para o usuário:
            printf("\nNOME DO ITEM                    TIPO DE ITEM:         QTD\n");
            printf("==============================  ====================  ===\n"); 
            
            // carrega os dados do tipo texto para formatá-los em variáveis locais:
            strcpy(txt_nome, mochila->nome_item[pos - 1]);
            strncat(txt_nome, "                              ", MAX_STRING_NOME - 1);
            txt_nome[MAX_STRING_NOME] = '\0';
            strcpy(txt_tipo, mochila->tipo_item[pos - 1]);
            strncat(txt_tipo, "                    ", MAX_STRING_TIPO - 1);
            txt_tipo[MAX_STRING_TIPO] = '\0';
            
            // Exibe o item:
            printf("%s  %s  %3d\n", txt_nome, txt_tipo, mochila->quantidade_item[pos - 1]);

        } else {
            // Alerta que o item não foi encontrado:
            printf("\nO item %s não foi encontrado na mochila!\n", nome_item_procurado);
            Beep(440, 500);
            return;
        }

    } else {
        // Exibe mensagem se a mochila estiver vazia:
        printf("\nA mochila está vazia!\n");
        Beep(440, 500);
        return;
    }
}
