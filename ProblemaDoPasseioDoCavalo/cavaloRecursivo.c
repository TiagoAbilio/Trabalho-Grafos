#include <stdio.h>

#define N 5 // Tamanho do lado do tabuleiro
#define FALSE 0
#define TRUE 1

int i, j, t[N][N], a[N], b[N], tentativa = 0;
short q;

void Tenta(int i, int x, int y, short *q){
    int u, v ,ii, jj;
    int k = -1;
    tentativa++;
    short q1; // Inicializa seleção de movimentos
    for(ii = 0; ii < N; ii++){
        for(jj = 0; jj < N; jj++)
        printf( "%d ", t[ii][jj]);
        putchar('\n');
    }

    printf("\n\nTentativa: %d\n", tentativa);

    do{
        k++;
        q1 = FALSE;
        u = x + a[k ];
        v = y + b[k ];
        if(u >= 0 && u < N && v >= 0 && v < N)
            if (t [u][ v] == 0){
                t [u][ v] = i ;
                if(i < N * N) { // Tabuleiro não esta cheio
                    Tenta(i + 1, u, v, &q1) ; // Tenta novo movimento
                    if(!q1)
                    t [u][ v] = 0; // Não sucedido apaga registro anterior
                }
                else
                    q1 = TRUE;
            }
    }while(!(q1 || k == 7));
    *q = q1;
}

int main(int argc , char *argv [ ]){ // Programa principal
    int l,c;
    a[0] = 2;
    a[1] = 1;
    a[2] = -1;
    a[3] = -2;
    b[0] = 1;
    b[1] = 2;
    b[2] = 2;
    b[3] = 1;
    a[4] = -2;
    a[5] = -1;
    a[6] = 1;
    a[7] = 2;
    b[4] = -1;
    b[5] = -2;
    b[6] = -2;
    b[7] = -1;

    for(i = 0; i < N; i ++)
        for(j = 0; j < N; j++)
            t[i][j] = 0;

    printf("Digite a posicao inicial do cavalo\nlinha: ");
    scanf("%d", &l);
    printf("coluna: ");
    scanf("%d", &c);

    //t[0][0] = 1; // Escolhemos uma casa do tabuleiro
    t[l][c] = 1; // Posição escolhida

    Tenta(2, 0, 0, &q);
    if(!q){
        printf("Sem solucao\n");
        return 0;
    }

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j ++)
            printf("%d.2", t[i][j]);
       putchar('\n') ;
    }
    return 0;
}
