//acessar documento OK
//navegar e pegar informaçõpes OK
//salver informaçoes no struct 
//criar funcoes de varredura
//criar threads
//dividir tarefas entre threads
//output em arquivo especifico com resposta OK
//TESTES 2/3


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int error = 0;

typedef struct{
        int N;
        int linha;
        int coluna;
        int *matriz;
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
        printf("N: %d\nlinha: %d\ncoluna: %d\n",n,linha,coluna);
        
        int matriz[n][n];
        sudoku sdk = {n, linha, coluna, &matriz[n][n]};

        for(i=0; i < n; i++){
                for(j=0; j < n ; j++){
                        //matriz[i][j] = fgetc(in) - 48;
                        fscanf(in," %d%c",&matriz[i][j], &lixo);
                }
        }

        for(i=0; i < n; i++){
                for(j=0; j < n ; j++){
                        printf("%d ",matriz[i][j]);
                }
                printf("\n");
        }

        fclose(in);

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