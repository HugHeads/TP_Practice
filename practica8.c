#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define N 100

unsigned resto_DNI(unsigned);
char letra_calculada(unsigned);
void rand_dig (char *);
void buscar_substring(char [N][9+1]);
void buscar_letra(char [N][9+1]);
void print_strings_DNIs(char [N][9+1]);
void rand_strings_DNIs(char [N][9+1]);
void rand_str_DNI(char [9+1]);
void strings_swap(char [9+1], char [9+1]);
void strings_bubbleSort(char [N][9+1]);

int main(){
    char dnis[N][9+1];
    srand(time(NULL));
    rand_strings_DNIs(dnis);
    printf(" > DNIs (con letra) aleatorios:\n");
    print_strings_DNIs(dnis);
    strings_bubbleSort(dnis);
    printf("\n\n > DNIs (con letras) ordenador:\n");
    print_strings_DNIs(dnis);
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

void print_strings_DNIs(char dni[N][9+1]){
    for (int i = 0; i < N; i++)
    {
        printf("%s ", dni[i]);
    }
}

void rand_dig (char *dig){
    *dig = rand()%10 + '0';
}

void rand_str_DNI(char dni[9+1]){
    for (int i = 0; i < 8; i++)
    {
        rand_dig(&dni[i]);
    }
}


void rand_strings_DNIs(char dnis[N][9+1]){
    unsigned dni = 0;
    for (int i = 0; i < N; i++){
        rand_str_DNI(dnis[i]);
        for (int j = 0; j < 10; j++){
            dni = dni * 10 + (dnis[i][j]-'0');
        }
        dnis[i][8] = letra_calculada(dni);
        dnis[i][9] = '\0';
        
        dni = 0;
    }
}

void strings_swap(char prim[9+1], char sec[9+1]){
    char temp[9+1];
    memcpy(temp, prim, 9+1);
    memcpy(prim, sec, 9+1);
    memcpy(sec, temp, 9+1);
}

void strings_bubbleSort(char letra[N][9+1]){
    int ret;
    for (int j = 0; j < N-1; j++){
        for (int i = 0; i < N-j-1; i++){
            if (memcmp(letra[i], letra[i+1], 9+1) > 0)
            {
                strings_swap(letra[i], letra[i+1]);
            }
            
        }
    }
}