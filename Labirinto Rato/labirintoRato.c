#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int **lab;
} posicao;

int alocar_labirinto(int lin, int col)
{
    int i;
    posicao matriz;

    matriz.lab=(int**)malloc(lin*sizeof(int));

    for(i=0; i<lin; i++)
    {
        matriz.lab[i]=(int*)calloc(col,sizeof(int));
    }

    return matriz.lab;
}

void imprimir_labirinto(int **lab,int lin, int col)
{
    int i, j;
    printf("\n\n\nLABIRINTO %d X %d\n\nESPACOS LIVRES '0' E PAREDES '-1'\n\n\n", lin, col);
    
    FILE *fp;
    fp = fopen("labirinto.txt","a+");
    
    srand((unsigned)time(NULL));
    for(i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
            //se mudar o numero dps do % muda o nmr de paredes
            lab[i][j]= rand() % 5;

            if(lab[i][j]>=1) //
            {
                lab[i][j]=0;
            }
            else if( lab[i][j]==0)
            {
                lab[i][j]=-1;
            }
            fprintf(fp, "%4d\n\n", lab[i][j]);
            printf("%2d ",lab[i][j]);
        }
        printf("\n");
    }

}

void posicoes_livres(int **lab, int lin, int col, int passo_linha, int passo_coluna)
{
    int i, j, quantidade_posicoes_livres=0, quantidade_de_paredes=0;
    for(i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
            if(lab[i][j]==0)
            {
                quantidade_posicoes_livres++;
            }
            else
            {
                quantidade_de_paredes++;
            }
        }
    }
    printf("\nA quantidade de posicoes livres e %d\nQuantidade de paredes e %d\n\n", quantidade_posicoes_livres,quantidade_de_paredes);
}

void calcula_passos(int **lab,int lin, int col, int i, int j)
{
    lab[i][j]=1;

    int a,b,c,k;
    c=lab[i][j];
    do
    {
        k=0;
        for (a=0; a<lin; a++)
        {
            for (b=0; b<col; b++)
            {
                if (lab[a][b]==c)
                {
                    if (a>0&&lab[a-1][b]==0)
                    {
                        lab[a-1][b]=c+1;
                        k++;
                    }
                    if (b<col-1&&lab[a][b+1]==0)
                    {
                        lab[a][b+1]=c+1;
                        k++;
                    }
                    if (a<lin-1&&lab[a+1][b]==0)
                    {
                        lab[a+1][b]=c+1;
                        k++;
                    }
                    if (b>0&&lab[a][b-1]==0)
                    {
                        lab[a][b-1]=c+1;
                        k++;
                    }
                }
            }
        }
        c++;
    }
    while(k>0);
}

void imprimir_caminho_minimo(int **lab, int lin, int col, int ir, int jr)
{
    int i, j;
    FILE *cm;
    cm = fopen("caminho_minimo.txt","a+");

    for (i=0; i<lin; i++)
    {
        for (j=0; j<col; j++)
        {
            if (lab[i][j]!=0)
            {
                fprintf(cm, "%2d\n\n", lab[i][j]);
                printf("%2.d ",lab[i][j]);
            }
            else
            {
                printf(" %d ",0);
            }
        }
        printf("\n");
    }

    if (lab[ir][jr]<=0)
    {
        printf("\nO RATO ESTA PRESO!\n");
    }
    else
    {
        printf("\nO caminho minimo ate a saida e %d\n",lab[ir][jr]);
    }
}

void libera(int **lab, int lin)
{
    int i;

    for(i=0; i<lin; i++)
    {
        free(lab[i]);
    }
    free(lab);

    printf("\nA memoria foi liberada.\n");
}

int main ( )
{
    int lin, col;
    int ratoI, ratoJ, saidaI, saidaII;
    int resp;
    posicao *matriz;
    matriz=malloc(sizeof(posicao));

    do
    {
        system("cls");
        printf("\tAJUDE O RATO A ENCONTRAR O A SAIDA!!\n\n");

        printf("Digite o numero de linhas:\n");
        scanf("%d", &lin);

        printf("Digite o numero de colunas:\n");
        scanf("%d",&col);

        printf("Digite a posicao de saida do rato (linha):\n"); // origem
        scanf ("%d", &ratoI);

        printf("Digite a posicao de saida do rato (coluna):\n"); // origem
        scanf ("%d", &ratoJ);

        printf("Digite a posicao da saida do labirinto (linha):\n"); //destino
        scanf ("%d", &saidaI);

        printf("Digite a posicao da saida do labirinto (coluna):\n"); //destino
        scanf ("%d", &saidaII);

        // Correção para não precisar usar posições 0s com o usuario
        ratoI = ratoI-1;
        ratoJ = ratoJ-1;
        saidaI = saidaI-1;
        saidaII = saidaII-1;

        matriz->lab=alocar_labirinto(lin,col); //Cria Matriz

        imprimir_labirinto(matriz->lab, lin, col); //Imprime o Labirinto e sorteia as paredes

        posicoes_livres(matriz->lab, lin, col, saidaI, saidaII); // Mostra a quantidade de posições livres e paredes

        calcula_passos(matriz->lab, lin, col, saidaI, saidaII); // Calcula os passos de todas posições possiveis até a saida

        imprimir_caminho_minimo(matriz->lab, lin, col, ratoI, ratoJ); // Imprime Labirinto com todos os caminhos e o caminho minimo até a saida

        libera(matriz->lab, lin);

        printf("Deseja ir novamente? Sim(1) Nao(0):\n");
        scanf ("%d", &resp);

    }while(resp==1);

    return 0;

}
