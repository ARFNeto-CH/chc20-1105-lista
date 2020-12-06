#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
	int valor;
	struct No* prox;
}	TNo;

typedef TNo* TLista;


int insereNaPosicao(TLista* L, int inserido, int posicao)
{
	int con = 0, CON = 0;

	TLista AUX, aux, novo, tam;

	AUX = *L;	tam = *L;

	posicao = posicao - 1;

	novo = (TLista)malloc(sizeof(TNo));

	novo->valor = inserido;

	while (tam != NULL)
	{
		tam = tam->prox;

		CON++;
	}

	if (posicao > CON || posicao < 0)
	{
		return 0;
	}

	while (con < posicao - 1)
	{
		AUX = AUX->prox;

		con++;
	}

	aux = AUX->prox;

	AUX->prox = novo;

	novo->prox = aux;

	return 1;
}
// https://www.clubedohardware.com.br/topic/
// 1498772-inserindo-valor-em-determinada-posi%C3%A7%C3%A3o
// -da-lista-encadeada-linguagem-c/