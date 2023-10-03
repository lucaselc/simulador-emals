#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista2.h"

//funcao verifica se o usuario do id passado tem "emails" na caixa de mensagem
void consulta_caixa(Lista_user* lista, int id){
    Email saida;
    //se o usuario existir, chama a função da ler o email e printa ele na tela
    //quando houver email na caixa de email, quando estiver vazia, ele imprime erro
    if(retorna_usuario(lista, id) != NULL){
        if(ler_email(lista, id, saida)) {
        printf("CONSULTA %d: %s\n", id , saida);
        } else {
        printf("CAIXA DE ENTRADA VAZIA\n");
        }    
    }
    //quando a conta não existe, imprime um erro.
    else{
        printf("ERRO: CONTA %d NAO EXISTE\n", id);
    }

}

//função para cadastrar usuario
void cadastra_usuario(Lista_user* lista, int id){
    //quando é chamada a funcão dentro do if, se retorna NULL, significa que não 
    // tem nenhum usuario cadastrado com esse id e chama a função para cadastrar o novo usuario
    if(retorna_usuario(lista, id) == NULL){
        novo_usuario(lista, id);
        printf("OK: CONTA %d CADASTRADA\n", id);
    }
    //quando já existe algum usuario cadastrado com id passado
    else{
        printf("ERRO: CONTA %d JA EXISTENTE\n", id);
    }
}

// funcao remove usuario com id passado
void remove_id(Lista_user* lista, int id){
    //quando chama a função do if e é executado o if, é chamada a função para remover
    //o usuario e imprime que foi removida a conta
    if(retorna_usuario(lista, id) != NULL){
        remove_usuario(lista, id);
        printf("OK: CONTA %d REMOVIDA\n", id);
    }
    //quando não entra no if, é porque não há usuario com o id passado
    else{
        printf("ERRO: CONTA %d NAO EXISTE\n", id);
    }
}


//função para inserir email na fila do usuario 
void entrega_email(Lista_user* lista, int id, int prioridade, Email email){
    //como foi pedido na especificação que o email teria "FIM" no final da 
    // mensagem indicando final do email, então usei a fução strstr para encontrar
    // "FIM" no email.
    char* p =  strstr(email, "FIM");
    //
    if(p == NULL){
        return;
    }
    //colocando '\0' antes do "FIM", para enviar o email até aquela parte
    *(p - 1) = '\0';
    //chama a função para enviar email e só entra if se a conta existir, quando existir 
    // printa uma mensagem de sucesso(o email foi enviado), caso contrario mensagem de erro, pois
    //não existe a conta que deseja enviar email
    if(enviar_email(lista,id, email, prioridade)){
        printf("OK: MENSAGEM PARA %d ENTREGUE\n", id);
    }else{
        printf("ERRO: CONTA %d NAO EXISTE\n", id);
    }
}
