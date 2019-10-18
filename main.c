#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include <ctype.h>

typedef struct cancion cancion;
const char *get_csv_field (char * tmp, int i);
cancion *crear_cancion (char * nombre, char *artista, char*duracion, char*album);


long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}


struct cancion{
    char*nombre;
    char *artista;
    char *duracion;
    char *album;
};


int main () {

    int op;

    Map * canciones = createMap(stringHash, stringEqual);

    do{
        printf("ELIJA UNA OPCION: \n");
        printf("       1.- Importar musica desde un archivo\n");
        printf("       2.- Exportar musica CSV\n");
        printf("       3.- Agregar album \n");
        printf("       4.- Agregar cancion \n");
        printf("       5.- Eliminar canciones de un artista \n");
        printf("       6.- Buscar cancion\n");
        printf("       7.- Buscar canciones de un artista\n");
        printf("       8.- Buscar album\n");
        printf("       9.- Salir\n");
        printf("Indique la opcion: ");
        scanf("%d", &op);
        fflush( stdin );
        printf("\n");


        if(op==1){
            FILE*fp;
            fp=fopen("canciones.csv","r");
            if(fp==NULL){
                printf("No se pudo cargar el archivo. \n");
                exit(1);
            }
            else{
                printf("Las canciones se cargaron correctamente!! \n");

                char linea[1024];

                while (fgets (linea, 1023, fp) != NULL){
                    char *nombre = get_csv_field(linea, 1);
                    char *artista = get_csv_field(linea, 2);
                    char *duracion = get_csv_field(linea, 3);
                    char *album = get_csv_field(linea, 4);
                    cancion *c = crear_cancion (nombre, artista, duracion, album);

                    insertMap(canciones, c->nombre, c);

                }
                cancion * x = firstMap(canciones);
                x = firstMap(canciones);

                while (x != NULL) {
                    printf("%s\n", x->nombre);
                    x = nextMap(canciones);
                }

                fclose(fp);
                //flag++;
            }
        }


        if (op==2){


        }

        if(op==9) break;
        printf("\n");
    }while(op!=9);

    return 0;
}


cancion *crear_cancion (char * nombre, char *artista, char*duracion, char*album){
    cancion *c = malloc(sizeof(cancion));
    c->nombre = nombre;
    c->artista = artista;
    c->duracion = duracion;
    c->album = album;
    return c;
}

const char *get_csv_field (char * tmp, int i){
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) if (!--i) return tok;
    return NULL;
}

