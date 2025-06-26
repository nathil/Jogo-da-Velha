#include <stdio.h>
#include <stdlib.h>

//verifica se linhas, colunas e diagonais já foram selecionadas

int verifica(int *mat, int n){
    int soma_princ = 0, soma_sec = 0; 
    int* vetor_linhas = malloc(sizeof(int)*(n));
    int* vetor_colunas = malloc(sizeof(int)*(n));

    for(int i=0; i<n; i++){
        vetor_linhas[i] = 0;
        vetor_colunas[i] = 0; 
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            vetor_linhas[i] += mat[n*i+j]; //soma das linhas
            vetor_colunas[j] += mat[n*i+j]; //soma das colunas

            if(i == j) soma_princ += mat[n*i+j]; //soma da diagonal principal 
            if(i + j == n - 1) soma_sec += mat[n*i+j]; //soma da diagonal secundária 
        }
    }

    for(int i=0; i<n; i++) if(vetor_linhas[i] == 3 || vetor_linhas[i] == -3) return 1; // verificando a soma das linhas
    for(int i=0; i<n; i++) if(vetor_colunas[i] == 3 || vetor_colunas[i] == -3) return 1; // verificando a soma das colunas

    if(soma_princ == 3 || soma_princ == -3) return 1; // verificando diagonal principal
    if(soma_sec == 3 || soma_sec == -3) return 1; // verificando diagonal secundária

    return 0; 
}

//verifica se o jogo está empatado 

int empate(int *mat, int n){
    int cont = 0; 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[n*i+j] == 1 || mat[n*i+j] == -1){
                cont += 1; 
            }
        }
    }

    return cont == 9;  
}

void zera_matriz(int *mat, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            mat[n*i+j] = 0; 
        }
    }
}

int main(){
    int n=3, posicao, jogador = 1; 

    int* matriz = malloc(sizeof(int)*(n*n)); 

    zera_matriz(matriz, n); 

    while(1){

        for(int i=0; i<n; i++){
            printf("\n"); 
            for(int j=0; j<n; j++){
                printf("| %s |", matriz[n*i+j] == 0 ? " " : matriz[n*i+j] == 1 ? "X" : "O"); 
            }
        }

        if(jogador == 1){
            printf("\n\nE a vez do jogador 1!"); 
        } else{
            printf("\n\nE a vez do jogador 2!"); 
        }

        printf("\nInforme a posicao (1-9):");
        scanf("%d", &posicao); 

        posicao = posicao - 1;  

        if(posicao < 9 && posicao >= 0 && matriz[posicao] == 0){
            matriz[posicao] = jogador;
            if(verifica(matriz, n)){  
                printf("\nJogador %s Ganhou!!", jogador == 1 ? "1" : "2"); 
                break; 
            } else if(empate(matriz, n)){
                printf("\nEmpate!!"); 
                break;
            }

            jogador *= -1;

        } else {
            printf("Posicao Ocupada!");
        }
        
    }
    
    //print final
    printf("\n"); 

    for(int i=0; i<n; i++){
        printf("\n"); 
        for(int j=0; j<n; j++){
            printf("| %s |", matriz[n*i+j] == 0 ? " " : matriz[n*i+j] == 1 ? "X" : "O"); 
        }
    }
}