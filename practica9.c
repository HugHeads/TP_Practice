#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define A 80

typedef struct
{
    unsigned dia, mes, anyo;
} DATE;

struct ALUMNO
{
    char DNI[9+1];
    char nom_comp[20+1];
    DATE nac;
};

const char nombre[8][10+1] = {"jose", "roberto", "fernando", "mario", 
    "sandra", "raquel", "isabel", "pilar"};
const char apellidos[8][10+1] = {"garcia", "hernandez", "gutierrez",
    "gomez", "fernandez", "lopez", "sanchez", "perez"};

unsigned resto_DNI(unsigned);
void print_DATE(DATE );
void print_ALUMNO(struct ALUMNO);
void rand_DATE(DATE *);
unsigned es_fecha_valida(DATE );
void rand_nom_comp(char [20+1]);
void rand_ALUMNO(struct ALUMNO *);
char letra_calculada(unsigned);
void rand_dig (char *);
void rand_str_DNI(char [9+1]);

int main(){

    struct ALUMNO alumnos[A];

    srand(time(NULL));

    for (int i = 0; i < A; i++)
    {
        rand_ALUMNO(&alumnos[i]);
        print_ALUMNO(alumnos[i]);
    }
    
    
    return 0;
}

void print_DATE(DATE fecha){
    printf("%u-%u-%u\n", fecha.dia, fecha.mes, fecha.anyo);
}

void print_ALUMNO(struct ALUMNO alumno){
    printf("%s  ", alumno.DNI);
    printf("%s  ", alumno.nom_comp);
    print_DATE(alumno.nac);
}

void rand_DATE(DATE *fecha){
    do{
        fecha->dia = rand() % 31 + 1;
        fecha->mes = rand() % 12 + 1;
        fecha->anyo = rand() % 6 + 1999;
    } while (es_fecha_valida(*fecha));
}

unsigned es_fecha_valida(DATE fecha){
    unsigned res = 1;
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (fecha.dia < diasMes[fecha.mes-1]){
        res = 0;
    }
    return res;
}

void rand_nom_comp(char nom[20+1]){
    sprintf( nom,"%s, %s", apellidos[rand() % 8], nombre[rand() % 8]);
}

void rand_ALUMNO(struct ALUMNO *alumno){
    rand_str_DNI(alumno->DNI);
    rand_nom_comp(alumno->nom_comp);
    rand_DATE(&(alumno->nac));
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

void rand_str_DNI(char dni[9+1]){
    unsigned a = 0;
    for (int i = 0; i < 8; i++)
    {
        rand_dig(&dni[i]);
    }
    for (int j = 0; j < 10; j++){
            a = a * 10 + (dni[j]-'0');
    }
    dni[8] = letra_calculada(a);
    dni[9] = '\0';
}