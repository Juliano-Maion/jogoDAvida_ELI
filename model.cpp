//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * model.cpp  -  MODEL (MVC): matriz, regras, lista ligada e arquivo.
 * (sem entrada/saida de tela: nenhuma interacao com o operador aqui)
 */
#include <stdio.h>      /* so FILE, fopen, fread, fwrite, fclose */
#include <stdlib.h>
#include <string.h>
#include "model.h"

/* DEFINICAO da matriz do jogo (exigencia: fica no model) */
char matriz[linhas][colunas];
int  dimensao = DIM_MINIMA;

/* ------------------------------------------------------------------ */
/* Mundo                                                               */
/* ------------------------------------------------------------------ */

/* REQ01 / REQ05 - mapa vazio */
void iniciar_mundo(void)
{
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			matriz[i][j] = '.';
}

/* REQ01 - novo tamanho; o mapa volta a ficar vazio */
void definir_dimensao(int nova_dimensao)
{
	dimensao = nova_dimensao;
	iniciar_mundo();
}

int coordenada_valida(int l, int c)
{
	return l >= 0 && l < dimensao && c >= 0 && c < dimensao;
}

/* REQ02 */
int celula_viva(int l, int c)
{
	return matriz[l][c] == 'O';
}

void criar_celula(int l, int c)
{
	matriz[l][c] = 'O';
}

void remover_celula(int l, int c)
{
	matriz[l][c] = '.';
}

/* ------------------------------------------------------------------ */
/* Vizinhos                                                            */
/* ------------------------------------------------------------------ */
int contar_vizinhos_vivos(int l, int c)
{
	int dl, dc, nl, nc;
	int total = 0;

	/* percorre o quadrado 3x3 em volta de (l,c) */
	for (dl = -1; dl <= 1; dl++)
	{
		for (dc = -1; dc <= 1; dc++)
		{
			if (dl == 0 && dc == 0)
				continue;               /* a propria celula nao e vizinha de si */

			nl = l + dl;
			nc = c + dc;

			/* mundo plano: so conta se a posicao existe */
			if (coordenada_valida(nl, nc) && matriz[nl][nc] == 'O')
				total++;
		}
	}
	return total;
}

int contar_vivas(void)
{
	int i, j, total = 0;
	for (i = 0; i < dimensao; i++)
		for (j = 0; j < dimensao; j++)
			if (matriz[i][j] == 'O')
				total++;
	return total;
}

/* ------------------------------------------------------------------ */
/* REQ10 - lista simplesmente ligada com alocacao dinamica             */
/* ------------------------------------------------------------------ */

/* Insere no FIM em O(1) usando o ponteiro 'fim'.
   Retorna 1 ok, 0 se faltou memoria. */
static int inserir_fim(No **ini, No **fim, int l, int c)
{
	No *novo = (No *)malloc(sizeof(No));
	if (novo == NULL)                 /* sempre testar o malloc */
		return 0;

	novo->lin = l;
	novo->col = c;
	novo->prox = NULL;

	if (*ini == NULL)                 /* lista vazia: novo e o primeiro */
		*ini = novo;
	else                              /* senao liga o ultimo ao novo */
		(*fim)->prox = novo;
	*fim = novo;
	return 1;
}

void liberar_lista(No *lista)
{
	No *proximo;
	while (lista != NULL)
	{
		proximo = lista->prox;        /* guarda o proximo ANTES do free */
		free(lista);
		lista = proximo;
	}
}

int contar_lista(No *lista)
{
	int n = 0;
	while (lista != NULL)
	{
		n++;
		lista = lista->prox;
	}
	return n;
}

/* REQ11 - celulas vivas (se faltar memoria, devolve NULL) */
No *lista_vivas(void)
{
	No *ini = NULL, *fim = NULL;
	int i, j;
	for (i = 0; i < dimensao; i++)
		for (j = 0; j < dimensao; j++)
			if (matriz[i][j] == 'O' && !inserir_fim(&ini, &fim, i, j))
			{
				liberar_lista(ini);
				return NULL;
			}
	return ini;
}

/* REQ04/REQ11 - vizinha-morta: celula morta com ao menos 1 vizinho vivo */
No *lista_vizinhas_mortas(void)
{
	No *ini = NULL, *fim = NULL;
	int i, j;
	for (i = 0; i < dimensao; i++)
		for (j = 0; j < dimensao; j++)
			if (matriz[i][j] != 'O' && contar_vizinhos_vivos(i, j) > 0 &&
			    !inserir_fim(&ini, &fim, i, j))
			{
				liberar_lista(ini);
				return NULL;
			}
	return ini;
}

/* ------------------------------------------------------------------ */
/* REQ06 / REQ10 - proxima geracao                                     */
/* ------------------------------------------------------------------ */
/*
 * As regras valem "ao mesmo tempo" para todas as celulas: NAO alteramos
 * a matriz enquanto a percorremos. Primeiro montamos, numa lista
 * auxiliar, quem estara VIVO na proxima geracao; so depois limpamos a
 * matriz e preenchemos com essa lista.
 *
 *  - viva com 2 ou 3 vizinhos            -> sobrevive
 *  - viva com 0,1 (solidao) ou 4+        -> morre
 *  - vazia com exatamente 3 vizinhos     -> nasce
 */
int proxima_geracao(void)
{
	No *ini = NULL, *fim = NULL, *p;
	int i, j, viz, ok;

	for (i = 0; i < dimensao; i++)
	{
		for (j = 0; j < dimensao; j++)
		{
			viz = contar_vizinhos_vivos(i, j);
			ok = 1;

			if (matriz[i][j] == 'O')
			{
				if (viz == 2 || viz == 3)           /* sobrevivencia */
					ok = inserir_fim(&ini, &fim, i, j);
			}
			else if (viz == 3)                      /* reproducao */
				ok = inserir_fim(&ini, &fim, i, j);

			if (!ok)                                /* sem memoria: aborta */
			{
				liberar_lista(ini);
				return 0;
			}
		}
	}

	/* aplica a nova geracao */
	iniciar_mundo();
	for (p = ini; p != NULL; p = p->prox)
		matriz[p->lin][p->col] = 'O';

	liberar_lista(ini);
	return 1;
}

/* ------------------------------------------------------------------ */
/* REQ12 - salvar geracao                                              */
/* ------------------------------------------------------------------ */
/*
 * Arquivo BINARIO. Cada registro:
 *     int dimensao, int quantidade,
 *     depois 'quantidade' pares (int linha, int coluna) das vivas.
 * Abrimos com "ab" (append): cada gravacao e ACRESCENTADA ao fim,
 * sem apagar as anteriores ("gravadas sucessivamente").
 */
int salvar_geracao(const char *arquivo)
{
	FILE *fp = fopen(arquivo, "ab");
	int cab[2], par[2], i, j, ok = 1;

	if (fp == NULL)
		return 0;

	cab[0] = dimensao;
	cab[1] = contar_vivas();
	if (fwrite(cab, sizeof(int), 2, fp) != 2)
		ok = 0;

	for (i = 0; i < dimensao && ok; i++)
		for (j = 0; j < dimensao && ok; j++)
			if (matriz[i][j] == 'O')
			{
				par[0] = i;
				par[1] = j;
				if (fwrite(par, sizeof(int), 2, fp) != 2)
					ok = 0;
			}

	fclose(fp);
	return ok;
}

/* ------------------------------------------------------------------ */
/* REQ13 - carregar geracao                                            */
/* ------------------------------------------------------------------ */

/* Le UM registro para a matriz temporaria 'tmp'. 1 ok, 0 fim/invalido */
static int ler_registro(FILE *fp, int *dim, char tmp[linhas][colunas])
{
	int cab[2], par[2], k;

	if (fread(cab, sizeof(int), 2, fp) != 2)
		return 0;
	*dim = cab[0];
	if (*dim < DIM_MINIMA || *dim > DIM_MAXIMA || cab[1] < 0 || cab[1] > (*dim) * (*dim))
		return 0;

	for (k = 0; k < linhas * colunas; k++)      /* limpa tmp */
		tmp[k / colunas][k % colunas] = '.';

	for (k = 0; k < cab[1]; k++)
	{
		if (fread(par, sizeof(int), 2, fp) != 2)
			return 0;
		if (par[0] >= 0 && par[0] < *dim && par[1] >= 0 && par[1] < *dim)
			tmp[par[0]][par[1]] = 'O';
	}
	return 1;
}

/* Para chegar ao registro 'indice' lemos (e descartamos) os anteriores.
   Matriz temporaria: se o registro nao existir, o mapa atual nao e perdido. */
int carregar_geracao(const char *arquivo, int indice)
{
	char tmp[linhas][colunas];
	int k, dim = 0;
	FILE *fp = fopen(arquivo, "rb");

	if (fp == NULL)
		return -1;

	for (k = 0; k <= indice; k++)
	{
		if (!ler_registro(fp, &dim, tmp))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);

	dimensao = dim;
	memcpy(matriz, tmp, sizeof(tmp));
	return 1;
}
