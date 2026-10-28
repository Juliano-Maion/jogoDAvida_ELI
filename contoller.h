//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * controller.h  -  CONTROLLER (MVC)
 *
 * Decide o que fazer: pede dados ao View, altera o Model e manda o View
 * mostrar o resultado. NAO interage com o operador.
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

/* Inicia o jogo: pede o tamanho (REQ01) e abre o menu principal */
void iniciar_jogo(void);

/* Loop do menu: termina quando o usuario escolhe sair */
void menu_principal(void);

#endif
