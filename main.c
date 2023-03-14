//acessar documento OK
//navegar e pegar informaçõpes OK
//salver informaçoes no struct OK
//criar funcoes de varredura
//criar threads
//dividir tarefas entre threads
//output em arquivo especifico com resposta OK
//TESTES 2/3


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *verifica_linha(void *ptr);
void *verifica_coluna(void *ptr);
void *verifica_grade(void *ptr);

int error = 0;

typedef struct{
        int N;
        int tot;
        int linha;
        int coluna;
        int qtd_grades;
        int **matriz;
}sudoku;


int main(int argc, char *argv[]){

        //printf("%s", argv[1]);
        FILE *in, *out;
        int n, linha, coluna;
        int i, j;
        char lixo, lixo1;

        if(argc != 2){
                printf("Invalid number of parameters");
                exit(1);
        }

        in = fopen(argv[1], "r");

        if (in == NULL){
                printf("Error to read file");
                exit(1);
        }

        /*
        n = fgetc(in) -48;
        fgetc(in);fgetc(in);fgetc(in);
        linha = fgetc(in) - 48;
        fgetc(in);
        coluna = fgetc(in) -48;
        fgetc(in); 
        char lixo sem & nao funcionava!!
        */

        fscanf(in," %d%c%c", &n, &lixo, &lixo1);
        fscanf(in," %d%c%d", &linha, &lixo, &coluna);
        fgetc(in);
/*
        printf("N: %d\nlinha: %d\ncoluna: %d\n",n,linha,coluna);
*/      
              
        sudoku sdk = {n, n*n, linha, coluna, (n*n)/(linha*coluna),malloc(sizeof(*sdk.matriz )*n)};

        for (i=0; i<n;i++){
                sdk.matriz[i] = malloc(sizeof(*sdk.matriz[n])*n);
        }

        for(i=0; i < n; i++){
                for(j=0; j < n ; j++){
                        //matriz[i][j] = fgetc(in) - 48;
                        fscanf(in," %d%c",&sdk.matriz[i][j], &lixo);
                }
        }
        
        fscanf(in,"%c", &lixo);
        if (lixo == EOF){

                printf("\n%d\n", lixo);
        }

        fclose(in);

/*
        printf("sdk.N: %d\nsdk.linha: %d\nsdk.coluna: %d\nsdk.total: %d\nsdk.grades: %d\n",sdk.N,sdk.linha,sdk.coluna,sdk.tot,sdk.grades);      
*/

        for(i=0; i < n; i++){
                for(j=0; j < n ; j++){
                        printf("%d ",sdk.matriz[i][j]);
                }
                printf("\n");
        }

        //inicialização de threads
        pthread_t thread_linha[n], thread_coluna[n], thread_grade[sdk.qtd_grades]; 
        
        int t_linha[n], t_coluna[n], t_grade[sdk.qtd_grades];

        //declaracao de resultado
        out = fopen("sudoku_jphc.out.txt", "w");

        if(error == 0){
                fprintf(out, "SUCCESS");
        }
        else{
                fprintf(out, "FAIL");
        }

        fclose(out);

        return 0;
}