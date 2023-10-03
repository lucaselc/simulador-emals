#ifndef FILA_H
#define FILA_H
#include <stdbool.h>

typedef char Email[1024];

typedef struct Celula_email{
    Email email;
    struct Celula_email* next;
} Celula_email;

typedef struct Fila_email{
    int tamanho;
    Celula_email* primeiro , *ultimo;
} Fila_email;

Fila_email* nova_fila();
bool fila_vazia(Fila_email* fila);
void coloca_email(Fila_email* fila, Email email);
bool tira_email(Fila_email* fila, Email email);
void limpa_fila(Fila_email* fila);


#endif