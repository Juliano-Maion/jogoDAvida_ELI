//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * main.cpp  -  Projeto Jogo da Vida (REQ01 a REQ13)
 *
 * Padrao MVC:
 *   model.*       -> matriz, regras, lista ligada, arquivo (sem tela/teclado)
 *   view.*        -> toda interacao com o operador (tela e teclado)
 *   controller.*  -> fluxo do programa (sem tela/teclado)
 *
 * COMO COMPILAR (sem criar projeto):
 *   Para permitir compilar SOMENTE este arquivo no Dev-C++ (F11),
 *   as implementacoes das tres camadas sao incluidas aqui embaixo.
 *
 *   IMPORTANTE: compile apenas main.cpp. NAO adicione model.cpp,
 *   view.cpp e controller.cpp separadamente na compilacao, pois eles
 *   ja sao incluidos abaixo (senao ocorre erro de definicao duplicada).
 *
 * Linha de comando equivalente:  g++ main.cpp -o jogo_da_vida
 */
#include "model.h"
#include "view.h"
#include "controller.h"

/* implementacoes das tres camadas (ordem: model, view, controller) */
#include "model.cpp"
#include "view.cpp"
#include "controller.cpp"

int main(void)
{
	iniciar_jogo();
	return 0;
}
