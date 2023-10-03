#include "lista2.h"
#include <stdlib.h>
#include <stdio.h>

usermail inicia_usuario(int id);

//a função inicia a lista, reservando memória com alocação dinamica
Lista_user* nova_lista(){
    Lista_user* lista = malloc(sizeof(Lista_user));
    lista->tamanho = 0;
    lista->inicio = NULL;
    return lista;
}
// retorno da função é o tamanho lista
int tamamho_lista(Lista_user* lista){
    return lista->tamanho;
}

void novo_usuario(Lista_user* lista,  int id){
    //cria uma celula para o novo usuario e guarda ele.
    Celula* insere_celula = malloc(sizeof(Celula));
    //para criar o novo usuario, tambem é necessario inicar ele
    insere_celula->usuario = inicia_usuario(id); 
    //o novo usuario é adicionado no fim da fila, logo o ponteiro "next" passa a apontar pra NULL
    insere_celula->next = NULL;
    lista->tamanho++;

    //Quando  a lista tiver vazia, essa pessoa será inserida na "cabeça"
    if(lista->inicio == NULL){
        lista->inicio = insere_celula;
        return;
    }
    // percorre a lista até o final, e usa uma variavel auxiliar e depois do laço, insere no ultimo elemento
    Celula* c = lista->inicio;
    while(c->next != NULL){
        c = c->next;
    }
    c->next = insere_celula;
}

//a função inicia as caixas de "emails" do usuario, no caso as dez filas
usermail inicia_usuario(int id){
    usermail retorna;
    for(int i = 0; i < PRIORIDADE; i++){
        retorna.fila[i] = nova_fila();
    }
    retorna.id = id;
    return retorna;
}

//passa o id e devolve o indice do usuario na lista
int procura_indice(Lista_user* lista, int id){
    Celula* c = lista->inicio;
    int i = 0;
    while(c != NULL){
        if(c->usuario.id == id){
            return i;
        }
        c = c->next;
        i++;
    }
    //para quando o usuario com id que foi passado nao existe
    return -1;
}

//remove o usuario da lista com o id
void remove_usuario(Lista_user* lista, int id){
    int i = procura_indice(lista, id);
    //quando o retorno da função é -1, significa que o usuario do id indicado nao existe
    if(i == -1){
        printf("CONTA ID NAO EXISTE!\n");
        return;
    }
    Celula* c = lista->inicio;
    int indice = 0;
    //quando o i = 0, vamos remover a cabeca, atualizamos a celula pra NULL
    if(i == 0){
        Celula* aux;
        aux = lista->inicio;
        lista->inicio = lista->inicio->next;
        limpa_usuario(aux->usuario);
        free(aux);
        lista->tamanho--;
        return;
    }
    // caso contrario, pega a celula antes do elemento que deseja remover
    // e coloca pra apontar para o proximo da lista que deseja remover e depois dar um free na celula
    while(c->next != NULL){
        if(indice == i - 1){
          Celula* aux;
          aux = c->next;
          c->next = c->next->next;
          limpa_usuario(aux->usuario);
          free(aux);
          lista->tamanho--;
          break;
        }
        c = c->next;
        indice++;
    }
}   

//funcao que retorna o usuario passando o id, percorre a lista e procura
// usuario com o mesmo id que o passado, quando encontra é retornado o o usuario
usermail* retorna_usuario(Lista_user* lista, int id){
    Celula* c = lista->inicio;
    while(c != NULL){
        if(c->usuario.id == id){
            return &c->usuario;
        }
        c = c-> next;
    }
    return NULL;
}

//é passado o id e é chamada uma funcao que retorna o o usuario, quando usuario
// nao existe é retornado false, quando é diferente de NULL o retorno
// é chamada uma funcao que coloca o email na fila no indice da prioridade que é passada
bool enviar_email(Lista_user* lista, int id, Email email, int prioridade){
    usermail *usuario = retorna_usuario(lista, id);
    if(usuario == NULL){
        return false;
    }
    coloca_email(usuario->fila[prioridade], email);
    return true;
}

//é passado o id e é chamada uma funcao que retorna o o usuario, depois percorre
// a fila da maior prioridade para a menor, quando está vazia ela retorna falso e nao executa o if,
//quando executa, é tirado o email da fila, o mais antigo com maior prioridade e a variavel
// email é atualizada com o email retirado, porem quando a fila nao tem email, é retornado falso
bool ler_email(Lista_user* lista, int id, Email email){
    usermail *usuario = retorna_usuario(lista, id);
    for(int i = PRIORIDADE - 1; i>=0; i--){
        if(tira_email(usuario->fila[i], email)){
            return true;
        }
    }
    return false;
}


void limpa_usuario(usermail user) {
    for(int i = 0; i < PRIORIDADE; i++) {
        limpa_fila(user.fila[i]);
    }
}