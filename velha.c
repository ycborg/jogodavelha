#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LINHAS 3
#define COLUNAS 3

typedef struct {
    char XorO[LINHAS][COLUNAS];
} Tabuleiro;

void inicializarTabuleiro(Tabuleiro* tabuleiro) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro->XorO[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro(const Tabuleiro* tabuleiro) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (j == 0) printf("\t\t\t");
            printf(" %c ", tabuleiro->XorO[i][j]);
            if (j < COLUNAS - 1) {
                printf("|");
            }
        }
        if (i < LINHAS - 1) {
            printf("\n\t\t\t---|---|---\n");
        }
    }
}

int realizarJogada(Tabuleiro* tabuleiro, int x, int y, int jogada) {
    if (tabuleiro->XorO[x][y] == ' ') {
        tabuleiro->XorO[x][y] = (jogada%2==0) ? 'O' : 'X';
        jogada++;
    } else {
        system("cls || clear");
        printf ("Esse quadrante ja foi escolhido\n");
        system("pause ");
    }
    return jogada;
}

bool verificarVencedor(Tabuleiro* tabuleiro) {
    for (int i = 0; i < 3; ++i) {
        if (tabuleiro->XorO[i][0] == tabuleiro->XorO[i][1] &&
            tabuleiro->XorO[i][1] == tabuleiro->XorO[i][2] &&
            tabuleiro->XorO[i][2] != ' ') return true;
    }

    for (int j = 0; j < 3; ++j) {
        if (tabuleiro->XorO[0][j] == tabuleiro->XorO[1][j] &&
            tabuleiro->XorO[1][j] == tabuleiro->XorO[2][j] &&
            tabuleiro->XorO[2][j] != ' ') return true;
    }

    if (tabuleiro->XorO[0][0] == tabuleiro->XorO[1][1] &&
        tabuleiro->XorO[1][1] == tabuleiro->XorO[2][2] &&
        tabuleiro->XorO[2][2] != ' ') return true;

    if (tabuleiro->XorO[0][2] == tabuleiro->XorO[1][1] &&
        tabuleiro->XorO[1][1] == tabuleiro->XorO[2][0] &&
        tabuleiro->XorO[2][0] != ' ') return true;

    return false;
}

int main(void) {

    bool alguemVenceu;
    Tabuleiro meuTabuleiro;
    int resp = 1, x, y, jogada = 1;
    inicializarTabuleiro(&meuTabuleiro);

    do {
        system("cls || clear");
        printf("\t\t Bem vindo ao jogo da velha!\n\n");
        printf("Para realizar uma jogada coloque as coordenadas x y do quadrante que deseja.\n");
        printf("Por Exemplo: para jogar no meio coloque 2 2.\n\n");
        imprimirTabuleiro(&meuTabuleiro);

        if (jogada%2==0) printf("\n\nE a vez do 'O' > ");
        else printf("\n\nE a vez do 'X' > ");

        int i = scanf("%i %i", &x, &y);

        if (i != 2 || x > 3 || x < 1 || y > 3 || y < 1) {
            system("cls || clear");
            fflush(stdin);
            printf("Voce precisa escolher as coordenadas corretamente\n");
            system("pause");
            continue;
        }

        jogada = realizarJogada(&meuTabuleiro, x - 1, y - 1, jogada);

        if (jogada >= 6) alguemVenceu = verificarVencedor(&meuTabuleiro);
        
        if (alguemVenceu == false && jogada == 10) {
            system("cls || clear");
            imprimirTabuleiro(&meuTabuleiro);
            printf("\n\n\t\tO jogo empatou (deu velha) :/\n\n");
            system("pause");
        } else if (alguemVenceu == false) continue;
        else {
            system("cls || clear");
            imprimirTabuleiro(&meuTabuleiro);
            if (jogada%2==0) printf("\n\n\t\tO 'X' venceu!!! Parabens :)\n\n");
            else printf("\n\n\t\tO 'O' venceu!!! Parabens :)\n\n");
            system("pause");
        }

        system("cls || clear");
        printf("Deseja jogar novamente?\n");
        printf("  1 = sim | 2 = nao\n > ");
        scanf("%i", &resp);
        system("cls || clear");

    } while (resp == 1);
    return 0;
}