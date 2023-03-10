//acessar documento
//navegar e pegar informaçõpes
//salver informaçoes no struct
//criar threads
//dividir tarefas entre threads
//criar funcoes de varredura
//output em arquivo especifico com resposta
//TESTES


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
        int N;
        int linha;
        int coluna;
        int *matriz;
}sudoku;

int main(int argc, char *argv[]){

        //printf("%s", argv[1]);
        FILE *in, *out;
        char *N, linha, coluna;


        in = fopen(argv[1], "r");

        /*
        fscanf(in,"%c",N);

        printf("%d",*N);
        */

        fclose(in);

        out = fopen("sudoku_jphc.out.txt", "w");

        fprintf(out, "SUCCESS");

        fclose(out);


        return 0;
}