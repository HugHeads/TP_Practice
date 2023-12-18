#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100

unsigned resto_DNI(unsigned dni);
char letra_calculada(unsigned);
void rand_dig (int *);
void rand_DNI (unsigned *);
void rand_DNIs (unsigned [N], char [N]);
void print_DNIs (unsigned [N], char [N]);
void swap_unsigned(unsigned *, unsigned *);
void swap_char(char *, char *);
void bubbleSort(unsigned [N], char [N]);

int main(){
    unsigned dnis[N];
    char letras[N];
    srand(time(NULL));
    rand_DNIs(dnis, letras);
    printf(" > DNIs (con letra) aleatorios:\n");
    print_DNIs(dnis, letras);
    bubbleSort(dnis, letras);
    printf("\n\n > DNIs (con letras) ordenador:\n");
    print_DNIs(dnis, letras);
}

unsigned resto_DNI(unsigned dni){
    return dni - (int)(dni/23)*23;
}

char letra_calculada(unsigned dni){
    int resto = resto_DNI(dni);
    char letras[] = {
        'T','R','W','A','G','M','Y','F','P','D','X',
        'B','N','J','Z','S','Q','V','H','L','C','K','E'};
    return letras[resto];
}

void rand_dig (int *dig){
    *dig = rand()%10;
}


void rand_DNI (unsigned *dni){
    int a;
    *dni = 0;
    for (int i = 0; i < 8; i++){
        rand_dig(&a);
        *dni = *dni * 10 + a;
    }
}


void rand_DNIs (unsigned dnis[N], char letras[N]){
    for (int i = 0; i < N; i++){
        rand_DNI( &dnis[i]);
    }
    for (int i = 0; i < N; i++){
        letras[i] = letra_calculada(dnis[i]);
    }
}

void print_DNIs (unsigned dnis[N], char letras[N]){
    for (int i = 0; i < N; i++){
        printf("%d-%c  ", dnis[i], letras[i]);
    }
}

void swap_unsigned(unsigned *may, unsigned *men){
    unsigned test = *may;
    *may = *men;
    *men = test;
}

void swap_char(char *may, char *men){
    char test = *may;
    *may = *men;
    *men = test;
}

void bubbleSort(unsigned dni[N], char letra[N]){
    for (int j = 0; j < N-1; j++){
        for (int i = 0; i < N-j-1; i++){
        if (dni[i] > dni[i+1]){
            swap_char(&letra[i], &letra[i+1]);
            swap_unsigned(&dni[i], &dni[i+1]);
        }
    }
    }
}