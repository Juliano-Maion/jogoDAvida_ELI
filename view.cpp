#include<stdio.h>
#include "model.h"
#include "view.h"
void mostrar_matriz(int dimensao, char matriz[linhas][colunas])
{
	printf("   ");
	for(int j=0;j<dimensao;j++)
		printf("%3d ",j);
	printf("\n");
	for(int i=0; i<dimensao;i++)
	{
		printf("%2d ",i);
		for(int j=0;j<dimensao;j++)
			printf("  %c ", matriz[i][j]);
		printf("\n");
	}
}

/*void mostrar_mortas(char matriz[60][60], int dimensao)
{
	for(int i=0;i<dimensao;i++)
		printf(" %3d ",i);
	printf("\n");
	for(int i=0; i<dimensao;i++)
	{
		printf("%2d ",i);
		for(int j=0;j<dimensao;j++)
			{
				if(matriz[dimensao][dimensao]=='O')
					{
						if(matriz[dimensao][dimensao-1]!='O')
							matriz[dimensao][dimensao-1]='+';
						if(matriz[dimensao][dimensao+1]!='O')
							matriz[dimensao][dimensao+1]='+';
						if(matriz[dimensao-1][dimensao]!='O')
							matriz[dimensao-1][dimensao]='+';
						if(matriz[dimensao+1][dimensao]!='O')
							matriz[dimensao+1][dimensao]='+';							
					}
				else if(matriz[dimensao][dimensao]=='.')
					printf(".");
				else if (matriz[dimensao][dimensao]!=NULL)
					printf("+");
				
			}
	}	
	
}
*/

