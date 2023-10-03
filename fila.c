#include <stdio.h>
#include "fila.h"
#include <stdlib.h>
#include <string.h>

void limpa_fila(Fila_email* fila) {
    Celula_email* antigo = NULL;
    for(Celula_email* c = fila->primeiro; c != NULL; c = c->next) {
        if(antigo != NULL) free(antigo);
        antigo = c;
    }
    free(antigo);
    free(fila);
}

//a funcao inicia a fila, alocando memoria para ela
Fila_email* nova_fila(){
    Fila_email* fila = malloc(sizeof(Fila_email));
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    return fila;
}

// funcao que verifica se a fila ta vazia
bool fila_vazia(Fila_email* fila){
    if(fila->primeiro == NULL && fila->ultimo == NULL) return true;
    return false;
}

//funcao adiciona elemento na fila, nesse caso, o "email"
void coloca_email(Fila_email* fila, Email email){
    Celula_email* insere_celula = malloc(sizeof(Celula_email));
    strcpy(insere_celula->email, email);
    insere_celula->next = NULL; 
    //quando a fila está vazia, o novo elemento da fila 
    //é colocado no primeiro e ultimo elemento da fila
    if(fila->primeiro == NULL){
        fila->primeiro = insere_celula;
        fila->ultimo = insere_celula;
        return;
    }
    Celula_email* p = fila->primeiro;
    //quando tem mais elementos na fila, percorre até o ultimo e coloca no proximo
    while(p->next != NULL){
        p = p->next;
    }
    p->next = insere_celula;

}

//funcao que remove elemento da fila
bool tira_email(Fila_email* fila, Email email){
    //if verifica se a fila esta vazia, se estiver, retorna falso, pois 
    // não há nenhum elemento para ser removido
    if(fila_vazia(fila)){
        return false;
    }
    strcpy(email, fila->primeiro->email);
    Celula_email* aux;
    aux =  fila->primeiro;
    //para quando tiver apenas um elemento na fila
    if (fila->ultimo == fila->primeiro) {
        fila->ultimo = NULL;
    }
    //quando tiver apenas um elemento, o primeiro tambem apontará para NULL
    //nos outros casos, o primeiro passa a ser o proximo elemento e é deslocado
    //o antigo primeiro elemento
    fila->primeiro = fila->primeiro->next;
    free(aux);
    return true;
}


