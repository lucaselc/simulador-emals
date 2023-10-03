#ifndef LISTA2_H
#define LISTA2_H
#include "fila.h"
#include "string.h"
#define PRIORIDADE 10

typedef struct usermail{
    int id;
    Fila_email* fila[PRIORIDADE];
}usermail;

typedef struct Celula{
    usermail usuario;
    struct Celula* next;
} Celula;

typedef struct Lista_user{
    int tamanho;
    Celula* inicio;
} Lista_user;

Lista_user* nova_lista();
usermail* retorna_usuario(Lista_user* lista, int id);
int procura_indice(Lista_user* lista, int id);
int tamamho_lista(Lista_user* lista);
void novo_usuario(Lista_user* lista, int id);
void remove_usuario(Lista_user* lista, int id);
bool enviar_email(Lista_user* lista, int id, Email email, int prioridade);
bool ler_email(Lista_user* lista, int id, Email email);
void limpa_usuario(usermail user);

#endif