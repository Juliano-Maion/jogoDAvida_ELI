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
		printf("escolha as cordenadas(-1 para sair): ");
		if(troca_linha!=-1)
		{
		scanf("%d,%d",&troca_linha,&troca_coluna);
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
	return dimensao;
}
