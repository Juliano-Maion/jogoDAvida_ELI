//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * controller.cpp  -  CONTROLLER (MVC): fluxo do programa.
 * (sem entrada/saida de tela: toda interacao com o operador esta no View)
 */
#include <stdlib.h>
#include <time.h>
#include "model.h"
#include "view.h"
#include "controller.h"

/* Arquivo onde as geracoes sao gravadas (REQ12/REQ13) */
#define ARQUIVO "geracoes.dat"

/* Espera 'ms' milissegundos (clock() da biblioteca padrao) */
static void esperar_ms(int ms)
{
	clock_t fim = clock() + (clock_t)((double)ms * CLOCKS_PER_SEC / 1000.0);
	while (clock() < fim)
		;
}

/* ------------------------------------------------------------------ */
/* REQ02 - definir os seres vivos da primeira geracao                  */
/* ------------------------------------------------------------------ */
/* O mapa e mostrado de novo apos CADA alteracao. */
static void editar_celulas(int mostrar_mortas)
{
	int l, c;

	while (ler_coordenadas(&l, &c))         /* 0 = usuario digitou -1 */
	{
		if (celula_viva(l, c))
		{
			/* a celula ja existe: oferece excluir */
			if (confirmar("a celula ja existe. Deseja exclui-la?"))
				remover_celula(l, c);
		}
		else
			criar_celula(l, c);

		mostrar_estado(mostrar_mortas, 0, 0);
	}
}

/* ------------------------------------------------------------------ */
/* REQ06, REQ07, REQ08 - simulacao                                     */
/* ------------------------------------------------------------------ */
/* A geracao 1 e o mapa como esta agora (igual ao exemplo do enunciado);
   pedir N geracoes mostra a atual e mais N-1 evolucoes. */
static void simular(int mostrar_mortas)
{
	int total, velocidade, g;

	total = ler_geracoes();                 /* REQ07 */
	velocidade = ler_velocidade();          /* REQ08: 0 = passo a passo */

	for (g = 1; g <= total; g++)
	{
		limpar_tela();
		mostrar_estado(mostrar_mortas, g, total);

		if (g == total)                     /* ultima geracao pedida */
			break;

		if (contar_vivas() == 0)            /* ninguem vivo: nada a simular */
		{
			mostrar_mensagem("todas as celulas morreram. Simulacao encerrada.");
			break;
		}

		if (velocidade == 0)
		{
			if (!ler_passo())               /* passo a passo: operador decide */
				break;
		}
		else
			esperar_ms(velocidade);

		if (!proxima_geracao())             /* model calcula a proxima */
		{
			mostrar_mensagem("memoria insuficiente. Simulacao encerrada.");
			break;
		}
	}
}

/* ------------------------------------------------------------------ */
/* Menu principal                                                      */
/* ------------------------------------------------------------------ */
void menu_principal(void)
{
	int mostrar_mortas = 0;   /* REQ04: 0 = sem '+', 1 = com '+' */
	int indice_carga   = 0;   /* REQ13: proximo registro do arquivo a carregar */
	int mostrar        = 1;   /* 1 = mostra o mapa antes do menu */
	int opcao, r;

	do
	{
		/* o mapa aparece SEMPRE, automaticamente, apos cada interacao */
		if (mostrar)
			mostrar_estado(mostrar_mortas, 0, 0);
		mostrar = 1;

		opcao = ler_opcao_menu(mostrar_mortas);

		switch (opcao)
		{
		case 1:     /* REQ02 (ja mostra o mapa a cada alteracao) */
			editar_celulas(mostrar_mortas);
			mostrar = 0;
			break;

		case 2:     /* REQ04: liga/desliga o '+' */
			mostrar_mortas = !mostrar_mortas;
			break;

		case 3:     /* REQ05 */
			if (confirmar("limpar TODAS as celulas do mapa?"))
				iniciar_mundo();
			break;

		case 4:     /* REQ06, REQ07, REQ08 (termina mostrando a ultima geracao) */
			simular(mostrar_mortas);
			mostrar = 0;
			break;

		case 5:     /* REQ12 */
			if (salvar_geracao(ARQUIVO))
				mostrar_mensagem("geracao gravada no arquivo.");
			else
				mostrar_mensagem("erro ao gravar o arquivo.");
			break;

		case 6:     /* REQ13 */
			r = carregar_geracao(ARQUIVO, indice_carga);
			if (r == 1)
			{
				indice_carga++;      /* o proximo comando carrega a seguinte */
				mostrar_geracao_carregada(indice_carga);
			}
			else if (r == -1)
				mostrar_mensagem("arquivo nao encontrado (salve uma geracao antes).");
			else if (indice_carga == 0)
				mostrar_mensagem("o arquivo esta vazio.");
			else
			{
				mostrar_mensagem("fim do arquivo: nao ha mais geracoes. "
				                 "O proximo comando volta a primeira.");
				indice_carga = 0;
			}
			break;

		case 7:     /* REQ01: tamanho pode ser alterado a qualquer momento */
			definir_dimensao(ler_dimensao());   /* limpa o mapa */
			break;
		}
	} while (opcao != 0);
}

/* REQ01: pede o tamanho do mundo e entra no menu */
void iniciar_jogo(void)
{
	iniciar_mundo();                        /* mapa inicial so com '.' */
	definir_dimensao(ler_dimensao());
	menu_principal();
}
