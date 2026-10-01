#include<stdio.h>
#include "model.h"
#include "view.h"
#include "contoller.h"
int main()
{
	char matriz[linhas][colunas];
	iniciar_mundo(matriz);
	int dimensao = escolher_dimensao();
	escolher_troca(dimensao, matriz);
	return 0;
}

