//Jogo da vida - Projeto Jogo da vida 2026
//22/10/2026
//Juliano Vion Junior, Lorenzo Moraes Cunha, Murilo Lopes Fortes Bustamante, Rafael Mota Andrade Santos

/*
 * model.h  -  MODEL (MVC)
 *
 * Dados e regras do jogo. O MODEL NAO interage com o operador: toda interacao
 * com o operador (entrada e saida) fica no VIEW.
 *
 *  - O mundo e a matriz global 'matriz' (definida em model.cpp):
 *    'O' = ser vivo, '.' = vazio/morto.
 *  - 'dimensao' e o tamanho usado do mundo (10 a 60).
 *  - A lista simplesmente ligada (struct No) guarda celulas (REQ10/REQ11)
 *    e e a estrutura auxiliar usada para calcular a proxima geracao.
 */
#ifndef MODEL_H
#define MODEL_H

/* Tamanho MAXIMO da matriz (REQ01: o usuario escolhe de 10 a 60) */
#define linhas  60
#define colunas 60

#define DIM_MINIMA 10
#define DIM_MAXIMA 60

/* REQ10: no da lista simplesmente ligada (alocacao dinamica) */
typedef struct no
{
	int lin;
	int col;
	struct no *prox;
} No;

/* ---------- dados do jogo (definidos em model.cpp) ---------- */
extern char matriz[linhas][colunas];  /* o mundo */
extern int  dimensao;                 /* tamanho usado do mundo */

/* ---------- mundo ---------- */

/* REQ01/REQ05: preenche TODO o mundo com '.' (mapa vazio / limpar mapa) */
void iniciar_mundo(void);

/* REQ01: define o tamanho do mundo (10 a 60) e limpa o mapa */
void definir_dimensao(int nova_dimensao);

/* 1 se (l,c) esta dentro do mundo */
int coordenada_valida(int l, int c);

/* REQ02: consulta e altera uma celula */
int  celula_viva(int l, int c);
void criar_celula(int l, int c);
void remover_celula(int l, int c);

/* Vizinhos vivos de (l,c) - mundo plano (fora do mundo nao existe) */
int contar_vizinhos_vivos(int l, int c);

/* Total de celulas vivas no mundo */
int contar_vivas(void);

/* REQ06/REQ10: avanca UMA geracao. Retorna 1 ok, 0 se faltou memoria
   (nesse caso o mapa nao e alterado). */
int proxima_geracao(void);

/* ---------- lista ligada ---------- */
No *lista_vivas(void);            /* REQ11: celulas vivas */
No *lista_vizinhas_mortas(void);  /* REQ04/REQ11: mortas com vizinho vivo */
int  contar_lista(No *lista);
void liberar_lista(No *lista);    /* sempre liberar depois de usar */

/* ---------- arquivo ---------- */

/* REQ12: acrescenta a geracao atual ao final do arquivo. 1 ok, 0 erro. */
int salvar_geracao(const char *arquivo);

/* REQ13: carrega o registro numero 'indice' (0 = primeiro).
   Retorna 1 = carregou, 0 = nao existe esse registro, -1 = sem arquivo */
int carregar_geracao(const char *arquivo, int indice);

#endif
