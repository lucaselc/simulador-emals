#ifndef OPERACOES_H
#define OPERACOES_H
#include <string.h>
#include "lista2.h"

void consulta_caixa(Lista_user* lista, int id);
void cadastra_usuario(Lista_user* lista, int id);
void remove_id(Lista_user* lista, int id);
void entrega_email(Lista_user* lista, int id, int prioridade, Email email);


#endif