/*

DISCIPLINA: ESTRUTURA DE DADOS (3o. Período)

DESAFIO MESTRE - TEMA 2 - JOGO FREE FIRE - CÓDIGO DA ILHA

Neste desafio, o código deverá implementar diferentes algoritmos de ordenação, analisar seu desempenho, aplicar uma busca
binária otimizada e permitir ao jogador decidir qual estratégia usar com base nas condições de jogo. Esta fase integra e
consolida os conhecimentos de ordenação, busca eficiente e modularização. 

Autor: Elder de Souza Pachito - Matrícula: 202505123303

Data: 31/07/2026

*/

// Inclusão das bibliotecas necessárias para a entrada, exibição de dados e operações com strings:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>      // Para adicionar funções relacionadas com tempo e cronômetro
#include <windows.h>   // Para adicionar o recurso de beep sonoro no programa

// Definição das constantes:
#define MAX_ITENS_ESTATICO 20
#define MAX_STRING_NOME 30
#define MAX_STRING_TIPO 20

// Criação do tipo Tipo_mochila_estatica, um vetor de structs, para armazenas os itens coletados: 
typedef struct {
    char nome_item[MAX_ITENS_ESTATICO][MAX_STRING_NOME];        // campo que armazena o nome de cada item
    char tipo_item[MAX_ITENS_ESTATICO][MAX_STRING_TIPO];        // campo que armazena o tipo de cada item
    int prioridade_item[MAX_ITENS_ESTATICO];                    // campo que armazena a prioridade de cada item
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

// Definição das funções para exibição dos menus - Implementação das mesmas após o bloco main:
void exibir_menu(Tipo_mochila_estatica *mochila);
void exibir_menu_ordenacao();

// Define uma estrutura auxiliar para armazenar os dados de um item da mochila:
struct item {
    char nome_item[MAX_STRING_NOME];        // campo que armazena temporariamente o nome de um item
    char tipo_item[MAX_STRING_TIPO];        // campo que armazena temporariamente o tipo de um item
    int prioridade_item;                    // campo que armazena temporariamente a prioridade de um item
};

// Definição da função de troca de posição entre dois itens:
void trocar_itens_de_posicao(Tipo_mochila_estatica *mochila, int indice_1, int indice_2);

// Definição das funções de ordenação da mochila - Implementação das mesmas após o bloco main:
void ordenar_por_nome(Tipo_mochila_estatica *mochila);
void ordenar_por_tipo(Tipo_mochila_estatica *mochila);
void ordenar_por_prioridade(Tipo_mochila_estatica *mochila);

// ================================================================================================
//
// Programa principal - Bloco main:
//
// ================================================================================================

int main() {

    // Criação da variável de controle do menu e de controle da ordenação por nome:
    int opcao_menu, opcao_menu_ordenacao;
    int ordenado_por_nome = 0;

    // Criação da mochila estática:
    Tipo_mochila_estatica mochila;

    // inicializa a mochila estática:
    inicializar_mochila_estatica(&mochila);

    // *********************
    // ********************* ALIMENTAÇÃO TEMPORÁRIA DE DADOS DURANTE OS TESTES **********************
    // *********************

    /*
    strcpy(mochila.nome_item[0], "viga de aco");
    strcpy(mochila.tipo_item[0], "estrutural");
    mochila.prioridade_item[0] = 4;
    strcpy(mochila.nome_item[1], "bateria");
    strcpy(mochila.tipo_item[1], "energia");
    mochila.prioridade_item[1] = 3;
    strcpy(mochila.nome_item[2], "antena");
    strcpy(mochila.tipo_item[2], "eletronico");
    mochila.prioridade_item[2] = 5;
    strcpy(mochila.nome_item[3], "placa mae");
    strcpy(mochila.tipo_item[3], "eletronico");
    mochila.prioridade_item[3] = 6;
    strcpy(mochila.nome_item[4], "parafuso");
    strcpy(mochila.tipo_item[4], "estrutural");
    mochila.prioridade_item[4] = 4;
    strcpy(mochila.nome_item[5], "painel solar");
    strcpy(mochila.tipo_item[5], "energia");
    mochila.prioridade_item[5] = 7;
    strcpy(mochila.nome_item[6], "quadro de forca");
    strcpy(mochila.tipo_item[6], "energia");
    mochila.prioridade_item[6] = 6;
    strcpy(mochila.nome_item[7], "pilar de aco");
    strcpy(mochila.tipo_item[7], "estrutural");
    mochila.prioridade_item[7] = 8;

    mochila.vagas_ocupadas = 8;
    */

    // Inicializa a váriável de controle de ordenação por nome, assumindo que os itens ainda não estejam nessa ordem:
    ordenado_por_nome = 0;

    do {
        // Exibe o menu principal:
        exibir_menu(&mochila);

        // coleta a opção do usuário:
        printf("Escolha a sua opção entre 1 e 5 (0 para sair): ");
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
                if (mochila.vagas_ocupadas == 0) {
                    printf("\nA mochila está vazia!\n");
                    Beep(440, 500);
                    break;
                }
                do {
                    // Chama a função para organizar a mochila (ordenar os itens):
                    // Exibe menu de ordenação:
                    exibir_menu_ordenacao();

                    // Coleta a opção do usuário:
                    printf("Escolha a sua opção entre 1 e 3 (0 para voltar): ");
                    scanf("%d", &opcao_menu_ordenacao);

                    // Limpa o buffer do teclado:
                    limpa_buffer();

                    // Executa a ordenação correta conforme a opção escolhida pelo usuário:
                    switch (opcao_menu_ordenacao) {
                        case 1:
                            // Chama a função ordenar por nome, utilizando o método Bubble Sort:
                            ordenar_por_nome(&mochila);
                            // A ordenação por nome passa a ver verdadeira:
                            ordenado_por_nome = 1;
                            break;
                        case 2:
                            // A ordenação por nome não é mais a corrente ordenação:
                            ordenado_por_nome = 0;
                            // Chama a função para ordenar por tipo:
                            ordenar_por_tipo(&mochila);
                            break;
                        case 3:
                            // A ordenação por nome não é mais a corrente ordenação:
                            ordenado_por_nome = 0;
                            // Chama a função para ordenar por prioridade (decrescente):
                            ordenar_por_prioridade(&mochila);
                            break;
                        case 0:
                            printf("\nVoltando ao menu anterior...\n");
                            break;
                        default:
                            printf("\nERRO! - Opção Inválida!\n");
                            Beep(440, 500);
                    }
                } while (opcao_menu_ordenacao != 0);
                break;
            case 5:
                // Chama a função para realizar busca binária por nome, caso os itens estejam ordenados por nome:
                if (ordenado_por_nome) {
                    // Chama a função para realizar a busca binária por um item:
                    buscar_item_mochila_estatica(&mochila);
                } else {
                    // Exibe mensagem que primeiro é necessária a ordenação por nome:
                    printf("\nVocê primeiro deve realizar uma ordenação dos itens por NOME!\n");
                    Beep(440, 500);
                }
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
    printf("   3 - Listar itens armazenados (inventário)\n");
    printf("   4 - Organizar a mochila (ordenar os itens)\n");
    printf("   5 - Realizar busca binária por nome\n");
    printf("   0 - Sair\n");
    printf("=========================================================\n");
}

// Implementação da função exbibir_menu_ordenacao() - Exibe o menu de ordenacao:
void exibir_menu_ordenacao() {
    printf("\n\n=================== MENU DE ORDENAÇÃO =================\n");
    printf("   1 - Ordenar por nome do item (Bubble Sort)\n");
    printf("   2 - Ordenar por tipo do item (Insertion Sort)\n");
    printf("   3 - Ordenar por prioridade (Selection Sort)\n");
    printf("   0 - Voltar ao menu anterior\n");
    printf("=========================================================\n");
}

// Implementação da função inserir_item_mochila_estatica() - Insere um item na mochila estática:
void inserir_item_mochila_estatica(Tipo_mochila_estatica *mochila) {
    // Cria variável auxiliar para coletar a prioridade do usuário:
    int prioridade_aux;

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
        printf("Entre com o tipo do item (estrutural, energia, acionador, eletrônico, etc.): ");
        fgets(mochila->tipo_item[mochila->vagas_ocupadas], MAX_STRING_TIPO, stdin);

        mochila->nome_item[mochila->vagas_ocupadas][strcspn(mochila->nome_item[mochila->vagas_ocupadas], "\n")] = '\0';
        mochila->tipo_item[mochila->vagas_ocupadas][strcspn(mochila->tipo_item[mochila->vagas_ocupadas], "\n")] = '\0';

        // Coleta o valor da prioridade, até que o mesmo seja válido:
        prioridade_aux = 0;
        while ((prioridade_aux <= 0) || (prioridade_aux > 10)) {
            printf("Entre com a prioridade desse item (entre 1 e 10): ");
            scanf("%d", &prioridade_aux);
            if ((prioridade_aux <=0) || (prioridade_aux > 10)) limpa_buffer();
        }
        mochila->prioridade_item[mochila->vagas_ocupadas] = prioridade_aux;

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
                mochila->prioridade_item[i - 1] = mochila->prioridade_item[i];
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
        printf("\nNOME DO ITEM                    TIPO DE ITEM          PRI\n");
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
            printf("%s  %s  %3d\n", txt_nome, txt_tipo, mochila->prioridade_item[i]);
        }
    } else {
        // Exibe mensagem se a mochila estiver vazia:
        printf("\nA mochila está vazia!\n");
        Beep(440, 500);
        return;
    }
}

// Implementação da função buscar_item_mochila() - Busca BINÁRIA um item na mochila:
void buscar_item_mochila_estatica(Tipo_mochila_estatica *mochila) {

    // Cria variável local para armazenar o nome do item que o usuário deseja encontrar:
    char nome_item_procurado[MAX_STRING_NOME];

    // Cria as variáveis locais para identificar o bloco de varredura na mochila e se o item foi ou nao encontrado:
    int pos_inicio, pos_fim, pos_meio;
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

        // Utiliza o método de busca binária para tentar localizar o item procurado pelo usuário:
        pos_inicio = 0;
        pos_fim = mochila->vagas_ocupadas - 1;

        // Inicializa a variável 'achou' com 0, ou seja, ainda não achou o item procurado:
        achou = 0;

        // Inicia a busca binária:
        while (pos_inicio <= pos_fim) {
            pos_meio = (pos_inicio + pos_fim) / 2;
            if (strcmp(mochila->nome_item[pos_meio], nome_item_procurado) == 0) {
                // Registra na variável 'achou' o valor 1, para indicar que o item procurado foi encontrado:
                achou = 1;
                break;
            }
        else if (strcmp(mochila->nome_item[pos_meio], nome_item_procurado) < 0)
                pos_inicio = pos_meio + 1;
            else
                pos_fim = pos_meio - 1;
        }

        // Se a busca encontrou:
        if (achou == 1) {
            // Realiza procedimentos para exibir o item para o usuário:
            printf("\nNOME DO ITEM                    TIPO DE ITEM          PRI\n");
            printf("==============================  ====================  ===\n"); 
            
            // carrega os dados do tipo texto para formatá-los em variáveis locais:
            strcpy(txt_nome, mochila->nome_item[pos_meio]);
            strncat(txt_nome, "                              ", MAX_STRING_NOME - 1);
            txt_nome[MAX_STRING_NOME] = '\0';
            strcpy(txt_tipo, mochila->tipo_item[pos_meio]);
            strncat(txt_tipo, "                    ", MAX_STRING_TIPO - 1);
            txt_tipo[MAX_STRING_TIPO] = '\0';
            
            // Exibe o item:
            printf("%s  %s  %3d\n", txt_nome, txt_tipo, mochila->prioridade_item[pos_meio]);

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

// Implementação da função para troca da posição entre dois itens, índices indice_1 e indice_2:
void trocar_itens_de_posicao(Tipo_mochila_estatica *mochila, int indice_1, int indice_2) {
    // Cria variável auxiliar para armazenar os dados de um dos itens:
    struct item item_aux;

    // Armazena os dados de um dos itens:
    strcpy(item_aux.nome_item, mochila->nome_item[indice_1]);
    strcpy(item_aux.tipo_item, mochila->tipo_item[indice_1]);
    item_aux.prioridade_item = mochila->prioridade_item[indice_1];

    // Substitui os dados do item com indice_1 com os dados do item com indice_2:
    strcpy(mochila->nome_item[indice_1], mochila->nome_item[indice_2]);
    strcpy(mochila->tipo_item[indice_1], mochila->tipo_item[indice_2]);
    mochila->prioridade_item[indice_1] = mochila->prioridade_item[indice_2];

    // Recupera os dados armazenados na variável auxiliar item_aux para o item com indice_2:
    strcpy(mochila->nome_item[indice_2], item_aux.nome_item);
    strcpy(mochila->tipo_item[indice_2], item_aux.tipo_item);
    mochila->prioridade_item[indice_2] = item_aux.prioridade_item;
}

// Implementação da função de ordenar_por_nome() - Método: Bubble Sort:
void ordenar_por_nome(Tipo_mochila_estatica *mochila) {
    // Cria varíaveis para contagem da quantidade de comparações e tempo de processamento:
    int qtde_comparacoes = 0;
    clock_t cronometro_start, cronometro_end;
    double tempo_processamento;

    printf("\n**** ORDENAÇÃO POR NOME - MÉTODO BUBBLE SORT:\n");
    cronometro_start = clock();             // Inicia o temporizador
    for (int i = 0; i < mochila->vagas_ocupadas - 1; i++) {
        for (int j = 0; j < mochila->vagas_ocupadas - 1 - i; j++) {
            qtde_comparacoes++;             // Incrementa a contagem de comparações em 1 unidade
            if (strcmp(mochila->nome_item[j], mochila->nome_item[j + 1]) > 0) {
                trocar_itens_de_posicao(mochila, j, j + 1);
            }
        }
    }
    cronometro_end = clock();               // Finaliza o temporizador
    tempo_processamento = (double)(cronometro_end - cronometro_start) / CLOCKS_PER_SEC;  // Calcula o tempo decorrido

    // Exibe a lista ordenada e os cálculos de tempo e esforço:
    listar_mochila_estatica(mochila);
    printf("\nQUANTIDADE DE COMPARAÇÕES = %d", qtde_comparacoes);
    printf("\nTEMPO GASTO = %.8f segundos\n", tempo_processamento);
}

// Implementação da função ordenar_por_tipo() - Método: Insertion Sort:
void ordenar_por_tipo(Tipo_mochila_estatica *mochila) {
    // Cria variável temporária para guardar os dados de um item:
    struct item item_aux;

    // Cria varíaveis para contagem da quantidade de comparações e tempo de processamento:
    int qtde_comparacoes = 0;
    clock_t cronometro_start, cronometro_end;
    double tempo_processamento;

    printf("\n**** ORDENAÇÃO POR TIPO - MÉTODO INSERTION SORT:\n");
    cronometro_start = clock();             // Inicia o temporizador
    for (int i = 1; i < mochila->vagas_ocupadas; i++) {
        // Salva os dados do item de índice 'i' na variável auxiliar:
        strcpy(item_aux.nome_item, mochila->nome_item[i]);
        strcpy(item_aux.tipo_item, mochila->tipo_item[i]);
        item_aux.prioridade_item = mochila->prioridade_item[i];

        // Inicializa a variável de percorrimento das comparações para a posição anterior a 'i':
        int j = i - 1;

        // Move os elementos maiores que a chave uma posição à frente
        while ((j >= 0) && (strcmp(mochila->tipo_item[j], item_aux.tipo_item) > 0)) {
            // Incrementa a quantidade de comparações em mais 1 unidade:
            qtde_comparacoes++;
            // Move o item com índice 'j' uma posição para frente (j + 1):
            strcpy(mochila->nome_item[j + 1], mochila->nome_item[j]);
            strcpy(mochila->tipo_item[j + 1], mochila->tipo_item[j]);
            mochila->prioridade_item[j + 1] = mochila->prioridade_item[j];
            // Decrementa a variável de percorrimento das comparações:
            j--;
        }

        // Insere o item na posição correta:
        strcpy(mochila->nome_item[j + 1], item_aux.nome_item);
        strcpy(mochila->tipo_item[j + 1], item_aux.tipo_item);
        mochila->prioridade_item[j + 1] = item_aux.prioridade_item;
    }
    cronometro_end = clock();               // Finaliza o temporizador
    tempo_processamento = (double)(cronometro_end - cronometro_start) / CLOCKS_PER_SEC;  // Calcula o tempo decorrido

    // Exibe a lista ordenada e os cálculos de tempo e esforço:
    listar_mochila_estatica(mochila);
    printf("\nQUANTIDADE DE COMPARAÇÕES = %d", qtde_comparacoes);
    printf("\nTEMPO GASTO = %.8f segundos\n", tempo_processamento);
}

// Implementação da função ordenar_por_prioridade() - Método Selection Sort (OBS: ordem decrescente):
void ordenar_por_prioridade(Tipo_mochila_estatica *mochila) {
    // Cria variável local de controle do índice do maior valor encontrado:
    int indice_maior;

    // Cria varíaveis para contagem da quantidade de comparações e tempo de processamento:
    int qtde_comparacoes = 0;
    clock_t cronometro_start, cronometro_end;
    double tempo_processamento;

    printf("\n**** ORDENAÇÃO POR PRIORIDADE - MÉTODO SELECTION SORT:\n");
    cronometro_start = clock();             // Inicia o temporizador
    for (int i = 0; i < (mochila->vagas_ocupadas - 1); i++) {
        indice_maior = i;
        for (int j = (i + 1); j < mochila->vagas_ocupadas; j++) {
            // Incrementa a quantidade de comparações em 1 unidade:
            qtde_comparacoes++;
            // Encontra o maior valor de prioridade dentre os itens restantes:
            if (mochila->prioridade_item[j] > mochila->prioridade_item[indice_maior]) {
                indice_maior = j;
            }
        }
        if (indice_maior != i) {
            trocar_itens_de_posicao(mochila, i, indice_maior);
        }
    }
    cronometro_end = clock();               // Finaliza o temporizador
    tempo_processamento = (double)(cronometro_end - cronometro_start) / CLOCKS_PER_SEC;  // Calcula o tempo decorrido

    // Exibe a lista ordenada e os cálculos de tempo e esforço:
    listar_mochila_estatica(mochila);
    printf("\nQUANTIDADE DE COMPARAÇÕES = %d", qtde_comparacoes);
    printf("\nTEMPO GASTO = %.8f segundos\n", tempo_processamento);
}
