#include<stdio.h>
void mostrar_matriz(int x, char matriz[60][60])
{

	for(int i=0;i<x;i++)
		printf(" %3d ",i);
	printf("\n");
	for(int i=0; i<x;i++)
	{
		printf("%2d ",i);
		for(int j=0;j<x;j++)
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
void escolher_troca(int dimensao, char matriz[60][60])
{
	int troca_linha;int troca_coluna;
	do
	{
		mostrar_matriz(dimensao,matriz);
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
main()
{
	int dimensao;
	printf("escolha a dimensao da matriz[10 a 60]: ");
	scanf("%d",&dimensao);
	char matriz[60][60];
	for(int i=0; i<dimensao;i++)
		for(int j=0;j<dimensao;j++)
			matriz[i][j]='.';
	escolher_troca(dimensao,matriz);
	mostrar_mortas(matriz,dimensao);
	
}
