//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * view.h  -  VIEW (MVC)
 *
 * TODA a interacao com o operador fica aqui: tudo que e mostrado na
 * tela (printf) e tudo que e lido do teclado (fgets/sscanf).
 * O controller e o model NAO usam printf/scanf.
 */
#ifndef VIEW_H
#define VIEW_H

#include "model.h"

/* ---------- saida ---------- */
void limpar_tela(void);

/* REQ03/REQ04/REQ09/REQ11: mapa + contagens + listas.
   geracao > 0 mostra "geracao X"; total > 0 mostra "geracao X de Y". */
void mostrar_estado(int mostrar_mortas, int geracao, int total);

void mostrar_mensagem(const char *texto);
void mostrar_geracao_carregada(int numero);

/* ---------- entrada ---------- */
int ler_dimensao(void);                 /* REQ01: tamanho 10 a 60 */
int ler_opcao_menu(int mostrar_mortas); /* mostra o menu e le a opcao */
int ler_coordenadas(int *l, int *c);    /* REQ02: "linha coluna" separados por espaco; 1 = leu, 0 = usuario digitou -1 */
int confirmar(const char *pergunta);    /* sim/nao: 1 = sim */
int ler_geracoes(void);                 /* REQ07 */
int ler_velocidade(void);               /* REQ08 (0 = passo a passo) */
int ler_passo(void);                    /* passo a passo: 1 = continua, 0 = para */

#endif
