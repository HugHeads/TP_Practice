#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//strchr() -> buscar letra,  strstr() -> buscar substring
//getch() -> +-getchar()

#define N 100

unsigned resto_DNI(unsigned);
char letra_calculada(unsigned);
void rand_dig (char *);
void buscar_substring(char [N][9+1]);
void buscar_letra(char [N][9+1]);
void print_menu();
void print_strings_DNIs(char [N][9+1]);
void rand_strings_DNIs(char [N][9+1]);
void rand_str_DNI(char [9+1]);


int main(){
    char opc;
    char dnis[N][9+1];
    srand(time(NULL));
    rand_strings_DNIs(dnis);
    print_strings_DNIs(dnis);
    print_menu();
    do
    {
        opc = getch();
        switch (opc){
        case '1':
            buscar_letra(dnis);
            break;
        case '2':
            buscar_substring(dnis);
            break;
        default:
            break;
        }
    } while (opc != '0');
    
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
    for (int i = 0; i < 9+1; i++)
    {
        dni[i] = '\0';
    }
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

void print_menu(){
    printf("\n1 buscar letra\n2 buscar substring\n0 END");
}

void buscar_substring(char dnis[N][9+1]){
    char subcadena[10];
    printf("\n\nsubstring a buscar ? ");
    scanf("%s", subcadena);
    fflush(stdin);
    for (int i = 0; i < N; i++) {
        char *res = strstr(dnis[i], subcadena);
        if ( res != NULL) {
            printf(" > %s  ", dnis[i]);
        }
    }
}

void buscar_letra(char dnis[N][9+1]){
    char letra;
    printf("\n\nletra a buscar ? ");
    scanf("%c", &letra);
    fflush(stdin);
    for (int i = 0; i < N; i++) {
        char *res = strchr(dnis[i], letra);
        if ( res != NULL) {
            printf(" > %s  ", dnis[i]);
        }
    }
}