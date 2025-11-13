#include <stdio.h>
#include <stdlib.h> // Para a função system("cls") ou system("clear")
#include <math.h>   // Para a função abs()


// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.


#define LINHAS 10
#define COLUNAS 10

// Exibição do tabuleiro (imprime valores numéricos: 0=água, 3=navio, 5=habilidade)
void exibirTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    // Cabeçalho de colunas
    printf("  ");
    for (int j = 0; j < COLUNAS; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Linhas do tabuleiro: imprime os valores numéricos diretamente
    for (int i = 0; i < LINHAS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLUNAS; j++) {
            // Imprime o valor inteiro na célula (0, 3, 5, etc.)
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Definições de tamanho de habilidade
#define HABILIDADE_TAM 5

// Função para gerar a matriz de habilidade Cone 
void gerarMatrizCone(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            matriz[i][j] = 0; // Inicializa com 0
        }
    }

    // Padrão exato do cone (1 marca área de efeito)
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    matriz[0][2] = 1;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 1;
    matriz[2][0] = 1;
    matriz[2][1] = 1;
    matriz[2][2] = 1;
    matriz[2][3] = 1;
    matriz[2][4] = 1;
}

// Função para gerar a matriz de habilidade Cruz
void gerarMatrizCruz(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            matriz[i][j] = 0; // Inicializa com 0
        }
    }

    // Padrão exato da cruz (1 marca área de efeito)
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0
    matriz[0][2] = 1;
    matriz[1][0] = 1;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 1;
    matriz[1][4] = 1;
    matriz[2][2] = 1;
}

// Função para gerar a matriz de habilidade Octaedro
void gerarMatrizOctaedro(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            matriz[i][j] = 0; // Inicializa com 0
        }
    }

    // Padrão exato do octaedro (1 marca área de efeito)
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0
    matriz[0][2] = 1;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 1;
    matriz[2][2] = 1;
}

// Aplicação a habilidade ao tabuleiro
void aplicarHabilidade(
    int tabuleiro[LINHAS][COLUNAS],
    int matrizHabilidade[HABILIDADE_TAM][HABILIDADE_TAM],
    int origem_linha,
    int origem_coluna
) {
    int offset = HABILIDADE_TAM / 2;

    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (matrizHabilidade[i][j] == 1) {
                int linha_tabuleiro = origem_linha - offset + i;
                int coluna_tabuleiro = origem_coluna - offset + j;

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (linha_tabuleiro >= 0 && linha_tabuleiro < LINHAS &&
                    coluna_tabuleiro >= 0 && coluna_tabuleiro < COLUNAS) {
                    // Aplica a habilidade apenas se não houver um navio no local
                    if (tabuleiro[linha_tabuleiro][coluna_tabuleiro] != 3) {
                        tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;
                    }
                }
            }
        }
    }
}







int main() {
    int tabuleiro[LINHAS][COLUNAS];
    int matrizCone[HABILIDADE_TAM][HABILIDADE_TAM];
    int matrizCruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int matrizOctaedro[HABILIDADE_TAM][HABILIDADE_TAM];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Adiciona alguns navios (3) para demonstração
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[2][5] = 3;

    tabuleiro[5][1] = 3;
    tabuleiro[6][1] = 3;
    tabuleiro[7][1] = 3;

    printf("Tabuleiro Inicial:\n");
    exibirTabuleiro(tabuleiro);
    printf("Pressione ENTER para continuar...\n");
    getchar();

    // Gerar e aplicar habilidade Cone
    gerarMatrizCone(matrizCone);
    aplicarHabilidade(tabuleiro, matrizCone, 3, 3); // Origem (3,3)
    printf("Tabuleiro com Habilidade Cone (Origem 3,3):\n");
    exibirTabuleiro(tabuleiro);
    printf("Pressione ENTER para continuar...\n");
    getchar();

    // Resetar tabuleiro para aplicar próxima habilidade
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j] == 5) {
                tabuleiro[i][j] = 0;
            }
        }
    }

    // Gerar e aplicar habilidade Cruz
    gerarMatrizCruz(matrizCruz);
    aplicarHabilidade(tabuleiro, matrizCruz, 6, 6); // Origem (6,6)
    printf("Tabuleiro com Habilidade Cruz (Origem 6,6):\n");
    exibirTabuleiro(tabuleiro);
    printf("Pressione ENTER para continuar...\n");
    getchar();

    // Resetar tabuleiro para aplicar próxima habilidade
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j] == 5) {
                tabuleiro[i][j] = 0;
            }
        }
    }

    // Gerar e aplicar habilidade Octaedro
    gerarMatrizOctaedro(matrizOctaedro);
    aplicarHabilidade(tabuleiro, matrizOctaedro, 1, 8); // Origem (1,8)
    printf("Tabuleiro com Habilidade Octaedro (Origem 1,8):\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
