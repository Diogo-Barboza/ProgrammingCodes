#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
   int dado;
   struct celula *prox;
} celula;

void insere_inicio (celula *le, int x) {
    celula *novo = malloc(sizeof(celula));
    novo -> dado = x;
    novo -> prox = le -> prox;
    le -> prox = novo;
}


void insere_antes(celula *le, int x, int y) {
    celula *ant = le;
    celula *ptr = le->prox;

    while (ptr != NULL) {
        if (ptr->dado == y) {
            break; 
        }
        ant = ptr;
        ptr = ptr->prox;
    }

    celula *novo = malloc(sizeof(celula));
    novo->dado = x;

    novo->prox = ptr;
    ant->prox = novo;
}

