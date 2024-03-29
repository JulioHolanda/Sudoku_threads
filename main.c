//-lpthread 

//acessar documento OK
//navegar e pegar informaçõpes OK
//salver informaçoes no struct OK
//criar funcoes de varredura OK
//criar threads OK
//dividir tarefas entre threads OK
//output em arquivo especifico com resposta OK
//TESTES 3/3 OK
//aplicar MUTEX OK
//tratamentos de erro para malloc


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *verifica_linha(void *ptr);
void *verifica_coluna(void *ptr);
void *verifica_grade(void *ptr);

pthread_mutex_t mutex_linha = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_coluna = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_grade = PTHREAD_MUTEX_INITIALIZER;

int error_linha = 0;
int error_coluna = 0;
int error_grade = 0;

typedef struct{
        int N;
        int tot;
        int linha;
        int coluna;
        int qtd_grades;
        int **matriz;
}sudoku;

typedef struct{
        int index;
        sudoku *sudoku;
}funcionalidade;

int main(int argc, char *argv[]){

        //printf("%s", argv[1]);
        FILE *in, *out;
        int n, linha, coluna;
        int i, j;
        char lixo, lixo1;
        int lixoInt;

        if(argc != 2){
                printf("Invalid number of parameters\n");
                exit(1);
        }

        in = fopen(argv[1], "r");

        if (in == NULL){
                printf("Error to read file\n");
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

        fscanf(in," %d%c%d", &n, &lixo, &lixoInt);

        if( lixo != 'x' || n != lixoInt || n <9 || lixoInt < 9  ){
                printf("File out of format\n");
                exit(1);        
        }
                
        if (fgetc(in) != 10){

                printf("File out of format\n");
                exit(1);
        }

        //printf("%d", lixoInt);
        //printf("%d\n",fgetc(in));
        fscanf(in,"%d%c%d", &linha, &lixo, &coluna);

        if( lixo != 'x' || (linha*coluna) != n || linha ==0 ||coluna == 0 ){
                printf("File out of format\n");
                exit(1);        
        }

        if (fgetc(in) != 10){

                printf("File out of format\n");
                exit(1);
        }
        //printf("%d\n",fgetc(in));
/*
*/      
        //printf("N: %d\nlinha: %d\ncoluna: %d\n",n,linha,coluna);
              
        sudoku sdk = {n, n*n, linha, coluna, (n*n)/(linha*coluna),malloc(sizeof(*sdk.matriz )*n)};

        for (i=0; i<n;i++){
                sdk.matriz[i] = malloc(sizeof(**sdk.matriz)*n);
        }

        for(i=0; i < n; i++){
                fscanf(in," %d",&sdk.matriz[i][0]);
                if (sdk.matriz[i][0] < 1 || sdk.matriz[i][0] > n){
                        printf("File out of format\n");
                        exit(1);
                }

                for(j=1; j < n ; j++){
                        //matriz[i][j] = fgetc(in) - 48;
                        fscanf(in,"%c%d",&lixo, &sdk.matriz[i][j]);
                        if (sdk.matriz[i][j] < 1 || sdk.matriz[i][j] > n || lixo != ' '){
                                printf("File out of format\n");
                                exit(1);
                        }
                }

                if( i != (n-1) && fgetc(in) != 10){
                        printf("File out of format\n");
                        exit(1);
                }
                //printf(" %d", fgetc(in));

        }

        // ACHO ESSE PERIGOSO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        /*
        */
        if (fgetc(in) != EOF){

                printf("File out of format\n");
                exit(1);
        }
   

        fclose(in);

/*
        printf("sdk.N: %d\nsdk.linha: %d\nsdk.coluna: %d\nsdk.total: %d\nsdk.grades: %d\n",sdk.N,sdk.linha,sdk.coluna,sdk.tot,sdk.grades);      
        printf("\n");

        for(i=0; i < n; i++){
                for(j=0; j < n ; j++){
                        printf("%d ",sdk.matriz[i][j]);
                }
                printf("\n");
        }
*/

        //inicialização de threads
        pthread_t thread_linha[n], thread_coluna[n], thread_grade[sdk.qtd_grades]; 
        
        int t_linha[n], t_coluna[n], t_grade[sdk.qtd_grades];

/*
*/
        //associar funcoes as threads
        //para linhas 
        funcionalidade varre_linha[n];
        funcionalidade varre_coluna[n];
        funcionalidade varre_grade[sdk.qtd_grades];
        for (i=0; i<n; i++){
                varre_linha[i].index = i;
                varre_linha[i].sudoku = &sdk;
                t_linha[i] = pthread_create(&thread_linha[i],NULL,(void*)verifica_linha,(void *)&varre_linha[i]);
        	if(t_linha[i]){
                        fprintf(stderr, "Error -pthread_create() return code: %d\n", t_linha[i]);
                        exit(EXIT_FAILURE);
                }
                varre_coluna[i].index = i;
                varre_coluna[i].sudoku = &sdk;
                t_coluna[i] = pthread_create(&thread_coluna[i],NULL,(void*)verifica_coluna,(void *)&varre_coluna[i]);
                if(t_coluna[i]){
                        fprintf(stderr, "Error -pthread_create() return code: %d\n", t_coluna[i]);
                        exit(EXIT_FAILURE);
                }
                varre_grade[i].index = i;
                varre_grade[i].sudoku = &sdk;
                t_grade[i] = pthread_create(&thread_grade[i],NULL,(void*)verifica_grade,(void *)&varre_grade[i]);
                if(t_grade[i]){
                        fprintf(stderr, "Error -pthread_create() return code: %d\n", t_grade[i]);
                        exit(EXIT_FAILURE);
                }
        }

/*
        for (i=0; i<n; i++){
        }
        
        for (i=0; i<sdk.qtd_grades; i++){
        }
*/
        //esperando por threads
        for (i=0; i<n; i++){
                pthread_join(thread_linha[i], NULL);
                pthread_join(thread_coluna[i], NULL);
                pthread_join(thread_grade[i], NULL);
        }
/*
*/

/*
        for ( i=0 ; i < sdk.qtd_grades; i++){
        }
*/

        //declaracao de resultado
        out = fopen("sudoku_jphc.out", "w");

        if(error_linha == 0 && 
        error_coluna == 0 &&
        error_grade == 0){
                fprintf(out, "SUCCESS");
        }
        else{
                fprintf(out, "FAIL");
        }

        fclose(out);

        return 0;
}

void *verifica_linha(void *ptr){

        funcionalidade * varre_linha;
        varre_linha = (funcionalidade *) ptr;

        int avaliado, procurando;
        int error = 0;
        int linha = varre_linha->index;

        for (int i = 0; i < (varre_linha->sudoku->N)-1; i++){ //avaliado vai do ultimo ao penultimo
                for (int j= i+1; j < varre_linha->sudoku->N ; j++ ){ //começando seguinte ao avaliado ate os fim
                        if( varre_linha->sudoku->matriz[linha][i] == varre_linha->sudoku->matriz[linha][j]){
                                pthread_mutex_lock(&mutex_linha);
                                error_linha += 1;
                                pthread_mutex_unlock(&mutex_linha);
                        }
                }
        }

        return NULL;
}

void *verifica_coluna(void *ptr){

        funcionalidade *varre_coluna;
        varre_coluna = (funcionalidade*) ptr;

        int coluna = varre_coluna->index;

        for (int i = 0; i < (varre_coluna->sudoku->N)-1; i++){ 
                for (int j= i+1; j < varre_coluna->sudoku->N ; j++ ){ 
                        if( varre_coluna->sudoku->matriz[i][coluna] == varre_coluna->sudoku->matriz[j][coluna]){
                                pthread_mutex_lock(&mutex_coluna);
                                error_coluna += 1;
                                pthread_mutex_unlock(&mutex_coluna);
                        }
                }
        }

        return NULL;
}

void *verifica_grade(void *ptr){

        funcionalidade *varre_grade;
        varre_grade = (funcionalidade *) ptr;

        int repete = 0;
        
        int grade = varre_grade->index;
        int x = varre_grade->sudoku->coluna;
        int y = varre_grade->sudoku->linha;

        int qtd_grades = varre_grade->sudoku->qtd_grades;
        int i_inicial = ((grade * varre_grade->sudoku->coluna) / varre_grade->sudoku->N) * varre_grade->sudoku->linha;
        int j_inicial = (grade * varre_grade->sudoku->coluna) % varre_grade->sudoku->N;

        for ( int m = i_inicial ; m < i_inicial + y ; m++){        
                for(int n = j_inicial ; n<j_inicial+ x ; n++){       
                        for (int i = i_inicial; i< i_inicial+y ; i++){
                                for (int j = j_inicial; j<j_inicial+x; j++){
                                        if (varre_grade->sudoku->matriz[m][n] == varre_grade->sudoku->matriz[i][j]){
                                                repete++;
                                        }
                                }
                        }
                }
        }
/*
        printf("\n[%d] [%d]", i_inicial, j_inicial);
        printf("\nREPETE: %d", repete);
*/        
        if ( repete != varre_grade->sudoku->N ){
                pthread_mutex_lock(&mutex_grade);
                error_grade += 1;
                pthread_mutex_unlock(&mutex_grade);
        }

        return NULL;
}