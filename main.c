#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lista2.h"
#include "fila.h"
#include "operacoes.h"


void limpa_lista(Lista_user* user) {
    Celula* antigo = NULL;
    for(Celula* c = user->inicio; c != NULL; c = c->next) {
        if(antigo != NULL) free(antigo);
        limpa_usuario(c->usuario);
        antigo = c;
    }
    free(antigo);
    free(user);
}

int main(){
    Lista_user* lista = nova_lista();
    int id,pri;
    FILE* f = fopen("arquivo.txt", "r");
    //quando houver problemas para abrir o arquivo
    if(f == NULL){
        return 1;
    }
    //laço par5a executar os comando lido no arquivo, até o fim do arquivo
    while(!feof(f)){
        char palavra[20];
        fscanf(f, "%s %d", palavra, &id);
        if(strcmp(palavra, "CADASTRA") == 0){
            cadastra_usuario(lista, id);
        }
        else if(strcmp(palavra, "ENTREGA") == 0) {
            char op[1024];
            fscanf(f, " %d", &pri);
            fgets(op, 1023, f);
            entrega_email(lista, id, pri, op);
        }
        else if(strcmp(palavra, "REMOVE") == 0){
            remove_id(lista, id);
        }
        else if(strcmp(palavra, "CONSULTA") == 0){
            consulta_caixa(lista, id);
        }
        else{
            printf("Comando inválido\n");
        }

    }  
    fclose(f);
    //liberar a memoria
    limpa_lista(lista);
    return 0;
}