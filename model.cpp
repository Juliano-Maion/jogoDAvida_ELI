#include<stdio.h>
#include "model.h"
void iniciar_mundo(char matriz[linhas][colunas])
{
	for(int i=0; i<linhas;i++)
		for(int j=0;j<colunas;j++)
			matriz[i][j]='.';

}
