#pragma once

#include <memory.h>                               
#include <stdio.h>                               
#include <stdlib.h>
#include <string.h>

struct no
{
    void*      item;
    struct no* proxima;
    struct no* anterior;
};  // no
typedef struct no Node;

struct a_propria_lista
{
    char*     nome;
    unsigned  quantos;
    unsigned  maximo;
    Node*     inicio;
    Node*     fim;
};
typedef struct a_propria_lista Lista;

Lista*      _apagar(Lista*);
Lista*      _criar(const char*);
int         _define_maximo(Lista* l, const unsigned);
Lista*      _inserir_na_ordem(void*, Lista*, int(*)(void*, void*));
Lista*      _inserir_no_inicio(void*, Lista*);
Lista*      _inserir_no_final(void*, Lista*);
int         _listar(Lista*);
int         _listar_do_seu_jeito(Lista*, int(*)(void*));
int         _maximo(Lista*);
Node*       _primeiro(Lista*);
Lista*      _remover(void*, Lista*);
int         _tamanho(Lista*);
Node*       _ultimo(Lista*);
int         _vazia(Lista*);

//fim