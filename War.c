/*

DISCIPLINA: ESTRUTURA DE DADOS (3o. Período)

DESAFIO MESTRE - TEMA 1 - JOGO WAR

Neste desafio, o objetivo é implementar a funcionalidade de missões estratégicas individuais para cada jogador, que
deverá receber, no início do jogo, uma missão sorteada de forma automática entre diversas descrições pré-definidas,
armazenadas em um vetor de strings. Essa missão será consultada durante o jogo para verificar se a condição de vitória
foi atingida. A nova camada de estratégia exige organização modular do código, uso de ponteiros, passagem de parâmetros
por valor e referência e gerenciamento adequado da memória.

Autor: Elder de Souza Pachito - Matrícula: 202505123303

*/

// Inclusão da biblioteca necessária para a entrada e exibição de dados:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição das constantes:
#define MAX_TERRITORIOS 50
#define MAX_STRING1 30   // Tamanho máximo da string para nome de território
#define MAX_STRING2 10   // Tamanho máximo da string para nome de cor
#define MAX_STRING3 100  // Tamanho máximo da string para nome de missão
#define MAX_MISSOES 3

// Cria as variáveis globais de controle de vitória do atacante:
int atacante_venceu;
int atacante_venceu_ao_menos_1 = 0;

// Definição do tipo Tipo_territorio:
typedef struct {
    char nome[MAX_STRING1];
    char cor[MAX_STRING2];
    int qtde_tropas;
} Tipo_territorio;

// Definição do tipo Tipo_missao:
typedef struct {
    char missao[MAX_STRING3];
} Tipo_missao;

// Cria o ponteiro global do tipo Tipo_territorio:
Tipo_territorio *territorios;

// Cria função para sortear uma missão:
int sorteia_missao() {
    // Inicializa a semente do gerador
    srand(time(NULL));
    // retorna o idice do vetor de missões que foi sorteado:
    return (rand() % MAX_MISSOES);
}

// Cria função para limpar o buffer de entrada:
void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && (c != EOF));
}

// Cria função para cadastrar os territórios:
void cadastra_territorios(int qtde) {
    for (int i = 0; i < qtde; i++) {
        printf("\n");

        printf("Entre com o NOME do território %d: ", i + 1);
        fgets(territorios[i].nome, MAX_STRING1, stdin);
        printf("Entre com a COR do território %d: ", i + 1);
        fgets(territorios[i].cor, MAX_STRING2, stdin);
        
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        printf("Entre com a QUANTIDADE DE TROPAS do território %d: ", i + 1);
        scanf("%d", &territorios[i].qtde_tropas);

        // limpa o buffer do teclado:
        limpa_buffer();
    }
}

// Cria função para exibir a situação atual dos territórios:
void exibe_territorios(Tipo_territorio *vetor_territorios, int qtde) {
    printf("\n");
    for (int i = 0; i < qtde; i++) {
            printf("TERRITÓRIO %2d: %s (Cor: %s, Qtde Tropas: %d)\n", i + 1, vetor_territorios[i].nome, vetor_territorios[i].cor, vetor_territorios[i].qtde_tropas);
         }
}

// Cria função de ataque por simulção de lançamento de dados para os territórios solicitados pelo usuário:
void ataque(int indice_atacante, int indice_defensor) {
    // Inicializa a semente do gerador
    srand(time(NULL));

    // Simula o lançamento de um dado para o território ATACANTE:
    int resultado_atacante = (rand() % 6) + 1;

    // Simula o lançamento de um dado para o território DEFENSOR:
    int resultado_defensor = (rand() % 6) + 1;

    // Compara os resultados:
    if (resultado_atacante == resultado_defensor) {
        // Em caso de empate, mensagem é enviada para o terminal e nada muda nos territórios:
        printf("EMPATE NA BATALHA! Nada muda no tabuleiro:\n");
        printf("   >>>  Dado do ATACANTE (%s): %d  x  Dado do DEFENSOR (%s): %d\n", territorios[indice_atacante].nome, resultado_atacante, territorios[indice_defensor].nome, resultado_defensor);
        return;
    } else if (resultado_atacante > resultado_defensor) {
        // Em caso do ATACANTE ganhar:
        atacante_venceu = 1;   // registra que o atacante venceu a batalha em curso
        // Exibe resultado para o usuário:
        printf("Território ATACANTE (%s) VENCEU:\n", territorios[indice_atacante].nome);
        printf("   >>>  Dado do ATACANTE (%s): %d  x  Dado do DEFENSOR (%s): %d\n", territorios[indice_atacante].nome, resultado_atacante, territorios[indice_defensor].nome, resultado_defensor);
        // Uma unidade da tropa do território perdedor (DEFENSOR) será eliminada:
        territorios[indice_defensor].qtde_tropas = territorios[indice_defensor].qtde_tropas - 1;
        // Caso todas as tropas do DEFENSOR sejam dizimadas com este ataque, a cor do seu território será alterada para a
        // mesma cor do território vencedor (ATACANTE), e sua quantidade de tropas receberá metade da quantidade de tropas do vencedor:
        if (territorios[indice_defensor].qtde_tropas <= 0) {
            strcpy(territorios[indice_defensor].cor, territorios[indice_atacante].cor);
            territorios[indice_defensor].qtde_tropas = (territorios[indice_atacante].qtde_tropas / 2);
            territorios[indice_atacante].qtde_tropas = territorios[indice_atacante].qtde_tropas - (territorios[indice_atacante].qtde_tropas / 2);
            printf("   >>>  O território vencedor (%s) ASSUMIU o controle do território derrotado (%s)\n", territorios[indice_atacante].nome, territorios[indice_defensor].nome);
        }
        return;
    } else {
        // Em caso do DEFENSOR ganhar:
        atacante_venceu = 0;   // registra que o atacante NÃO venceu a batalha em curso
        // Exibe resultado para o usuário:
        printf("Território DEFENSOR (%s) VENCEU:\n", territorios[indice_defensor].nome);
        printf("   >>>  Dado do ATACANTE (%s): %d  x  Dado do DEFENSOR (%s): %d\n", territorios[indice_atacante].nome, resultado_atacante, territorios[indice_defensor].nome, resultado_defensor);
        // Uma unidade da tropa do território perdedor (ATACANTE) será eliminada:
        territorios[indice_atacante].qtde_tropas = territorios[indice_atacante].qtde_tropas - 1;
        // Caso todas as tropas do ATACANTE sejam dizimadas com este ataque, a cor do seu território será alterada para a
        // mesma cor do território vencedor (DEFENSOR), e sua quantidade de tropas receberá metade da quantidade de tropas do vencedor:
        if (territorios[indice_atacante].qtde_tropas <= 0) {
            strcpy(territorios[indice_atacante].cor, territorios[indice_defensor].cor);
            territorios[indice_atacante].qtde_tropas = (territorios[indice_defensor].qtde_tropas / 2);
            territorios[indice_defensor].qtde_tropas = territorios[indice_defensor].qtde_tropas - (territorios[indice_defensor].qtde_tropas / 2);
            printf("   >>>  O território vencedor (%s) ASSUMIU o controle do território derrotado (%s)\n", territorios[indice_defensor].nome, territorios[indice_atacante].nome);
        }
        return;
    }
}

// Cria função para verificar se a missão sorteada foi cumprida:
void verifica_missao(Tipo_missao *vetor_missoes, int id_missao, int atacante) {
    int j, territorios_dominados;
    switch (id_missao) {
        case 0:
            // Percorre o vetor de território verificando os territórios que cumpriram a missão:
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
                j = 0;
                territorios_dominados = 0;
                do {
                    if (strcmp(territorios[i].cor, territorios[j].cor) == 0) {
                        territorios_dominados++;
                    }
                    j++;
                } while ((j < MAX_TERRITORIOS) && (territorios_dominados < 3));

                // Exibe mensagem que um território cumpriu a missão:
                if ((territorios_dominados > 2) && (i == atacante)) {
                    printf("\n=== ATENÇÃO!!! - Território %s CUMPRIU A MISSÃO: %s\n", territorios[i].nome, vetor_missoes[id_missao].missao);
                }
            }
            break;
        case 1:
            // Percorre o vetor de território verificando os territórios que cumpriram a missão:
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
                j = 0;
                territorios_dominados = 0;
                do {
                    if (strcmp(territorios[i].cor, territorios[j].cor) == 0) {
                        territorios_dominados++;
                    }
                    j++;
                } while ((j < MAX_TERRITORIOS) && (territorios_dominados < 2));

                // Exibe mensagem que um território cumpriu a missão:
                if ((territorios_dominados > 1) && (i == atacante)) {
                    printf("\n=== ATENÇÃO!!! - Território %s CUMPRIU A MISSÃO: %s\n", territorios[i].nome, vetor_missoes[id_missao].missao);
                }
            }
            break;
        case 2:
            // Verifica se a o atacante venceu aos menos uma batalha:
            if ((atacante_venceu) || (atacante_venceu_ao_menos_1)) {
                atacante_venceu_ao_menos_1 = 1;
                printf("\n=== ATENÇÃO!!! - Território %s CUMPRIU A MISSÃO: %s\n", territorios[atacante].nome, vetor_missoes[id_missao].missao);
            }
            break;
    }
}

// Cria função para liberar memória alocada para os territórios:
void libera_memoria(Tipo_missao *vetor_missoes) {
    if (vetor_missoes != NULL) {
        free(vetor_missoes);
    }
    free(territorios);
}

int main() {
    // Criando as variáveis locais:
    int qtde_territorios = 0;
    int territorio_atacante, territorio_defensor;
    int nao_fim;
    char missao_sorteada[MAX_STRING3];
    int indice_missao_sorteada;

    // Cria o ponteiro do Tipo_missao para armazenar as missões possíveis do jogo:
    Tipo_missao *missoes;

    // Alocando memória dinamicamente para as possíveis missões do jogo:
    missoes = (Tipo_missao *) calloc(MAX_MISSOES, sizeof(Tipo_missao));

    // Verificando se deu erro na alocação de memória para o ponteiro de missões:
    if (missoes == NULL) {
        printf("\nERRO!!! - Erro na alocação de memória para as missões!\n");
        return 1; // Retorna 1 para indicar que houve erro.
    }

    // Define as possíveis missões e armazena no vetor missões:
    strcpy(missoes[0].missao, "Alcançar, no total, 3 ou mais territórios com sua cor de tropa (incluindo o próprio).");
    strcpy(missoes[1].missao, "Dominar por completo um outro território qualquer.");
    strcpy(missoes[2].missao, "Vencer ao menos uma batalha contra qualquer outro território.");

    // Sorteia a missão que será adotada:
    indice_missao_sorteada = sorteia_missao();   // Chama a função para sortear a missão
    strcpy(missao_sorteada, missoes[indice_missao_sorteada].missao);
    printf("\nMISSÃO SORTEADA: %s\n", missao_sorteada);

    // Solicitando ao usuário a quantidade de territórios que ele irá cadastrar:
    printf("\nEntre com a quantidade de territórios a serem cadastrados (entre 1 e 50, inclusive, ou outro valor qualquer para sair): ");
    scanf("%d", &qtde_territorios);

    // limpa o buffer do teclado:
    limpa_buffer();

    if ((qtde_territorios > 0) && (qtde_territorios <= 50)) {
       
        // Alocando dinamicamente memória para a quantidade de territórios solicitada pelo usuário:
        territorios = (Tipo_territorio *) calloc(qtde_territorios, sizeof(Tipo_territorio));

        // Varificando se a alocação de memória deu certo:
        if (territorios == NULL) {
            printf("\nERRO!!! - Erro ao alocar memória para os territórios!\n");
            return 1;  // Retorna 1 para indicar que houve erro.
        }

        // Coletando os dados de cada território:
        cadastra_territorios(qtde_territorios);

        // Exibição dos dados cadastrados para cada território:
        exibe_territorios(territorios, qtde_territorios);

        // Loop para as rodadas de ataques ordenadas pelo usuário:
        do {
            // inicializa a variável de controle do loop como não sendo o fim do loop
            nao_fim = 1;

            printf("\n");
            printf("===> Instrua um ataque, indicando o território atacante e o território defensor:\n");
            printf("Entre com o número do território ATACANTE (entre 1 e %d, ou outro valor para sair do jogo): ", qtde_territorios);
            scanf("%d", &territorio_atacante);

            // limpa buffer do teclado:
            limpa_buffer();

            if ((territorio_atacante > 0) && (territorio_atacante <= qtde_territorios)) {
                printf("Entre com o número do território DEFENSOR (entre 1 e %d, exceto %d, ou outro valor para sair do jogo): ", qtde_territorios, territorio_atacante);
                scanf("%d", &territorio_defensor);

                // limpa buffer do teclado:
                limpa_buffer();

                // Verifica de o território atacante tem tropas para atacar e se está atacando território que não é do seu domínio:
                if (territorios[territorio_atacante - 1].qtde_tropas > 0) {
                    if (strcmp(territorios[territorio_atacante - 1].cor, territorios[territorio_defensor - 1].cor) != 0) {
                        if ((territorio_defensor != territorio_atacante) && (territorio_defensor > 0) && (territorio_defensor <= qtde_territorios)) {
                            printf("\n");
                            
                            atacante_venceu = 0;        // inicializa a varíavel global de controle de vitória do atacante

                            // Chama a função de ataque para os dois territórios fornecidos:
                            ataque(territorio_atacante - 1, territorio_defensor - 1);

                            // A função ataque() acima atualiza o valor da variável glonal atacante_venceu para 0 ou 1, dependendo do resultado do ataque

                            // Exibe a posição resultante dos territórios após ataque:
                            exibe_territorios(territorios, qtde_territorios);

                            // Verifica se a missão foi cumprida:
                            verifica_missao(missoes, indice_missao_sorteada, territorio_atacante - 1);

                        } else {
                            nao_fim = 0;
                        }
                    } else {
                        // Exibe mensagem que o território atacante não pode atacar o território defensor:
                        printf("\n");
                        printf("ESCOLHA INVÁLIDA! Não é permitido que um território ataque territórios já incorporados. Escolha outro ataque...\n");
                    }
                } else {
                    // Exibe mensagem que o território atacante não pode atacar o território defensor:
                    printf("\n");
                    printf("ESCOLHA INVÁLIDA! Não é permitido que um território sem tropas ataque outro...\n");
                }
            } else {
                nao_fim = 0;
            }

        } while (nao_fim);

        // Exibe mensagem de finalização do jogo como solicitado:
        printf("\n");
        printf("=== Jogo finalizado como solicitado! Volte sempre! ===");

        // libera a memória alocada para os territórios:
        libera_memoria(missoes);
    }
    
    printf("\n");

    return 0;
}