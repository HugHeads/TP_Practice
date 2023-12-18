#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
void all_swap(struct ALUMNO *, struct ALUMNO *);
void all_bubbleSort(struct ALUMNO  [A], unsigned);
void fprint_DATE(FILE *, DATE);
void fprint_ALUMNO (FILE *, struct ALUMNO);


int main(){

    struct ALUMNO alumnos[A], aux;
    int anyo = -1, opc = -1;
    char es[256];
    printf("generandose datos aleatorios...\n");

    srand(time(NULL));

    for (int i = 0; i < A; i++)
    {
        rand_ALUMNO(&alumnos[i]);
        print_ALUMNO(alumnos[i]);
    }
    
    printf("\n\ngenerandose fichero de texto...");
    printf("\n\ngenerandose fichero binario...");

    FILE *archivo, *bin, *ordenado;
    bin = fopen("alum.bin", "wb");
    archivo = fopen("alum.txt", "w");
    ordenado = fopen("alum_sort.txt", "w");
    
    while (anyo > 2005 || anyo < 1999){
        printf("\n\nanyo a buscar en los datos del fichero binario?  ");
        scanf("%d", &anyo);
        fflush(stdin);
    }

    for (unsigned i = 0; i < A; i++) {
        if (alumnos[i].nac.anyo == anyo) {
            fwrite(&alumnos[i], sizeof(struct ALUMNO), 1, bin);
        }
    }

    fclose(bin);

    bin = fopen("alum.bin", "rb");

    fread(&aux, sizeof(struct ALUMNO), 1, bin);
    while (!feof(bin)) {
        print_ALUMNO(aux);
        fread(&aux, sizeof(struct ALUMNO), 1, bin);
    }

    for (int i = 0; i < A; i++)
    {
        fprint_ALUMNO( archivo, alumnos[i]);
    }

    while (opc < 1 || opc > 2){
        printf("\n\ngenerar fichero de texto con datos ordenador por dni (1) o por nombre completo (2)?  ");
        scanf("%d", &opc);
        fflush(stdin);
    }

    all_bubbleSort(alumnos, opc);
    
    if (opc == 2){
        printf("\n\nnombre completo a buscar en los datos del fichero ordenado de texto?  ");
        gets(es);
    } else{
        printf("\n\ndni a buscar en los datos del fichero ordenado de texto?  ");
        gets(es);
    }

    for (int i = 0; i < A; i++)
    {   
        if (opc == 1 && strstr(alumnos[i].DNI, es) != NULL){
            fprint_ALUMNO( ordenado, alumnos[i]);
        }
        else if (strcmp(alumnos[i].nom_comp, es) == 0)
        {
            fprint_ALUMNO( ordenado, alumnos[i]);
        }
    }

    fclose(archivo);
    fclose(ordenado);
    fclose(bin);

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

void all_swap(struct ALUMNO *a, struct ALUMNO *b){
    struct ALUMNO temp = *a;
    *a = *b;
    *b = temp;
}

void all_bubbleSort(struct ALUMNO  arr[A], unsigned opc){
    if (opc == 1){
        for (unsigned i = 0; i < A - 1; i++) {
            for (unsigned j = 0; j < A - i - 1; j++) {
                if ( strcmp(arr[j].DNI, arr[j + 1].DNI) > 0) {
                    all_swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
    else{
        for (unsigned i = 0; i < A - 1; i++) {
            for (unsigned j = 0; j < A - i - 1; j++) {
                if ( strcmp(arr[j].nom_comp, arr[j + 1].nom_comp) > 0) {
                    all_swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
    
    
}

void fprint_DATE(FILE *file, DATE fecha){
    fprintf(file, "%02u/%02u/%04u", fecha.dia, fecha.mes, fecha.anyo);
}

void fprint_ALUMNO (FILE *file, struct ALUMNO alumno){
    //file = fopen("alum.txt", "a");
    fprintf(file, "%s %s ", alumno.DNI, alumno.nom_comp);
    fprint_DATE(file, alumno.nac);
    fputs("\n", file);
    
}