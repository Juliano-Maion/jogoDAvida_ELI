//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * view.cpp  -  VIEW (MVC): unico arquivo com printf/scanf do programa.
 */
#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "view.h"

/* ------------------------------------------------------------------ */
/* Leitura segura                                                      */
/* ------------------------------------------------------------------ */
/* Lemos SEMPRE uma linha inteira (fgets) e depois interpretamos (sscanf):
   se o usuario digitar letras, o programa nao entra em loop infinito. */
static void ler_linha(char *buf, int n)
{
	if (fgets(buf, n, stdin) == NULL)
		exit(0);                    /* acabou a entrada: encerra */
}

/* Pede um inteiro entre minimo e maximo; repete ate ser valido */
static int ler_inteiro(const char *msg, int minimo, int maximo)
{
	char buf[100];
	int v;

	for (;;)
	{
		printf("%s", msg);
		ler_linha(buf, sizeof(buf));
		if (sscanf(buf, "%d", &v) == 1 && v >= minimo && v <= maximo)
			return v;
		printf("valor invalido (use de %d a %d)\n", minimo, maximo);
	}
}

/* ------------------------------------------------------------------ */
/* Saida                                                               */
/* ------------------------------------------------------------------ */
void limpar_tela(void)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void mostrar_mensagem(const char *texto)
{
	printf("%s\n", texto);
}

void mostrar_geracao_carregada(int numero)
{
	printf("geracao %d carregada do arquivo.\n", numero);
}

/*
 * REQ01: o mapa tem que caber na tela sem quebrar linha. Cada coluna
 * ocupa 2 caracteres e o cabecalho usa DUAS linhas (dezena em cima,
 * unidade embaixo). Com 60 colunas a linha tem ~123 caracteres.
 */
static void mostrar_matriz(int mostrar_mortas)
{
	int i, j;
	char c;

	printf("\n   ");                           /* linha das dezenas */
	for (j = 0; j < dimensao; j++)
	{
		if (j >= 10)
			printf("%d ", j / 10);
		else
			printf("  ");
	}

	printf("\n   ");                           /* linha das unidades */
	for (j = 0; j < dimensao; j++)
		printf("%d ", j % 10);
	printf("\n");

	for (i = 0; i < dimensao; i++)
	{
		printf("%2d ", i);                     /* numero da linha */
		for (j = 0; j < dimensao; j++)
		{
			c = matriz[i][j];

			/* REQ04: morta com vizinho vivo vira '+' (so na tela;
			   a matriz do model nao e alterada) */
			if (c != 'O' && mostrar_mortas && contar_vizinhos_vivos(i, j) > 0)
				c = '+';

			printf("%c ", c);
		}
		printf("\n");
	}
}

/* Imprime uma lista de coordenadas, 10 por linha */
static void imprimir_lista(const char *titulo, No *lista)
{
	int n = 0;
	No *p;

	printf("%s (%d):\n", titulo, contar_lista(lista));
	for (p = lista; p != NULL; p = p->prox)
	{
		printf("(%d,%d) ", p->lin, p->col);
		n++;
		if (n % 10 == 0)
			printf("\n");
	}
	if (n == 0)
		printf("(nenhuma)");
	if (n == 0 || n % 10 != 0)
		printf("\n");
}

/* REQ03, REQ07, REQ09 e REQ11: o mapa e, logo ABAIXO dele,
   a geracao, as quantidades e as listas */
void mostrar_estado(int mostrar_mortas, int geracao, int total)
{
	No *vivas  = lista_vivas();
	No *mortas = lista_vizinhas_mortas();

	mostrar_matriz(mostrar_mortas);

	if (geracao > 0)                            /* REQ07: identifica a geracao */
	{
		if (total > 0)
			printf("geracao %d de %d: ", geracao, total);
		else
			printf("geracao %d: ", geracao);
	}

	printf("%d celulas vivas | %d celulas vizinhas-mortas\n",
	       contar_lista(vivas), contar_lista(mortas));

	imprimir_lista("Lista de celulas vivas", vivas);
	imprimir_lista("Lista de vizinhas-mortas", mortas);

	liberar_lista(vivas);
	liberar_lista(mortas);
}

/* ------------------------------------------------------------------ */
/* Entradas especificas                                                */
/* ------------------------------------------------------------------ */
int ler_dimensao(void)
{
	return ler_inteiro("escolha o tamanho do mundo [10 a 60]: ",
	                   DIM_MINIMA, DIM_MAXIMA);
}

/* Menu enxuto: o mapa ja foi mostrado automaticamente antes dele */
int ler_opcao_menu(int mostrar_mortas)
{
	printf("\n1-Inserir/excluir celula  2-Vizinhas-mortas '+': %s  3-Limpar mapa\n",
	       mostrar_mortas ? "SIM" : "NAO");
	printf("4-Simular  5-Salvar  6-Carregar  7-Mudar tamanho  0-Sair\n");
	return ler_inteiro("opcao: ", 0, 7);
}

/* REQ02 */
int ler_coordenadas(int *l, int *c)
{
	char buf[100];
	int n;

	for (;;)
	{
		printf("coordenadas [linha,coluna] (-1 para voltar): ");
		ler_linha(buf, sizeof(buf));
		n = sscanf(buf, "%d,%d", l, c);

		if (n >= 1 && *l == -1)
			return 0;
		if (n == 2 && coordenada_valida(*l, *c))
			return 1;
		printf("coordenada invalida (use 0 a %d)\n", dimensao - 1);
	}
}

int confirmar(const char *pergunta)
{
	char buf[100];

	for (;;)
	{
		printf("%s (s/n): ", pergunta);
		ler_linha(buf, sizeof(buf));
		if (buf[0] == 's' || buf[0] == 'S')
			return 1;
		if (buf[0] == 'n' || buf[0] == 'N')
			return 0;
		printf("responda s ou n\n");
	}
}

int ler_geracoes(void)
{
	return ler_inteiro("quantas geracoes simular [1 a 100000]: ", 1, 100000);
}

int ler_velocidade(void)
{
	return ler_inteiro("intervalo entre geracoes em ms (0 = passo a passo): ", 0, 60000);
}

int ler_passo(void)
{
	char buf[100];
	printf("[Enter] proxima geracao | s + [Enter] para parar: ");
	ler_linha(buf, sizeof(buf));
	return !(buf[0] == 's' || buf[0] == 'S');
}
