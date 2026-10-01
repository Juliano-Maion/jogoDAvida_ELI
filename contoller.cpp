#include<stdio.h>
#include "model.h"
#include "view.h"
#include "contoller.h"
void escolher_troca(int dimensao,char matriz[linhas][colunas])
{
	int troca_linha;int troca_coluna;
	do
	{
		mostrar_matriz(dimensao, matriz);
		printf("escolha as cordenadas(-1 para sair)[linha,coluna]: ");
		scanf("%d,%d",&troca_linha,&troca_coluna);
		if(troca_linha!=-1 && (troca_coluna>=0 && troca_coluna<dimensao) && (troca_linha>=0 && troca_linha<dimensao))
		{
		if(matriz[troca_linha][troca_coluna] == 'O')
			matriz[troca_linha][troca_coluna] = '.';
		else
			matriz[troca_linha][troca_coluna] = 'O';
		}
	}while(troca_linha!=-1);
}
int escolher_dimensao()
{
	int dimensao;
	printf("escolha a dimensao da matriz[10 a 60]: ");
	scanf("%d",&dimensao);
	if(dimensao<10 || dimensao>60)
	{
		printf("dimensao invalida\n");
		return escolher_dimensao();
	}
	return dimensao;
}
