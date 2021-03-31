#include<stdio.h>
#include<stdlib.h>

typedef struct posicoes{ // Estrutura para representar todas as posições das jogadas feitas
    int linha, coluna, jogada;
}posicoes;

typedef struct valorpasso{ // Estrutura para guardar os dados dos 8 passos possíveis
    int a, b;
}valorpasso;

void inicializa(int colunas, int linhas, int **vet){ // Função que inicializa todos valores de vet em -1
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            vet[i][j] = -1;
        }
    }
}

// Função que inicializa todos valores das 8 posições de valor, referentes a cada passo possível
void inicializavalor(valorpasso *valor){
    valor[0].a = -1;
    valor[0].b = 2;
    valor[1].a = -2;
    valor[1].b = 1;
    valor[2].a = -2;
    valor[2].b = -1;
    valor[3].a = -1;
    valor[3].b = -2;
    valor[4].a = 1;
    valor[4].b = -2;
    valor[5].a = 2;
    valor[5].b = -1;
    valor[6].a = 2;
    valor[6].b = 1;
    valor[7].a = 1;
    valor[7].b = 2;
}

// Função que imprime toda matriz de vet na tela e também no arquivo cavalo.txt
void imprime(int linhas, int colunas, int **vet, int tentativas){
    int i, j;
    FILE *fp;

    fp = fopen("cavalo.txt", "a+");
    printf("Tentativa : %d\n\n", tentativas);

    if(fp == NULL){
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    fprintf(fp, "\nTentativa: %d\n\n", tentativas);
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            printf("%4d", vet[i][j]);
            fprintf(fp,"%4d", vet[i][j]);
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// Função que testa se determinada jogada é possível a partir de um local, se sim a executa e retorna 1 se não retorna 0
int teste(int colunas, int linhas, int x, int y, posicoes *vista, int *pp, int passo, int **vet){
    if ((x > -1) && (x < linhas) && (y > -1) && (y < colunas)){
        if (vet[x][y] == - 1){
            *pp = *pp + 1;
            vet[x][y] = *pp;
            vista[*pp].linha = x;
            vista[*pp].coluna = y;
            vista[*pp].jogada = passo;
            return 1;
        }
    }
    return 0;
}

// Função que prepara as informações necessárias para executar uma jogada, sendo que faz para as 8 jogadas possíveis e ainda a de volta
void jogadas(int colunas, int linhas, posicoes *vista, int *pp, int **vet, int *passoaux, valorpasso *passo){
    int x, y;

    do{
        x = vista[*pp].linha + passo[*passoaux].a;
        y = vista[*pp].coluna + passo[*passoaux].b;
        if(teste(colunas, linhas, x, y, vista, pp, *passoaux, vet)){
            printf("\n\n Passo %d", *passoaux + 1);
            *passoaux = 0;
            return;
        }
        *passoaux = *passoaux + 1;
    }while(*passoaux < 8);

    if (*pp > 0){
        vet[vista[*pp].linha][vista[*pp].coluna] = -1;
        *passoaux = vista[*pp].jogada + 1;
    }

    printf("\n\nNenhum movimento foi possivel\n");
    *pp = *pp - 1;
}

int main(){ // Função principal
    FILE *fp;
    int **vet;
    valorpasso passo[8];
    posicoes *vista;
    int linhas, colunas, tam, i, j, pp, passoaux;
    long int tentativas = 0;
    pp = passoaux = 0;

    printf("\t\tImplementacao do passeio do cavalo iterativo %c\n\n", 1);
    printf("Digite o tamanho do tabuleiro\n\n");

    do { // Obtendo a quantidade de linhas e colunas do tabuleiro
        printf("Linhas: ");
        scanf("%d", &linhas);
        printf("Colunas: ");
        scanf("%d", &colunas);
        if ((linhas < 1) || (colunas < 1))
            printf ("\nTabuleiro invalido!\n\nDigite um novo tamanho para o tabuleiro\n\n");
   }while((linhas < 1) || (colunas < 1));

    tam = linhas * colunas;
    vista = (posicoes *) malloc (tam * sizeof(posicoes)); // Alocação de vista para guardar todas as informações das jogadas efetuadas
    if(vista == NULL) {
        printf ("Erro: Memoria Insuficiente!");
        exit(1);
    }

    //Alocação da matriz vet
    vet = (int **) malloc (linhas * sizeof(int *));
    if(vet == NULL) {
        printf ("Erro: Memoria Insuficiente!");
        exit(1);
    }
    for( i = 0; i < linhas; i++){
        vet[i] = (int *) malloc (colunas * sizeof(int));
        if(vet[i] == NULL){
            printf("Erro: Memoria Insuficiente!");
            exit(1);
        }
    }

    inicializa(colunas, linhas, vet); // Inicializa toda matriz vet com - 1

    printf("\nDigite a posicao inicial do cavalo\n\n");
    do{ // Obtendo a linha e a coluna inicial
        printf("Linha: ");
        scanf("%d", &i);
        printf("Coluna: ");
        scanf("%d", &j);
        if((i < 1) || (j < 1) || (i > linhas-1) || (j > colunas-1)){
            printf("\nPosicoes invalidas!\n\nDigite uma nova posicao inicial do cavalo\n\n");
        }
    }while((i < 1) || (j < 1) || (i > linhas-1)|| (j > colunas-1));

    fp = fopen("cavalo.txt", "w"); // Cria arquivo cavalo.txt
    if(fp == NULL){
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    fclose(fp);

    inicializavalor(passo); // Inicializa todos valores referentes a cada passo
    i--; // Índice do vetor começa com zero
    j--;
    vet[i][j] = 0; // Marca posição inicial do cavalo
    vista[0].linha = i;
    vista[0].coluna = j;
    imprime(linhas, colunas, vet, tentativas);

    printf("\nPressione qualquer tecla para continuar....");
    getchar();

    tam--;
    do{ // Laço que efetua chamadas a jogadas e as imprime enquanto for necessário
        tentativas++;
        jogadas(colunas, linhas, vista, &pp, vet, &passoaux, passo);
        imprime(linhas, colunas, vet, tentativas);
    }while((pp < tam) && (pp > 0));

    fp = fopen("cavalo.txt", "a+"); // Abre arquivo para adicionar mais dados
    if(fp == NULL){
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    if(pp == tam){ // Imprime na tela e no arquivo se foi ou não possível uma solução
        printf("\n\nSolucao possivel %c!\n\n", 1);
        fprintf(fp, "\n\nSolucao possivel!\n\n");
    }else{
        printf("\n\nSolucao impossivel!\n\n");
        fprintf(fp, "\n\nSolucao impossivel!\n\n");
    }
    fclose(fp); // Fecha o arquivo

    // Liberando todos ponteiros alocados
    for(i=0; i < linhas; i++){
        free(vet[i]);
    }
    free(vet);
    free(vista);

    printf("\nPressione qualquer tecla para terminar a execucao do programa...");
    getchar();
    return 0;
}
