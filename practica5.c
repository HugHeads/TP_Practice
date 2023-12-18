#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100

unsigned resto_DNI(unsigned);
char letra_calculada(unsigned);
void rand_dig (char *);
void rand_DNI (unsigned *);
void rand_DNIs (unsigned [N], char [N]);
void print_DNIs (unsigned [N], char [N]);
void calcular_frecuencias (char [N], unsigned [26], float [26]);
void print_frecuencias (unsigned [26], float [26]);
void print_barra (float);


int main(){
    unsigned dnis[N], freq[26] = {0};
    float relativas[26] = {0.0};
    char letras[N];
    srand(time(NULL));
    rand_DNIs(dnis, letras);
    print_DNIs(dnis, letras);
    calcular_frecuencias( letras, freq, relativas);
    print_frecuencias(freq, relativas);
    return 0;
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

void rand_dig (char *dig){
    *dig = rand()%10 + '0';
}


void rand_DNI (unsigned *dni){
    char a;
    *dni = 0;
    for (int i = 0; i < 8; i++){
        rand_dig(&a);
        *dni = *dni * 10 + ((a)-48);
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


void calcular_frecuencias (char letras[N], unsigned freq[26], float relativas[26]){
    for (int i = 0; i < N; i++){
        freq[letras[i] - 'A']++;
    }
    for (int i = 0; i < 26; i++){
        relativas[i] = (float)freq[i]/N;
    }
    
}

void print_frecuencias (unsigned freq[26], float relativas[26]){
    printf("\n\n > frecuencias absolutas, relativas y diagrama de barras:\n");
    for (int i = 0; i < 26; i++){
        if (freq[i] != 0){
            printf("%c  %d %f  ", 'A'+i, freq[i], relativas[i]);
            print_barra(relativas[i]);
        }
    }
    
}

void print_barra (float relativa){
    for (int i = 0; i < (int)(relativa*100); i++){
        printf("*");
    }
    printf("\n");
}