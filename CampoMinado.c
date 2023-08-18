#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
/*
    -MinesWeeper's game
    -Jogo Campo Minado
*/

//Variáveis globais
int taml=20, tamc=20, bomb = 50, l, c, perdeu = 0, z;

typedef struct{
    int bvizinhos;
    int ehbomba;
    int estaaberto;
    int numero;
}mk;

mk jogo[20][20];
//Colocar valores 
void iniciar(){
     for(l=0;l<taml;l++){
        for(c=0;c<tamc;c++){
            jogo[l][c].numero = 0;
            jogo[l][c].estaaberto = 0;
            jogo[l][c].ehbomba = 0;
            jogo[l][c].bvizinhos = 0;
        }
    }
}
//Imprimir o tabuleiro
void imprimir(){
    printf("  # ");
    for(z=0;z<10;z++){
        printf("  %2d  ", z);
    }
    for(z=10;z<taml;z++){
        printf("  %2d  ", z);
        if(z==19){
            printf(" ");
        }
    }
    printf("\n");
    printf("    ");
    for(z=0;z<20;z++){
        printf("------");
    }
    printf("-");
    printf("\n");
    for(l=0;l<20;l++){
        printf("%2d", l);
        printf("  |");
        for(c=0;c<20;c++){
            if(jogo[l][c].numero == 157 && jogo[l][c].estaaberto == 1)
                printf("  %c  ", jogo[l][c].numero);
            else if (jogo[l][c].numero != 157 && jogo[l][c].estaaberto == 1)
                printf(" %2d  ", jogo[l][c].numero);
            else{
                printf("     ");
            }
            printf("|");
        }
        printf("\n");
        printf("    ");
        for(z=0;z<20;z++){
            printf("------");
        }
        printf("-");
    printf("\n");
    }
    
}
// Gerar bombas
void geradorbomba(){
    srand(time(NULL));
    int ta[bomb], y = (taml) * (tamc), x = 1, i = 0;
    for(l=0;l<bomb;l++){
        do{
        ta[l] = 1 + rand() % y;
        }while(ta[l] == ta[l-1]);
    }
    for(l=0;l<taml;l++){
        for(c=0;c<tamc;c++){
            for(i=0;i<bomb;i++){
                if(ta[i] == x){
                    jogo[l][c].numero = 157;
                    jogo[l][c].ehbomba = 1;
                }
            }
            x++;
        }
        x++;
    }
}
// Colocar os números de quem está perto da bomba
void putin(){
    int x, y;
    for(l=0;l<taml;l++){
        for(c=0;c<tamc;c++){
            for(x=l-1;x<=l+1;x++){
                for(y=c-1;y<=c+1;y++){
                    if(jogo[x][y].numero == 157 && jogo[l][c].numero != 157 && x>= 0 &&
                     x<taml && y>=0 && y<tamc){
                        jogo[l][c].numero = jogo[l][c].numero + 1;
                    }
                    jogo[l][c].bvizinhos = jogo[l][c].numero;
                }
            }  
        }
    }
}
// Abrir
void en(int x, int y){
    jogo[x][y].estaaberto = 1;  
    if(jogo[x][y].bvizinhos == 0 ){
        if(validar(x-1, y-1) == 1)
            en(x-1, y-1);
        if(validar(x-1, y) == 1)    
            en(x-1, y);
        if(validar(x-1, y+1) == 1)
            en(x-1, y+1);
        if(validar(x, y-1) == 1)
            en(x, y-1);
        if(validar(x, y+1) == 1)
            en(x, y+1);
        if(validar(x+1, y-1) == 1)
            en(x+1, y-1);
        if(validar(x+1, y) == 1)
            en(x+1, y);
        if(validar(x+1, y+1) == 1)
            en(x+1, y+1);
    }
}
// Verificar se as coordenadas estão certas
int validar(int x, int y){
    if(x>=0 && x < taml && y>= 0 && y<tamc && jogo[x][y].estaaberto == 0){
        return 1;
    }
    else{
        return 0;
    }
}
// Pedir as coordenadas
void pegar(){
    int k, m;
    do{
    printf("\tDigite a linha e a coluna(write the Bearings): ");
    scanf("%d%d", &k, &m);
    if(validar(k, m) == 0){
        printf("\tDigite novamente(Invalid bearings)! ");
    }
    }while(validar(k, m) == 0);
    if(jogo[k][m].ehbomba == 1){
        perdeu = 1;
    }
    en(k, m);
}
//Verificar a vitória
int  victory(){
    int cont = 0;
     for(l=0;l<taml;l++){
        for(c=0;c<tamc;c++){
            if(jogo[l][c].ehbomba == 1 && jogo[l][c].estaaberto == 0){
                cont++;
            }
        }
    }
    if(cont == bomb){
        return 1;
    }
    else{
        return 0;
    }
}
// Jogar
void play(){
    do{
    pegar();
    printf("\n\n");
    imprimir();
    printf("\n");
    if(perdeu == 1){
        printf("\n\tVc perdeu!(You have lost!!)");
    }
    else if(victory() == 1){
        printf("\n\tVc Ganhou!(Win!!!) ");
    }
    printf("\n\n\n");
    }while(victory() == 0 && perdeu == 0);
}

int main (){
    int aux;
    printf("\n\n\t\tMade by Owlbertoh\n\n");
    do{
    perdeu = 0;
    iniciar();
    geradorbomba();
    putin();
    imprimir();
    printf("\n\n");
    //Começar o jogo
    play();
    printf("\n\tDigite 1 para jogar novamente: ");
    scanf("%d", &aux);
    }while(aux == 1);
    return 0;
}
