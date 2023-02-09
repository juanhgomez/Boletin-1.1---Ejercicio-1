#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define N_TEMAS 30
#define N_ASIGNATURAS 44
#define N_GRADOS 20

int contAsignaturas = 0;

typedef struct t_temas
{
    char clave[3]; /* Clave de maximo 2 letras (clave de la asignatura) */
    int numeroTema; /* Numero del 1 al 30 */
    char identificador[6]; /* Id maximo 5 caracteres (XX_00) */
    char titulo[81]; /* Maximo 80 caracteres */
    char descripcion[81]; /* Maximo 80 caracteres */
    char fechaAlta[11]; /* Maximo 10 caracteres (00/00/0000) */
    char profesor[41]; /* Maximo 40 caracteres */
};

typedef struct t_asignaturas
{
    int numero; /* Numero del 1 al 44 */
    char clave[3]; /* Clave de maximo 2 letras */
    char nombre[31]; /* Nombre de una asignatura maximo 30 caracteres */
    char descripcion[81]; /* La descripcion maxima de una asignatura es de 80 caracteres */
    struct t_temas tema[N_TEMAS]; /* El numero maximo de temas por asignatura es 30 */
};

typedef struct t_grados{
    int numero; // Para tener un identificador de su posicion en el struct
    char id[3]; // Clave del grado de maximo 2 letras
    char titulo[81]; // Nombre del titulo del grado maximo 80 caracteres
    struct t_asignaturas asignatura[N_ASIGNATURAS]; /* Hasta un maximo de 44 asignaturas */
    int plazas;
};

struct t_grados grado[N_GRADOS];

void inicializar_grados(){
    for(int i=0; i<N_GRADOS; i++)
    {
        grado[i].numero = i+1;
        strcpy(grado[i].id, "0");
        strcpy(grado[i].titulo, "vacio");
        grado[i].plazas = 0;
    }
}

void imprimir_grados(){
    int contador = 0;

    for(int i=0; i<N_GRADOS; i++){ /* Desde 1 a 44 dejando la posicion 0 sin utilizar */
        if(strcmp(grado[i].id, "0") != 0) /* Solo imprime si la asignatura tiene clave distinta de 0 */
        {
            contador++; /* En caso de ser 0 indica que no existen asignaturas en el registro */
        }
    }
    if (contador == 0)
    {
        printf("\tNUMERO\tCLAVE\tPLAZAS\tTITULO\n\n");
        printf("\t\tNo hay ninguna asignatura en el registro\n\n\n");

        system("pause");
        menuPpal();
        return 0;
    }
    else if(contador != 0) /* En caso de ser distinto de cero imprime la lista con las asignaturas disponibles */
    {
        printf("\tNUMERO\tCLAVE\tPLAZAS\tTITULO\n\n");
        for(int i=0; i<N_ASIGNATURAS; i++)
        {
            if(strcmp(grado[i].id, "0") != 0)
            {
                printf("\t%-2d\t%-2s\t%-30s\t\t%-80s\n", grado[i].numero, grado[i].id, grado[i].plazas, grado[i].titulo);
            }
        }
    }
    printf("\n");

}
/* Funcion que inicializa las asignaturas con los valores "i", "0", "vacio", "vacio" */
void inicializarAsignaturas()
{
    for(int j=0; j<N_GRADOS; j++){
        for(int i=0; i<N_ASIGNATURAS; i++)
        {
            grado[j].asignatura[i].numero = i+1; // i+1 para que me almacene el [0] con el numero 1
            strcpy(grado[j].asignatura[i].clave, "0");
            strcpy(grado[j].asignatura[i].nombre, "vacio");
            strcpy(grado[j].asignatura[i].descripcion, "vacio");
        }
    }
}

/* Funcion que imprime la lista de asignaturas existentes */
void imprimirAsignaturas(){
    int contador = 0;

    for(int j=0; j<N_GRADOS; j++){
        for(int i=0; i<N_ASIGNATURAS; i++){ /* Desde 1 a 44 dejando la posicion 0 sin utilizar */
            if(strcmp(grado[j].asignatura[i].clave, "0") != 0) /* Solo imprime si la asignatura tiene clave distinta de 0 */
            {
                contador++; /* En caso de ser 0 indica que no existen asignaturas en el registro */
            }
        }
    }

    if (contador == 0)
    {
        printf("\tGRADO\tNUMERO\tCLAVE\tNOMBRE\t\t\t\t\tDESCRIPCION\n\n");
        printf("\t\tNo hay ninguna asignatura en el registro\n\n\n");

        system("pause");
        menuPpal();
        return 0;

    }
    else if(contador != 0) /* En caso de ser distinto de cero imprime la lista con las asignaturas disponibles */
    {
        printf("\tGRADO\tNUMERO\tCLAVE\tNOMBRE\t\t\t\t\tDESCRIPCION\n\n");
        for(int j=0; j<N_GRADOS; j++){
            for(int i=0; i<N_ASIGNATURAS; i++)
            {
                if(strcmp(grado[j].asignatura[i].clave, "0") != 0)
                {
                    printf("\t%-2s\t%-2d\t%-2s\t%-30s\t\t%-80s\n", grado[j].id, grado[j].asignatura[i].numero, grado[j].asignatura[i].clave, grado[j].asignatura[i].nombre, grado[j].asignatura[i].descripcion);
                }
            }
        }
    }
    printf("\n");
}

/* Funcion que inicializa los temas con los valores que se pueden ver */
void inicializarTemas()
{
    for(int k=0; k<N_GRADOS; k++){
        for(int j=0; j<N_ASIGNATURAS; j++){
            for(int i=0; i<N_TEMAS; i++)
            {
                strcpy(grado[k].asignatura[j].tema[i].clave, "0");
                grado[k].asignatura[j].tema[i].numeroTema = j+1;
                strcpy(grado[k].asignatura[j].tema[i].identificador, "vacio");
                strcpy(grado[k].asignatura[j].tema[i].titulo, "vacio");
                strcpy(grado[k].asignatura[j].tema[i].descripcion, "vacio");
                strcpy(grado[k].asignatura[j].tema[i].fechaAlta, "00/00/0000");
                strcpy(grado[k].asignatura[j].tema[i].profesor, "vacio");
            }
        }
    }
}

/* Funcion que imprime los temas existentes */
void imprimirTemas()
{
    int contadorTemas = 0; /* Indica lo mismo que el contador de asignaturas */
    printf("\tCLAVE\tTEMA\tID\tFECHA ALTA\tPROFESOR\n\n");
    for(int k=0; k<N_GRADOS; k++){
        for(int j=0; j<N_ASIGNATURAS; j++){
            for(int i=0; i<N_TEMAS; i++)
            {
                if(strcmp(grado[k].asignatura[j].tema[i].clave, "0") != 0)
                {
                    printf("\t%-2s\t%-2d\t%-5s\t%-10s\t%-40s\n", grado[k].asignatura[j].tema[i].clave, grado[k].asignatura[j].tema[i].numeroTema, grado[k].asignatura[j].tema[i].identificador, grado[k].asignatura[j].tema[i].fechaAlta, grado[k].asignatura[j].tema[i].profesor);
                    printf("\n\t\tTITULO: %-80s\n", grado[k].asignatura[j].tema[i].titulo);
                    printf("\t\tDESCRIPCION: %-80s\n\n\n", grado[k].asignatura[j].tema[i].descripcion);
                    contadorTemas++;
                }
            }
        }
    }
    if(contadorTemas == 0)
    {
        printf("\t\tNo existe ningun tema para esta asignatura\n\n\n");

        system("pause");
        menuPpal();
        return 0;    }
}

/* Funcion que imprime la cabecera */
void cabecera()
{
    printf("\t******************************\n");
    printf("\t**   GRADO EN INFORMATICA   **\n");
    printf("\t**   --------------------   **\n");
    printf("\t** BASE DE DATOS DE APUNTES **\n");
    printf("\t******************************\n\n\n");
}

/* Funcion que imprime la despedida */
void despedida()
{
    system("cls");

    printf("\t******************************\n");
    printf("\t**   CERRANDO EL PROGRAMA   **\n");
    printf("\t**   --------------------   **\n");
    printf("\t**   HASTA LA PROXIMA! :D   **\n");
    printf("\t******************************\n\n\n");

    system("pause");
    printf("\n\n");
    return 0;
}


void menuInicial(){
    int opcion = 0;

    while (isdigit(opcion) != 1 && (opcion <=0 || opcion > 3)) /* Para que no acepte valores distintos de numeros 1 al 6 */
    {
        system("cls");
        cabecera();

        printf("/****** MENU INICIAL *******/\n\n");

        printf("    QUE ACCION DESEA REALIIZAR?\n");
        printf("\t1. Introducir/Eliminar datos manualmente\n");
        printf("\t2. Introducir/Eliminar datos a traves de ficheros\n");
        printf("\t3. Salir\n");
        
        scanf(" %d", &opcion);
        fflush(stdin);

        switch(opcion)
        {
        case 1:
            menuPpal();
            return 0;
            break;
        case 2:
            return 0;
            break;
        case 3:
            despedida();
            system("pause");
            return 0;
            break;
        }
    }
}

/* Funcion que abre el menu principal */
void menuPpal()
{
    int opcion = 0;

    while (isdigit(opcion) != 1 && (opcion <=0 || opcion > 8)) /* Para que no acepte valores distintos de numeros 1 al 6 */
    {
        system("cls");
        cabecera();

        printf("/****** MENU MANUAL *******/\n\n");

        printf("    QUE ACCION DESEA REALIIZAR?\n");
        printf("\t1. Alta de un nuevo grado\n");
        printf("\t2. Baja de un grado existente\n");
        printf("\t3. Alta de una nueva asignatura\n");
        printf("\t4. Baja de una asignatura existente\n");
        printf("\t5. Aniadir un tema de una asignatura\n");
        printf("\t6. Eliminar un tema de una asignatura\n");
        printf("\t7. Mostrar un listado del registro\n");
        printf("\t8. Volver al menu inicial\n");
        
        scanf(" %d", &opcion);
        fflush(stdin);

        switch(opcion)
        {
        case 1:
            altaGrado();
            break;
        case 2:
            bajaGrado();
            break;
        case 3:
            altaAsignatura();
            return 0;
            break;
        case 4:
            bajaAsignatura();
            return 0;
            break;
        case 5:
            nuevoTema();
            return 0;
            break;
        case 6:
            eliminarTema();
            return 0;
            break;
        case 7:
            listadoRegistro();
            return 0;
            break;
        case 8:
            menuInicial();
            return 0;
            break;
        }
    }
}

/* Funcion que comprueba si existe un \n tras hacer un fgets, y en caso afirmativo que lo cambie por \0 */
char comprobarSaltoLinea(char variable[])
{
    /* El siguiente codigo lo introduzco porque al utilizar fgets me estaba cogiendo un \n que me hacia un salto de linea en el mensaje */
    int len=0;
    // obtengo la longitud del vector variable[]
    len = strlen(variable);
    // verifico si el ultimo caracter es un salto de linea
    if (variable[len-1] == '\n')
    {
        // en caso de ser un salto de linea lo cambio por el caracter fin de cadena
        variable[len-1] = '\0';
    }
    return variable;
}

/* Funcion que cambia un string en minusculas a letras en mayusculas */
char mayusculas(char variable[])
{
    for(int i=0; i<2; i++)
    {
        variable[i] = toupper(variable[i]);
    }
    return variable;
}

/*
int numero; // Para tener un identificador de su posicion en el struct
    char id[3]; // Clave del grado de maximo 2 letras
    char titulo[81]; // Nombre del titulo del grado maximo 80 caracteres
    struct t_asignaturas asignatura[N_ASIGNATURAS]; // Hasta un maximo de 44 asignaturas
    int plazas;
*/

void altaGrado(){
    int numGrado;
    char idGrado[3]; // por simplicidad el id del grado podra ser cualquier caracter (max. 2)
    char tituloGrado[81];
    int plazasGrado;

    char opcion = ' ';

    do{
        printf("Introduzca el numero de registro donde se almacenara el nuevo grado (1/20): ");
        scanf("%d", &numGrado);
    }while((numGrado <= 0 || numGrado > 20) && isdigit(numGrado) != 1);

    printf("Introduzca el ID que quiere que se asigne al nuevo grado (max. 2 caracteres): ");
    fgets(idGrado, (sizeof(idGrado)/sizeof(char)), stdin);
    fflush(stdin);

    do{
        printf("Introduzca el numero de plazas que tendra el nuevo grado: ");
        scanf("%d", &plazasGrado);
    }while(plazasGrado <= 0); // aqui he considerado que el numero de plazas tiene que ser positivo

    printf("Introduzca el nombre del nuevo grado: ");
    fgets(tituloGrado, (sizeof(tituloGrado)/sizeof(char)), stdin);
    fflush(stdin);

    printf("Quiere confirmar el alta (S/N)? ");
    scanf("%c", &opcion);
    opcion = toupper(opcion);
    fflush(stdin);

    switch(opcion){
        case 'S':
            grado[numGrado-1].numero = numGrado;
            strcpy(grado[numGrado-1].id, idGrado);
            strcpy(grado[numGrado-1].titulo, tituloGrado);
            grado[numGrado-1].plazas = plazasGrado;
            printf("Grado registrado con exito!\n\n");
            system("pause");
            menuPpal();
            return 0;
            break;
        case 'N':
            menuPpal();
            return 0;
            break;
    }
}

void bajaGrado(){
    char idGrado[3];
    char opcion = ' ';

    printf("Introduzca la clave del grado que desea eliminar del sistema: ");
    scanf("%s", &idGrado);
    fflush(stdin);

    printf("Con la eliminacion de este grado se procedera al borrado de todas sus asignaturas y los temas correspondientes.\n");
    printf("Esta segundo de querer eliminar todos los datos (S/N): ");
    scanf("%c", &opcion);
    fflush(stdin);

    switch(opcion){
        case 'S':
            break;
        case 'N':
            printf("Los datos no han sido eliminados.\n\n");
            system("pause");
            menuPpal();
            break;
    }
}

/* Funcion para introducir una nueva asignatura en el sistema */
void altaAsignatura()
{
    int numReg = 0;
    char clave[100]; // Le pongo una cifra alta para que no sobrecargar el buffer, pero luego lo limito a 2 caracteres
    char opcion = ' ';
    char nombre[31];
    char descripcion[81];
    int contador = 0;
    int noEsLetra = 0;
    int numTemas = 0;
    int numGrado = 0;

    system("cls");
    cabecera();

    printf("/****** ALTA DE UNA NUEVA ASIGNATURA EN EL SISTEMA ******/\n\n");

    printf("\tATENCION! Esta operacion puede sobreescribir datos existentes.\n\n");
    printf("    Introduzca la siguiente informacion:\n");

    printf("Numero de registro del grado al que pertenece (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    do
    {
        contador = 0;
        printf("\t  Numero de registro de la asignatura (1/44): ");
        scanf(" %d", &numReg);
        fflush(stdin);
    }
    while(isdigit(numReg) != 1 && (numReg <= 0 || numReg > 44)); /* Para que solo acepte numeros del 1 al 44 */

    if(strcmp(grado[numGrado-1].asignatura[numReg-1].clave, "0") != 0) /* Comprueba si ya existe una asignatura en ese numero de registro */
    {
        printf("\n\t\tYa existe una asignatura con ese numero\n");


        while(opcion != 'S' && opcion != 'N') /* En caso afirmativo, pide si se desea sobreescribir los datos */
        {
            printf("\t\tDesea sobreescribir los datos (S/N): ");
            scanf(" %c", &opcion);
            opcion = toupper(opcion);
            fflush(stdin);

            switch(opcion)
            {
            case 'S': /* Si se elige SI se borran los datos de los temas asociados a la asignatura */
                for(int t=0; t<30; t++)
                {
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].clave, "0");
                    grado[numGrado-1].asignatura[numReg-1].tema[t].numeroTema = t+1;
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].identificador, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].titulo, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].descripcion, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].fechaAlta, "00/00/0000");
                    strcpy(grado[numGrado-1].asignatura[numReg-1].tema[t].profesor, "vacio");
                }
                break;
            case 'N': /* Si se elige NO se vuelve al menu principal sin borrar los datos */
                printf("\n\n\t\tLa asignatura no ha sido registrada\n\n\n");
                system("pause");
                menuPpal();
                return 0;
                break;
            }
        }
    }

    printf("\n");

    /* En caso de haber seleccionado SI se continua sobreescribiendo la asignatura */

    do
    {
        contador = 0;
        noEsLetra = 0;

        do{
            printf("\t  Clave (max. 2 letras): ");
            scanf("%s", &clave); // ERROR CORREGIDO del anterior codigo en el que usaba fgets y funcionaba pero era menos "preciso"
                                // Ahora si se le introducen mas de 2 letras pide introducir la clave de nuevo
                                // Con fgets si se introducian mas de 2 letras solo guardaba dos, pero seguia el proceso sin avisar
            mayusculas(clave);
            fflush(stdin);
        }while(strlen(clave) > 2 || strcmp(clave, "0") == 0);

        for(int j=0; j<2; j++)
        {
            if(isalpha(clave[j]) == 0 && clave[j] != '\0') /* Comprueba que se introducen solo letras en la clave */
            {
                noEsLetra++;
            }
        }

        for(int i=0; i<N_ASIGNATURAS; i++) /* Pide introducir una clave hasta que esta sea diferente de las existentes */
        {
            if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
            {
                contador++;
                printf("\t\tYa existe una asignatura con esa clave\n");
            }
        }
    }
    while (contador != 0  || noEsLetra != 0);

    do
    {
        contador = 0;
        printf("\t  Nombre (max. 30 caracteres): ");
        fgets(nombre, 31, stdin);
        comprobarSaltoLinea(nombre);
        fflush(stdin);

        for(int i=0; i<N_ASIGNATURAS; i++) /* Este for controla que no haya otra asignatura con el mismo nombre */
        {
            if(strcmp(grado[numGrado-1].asignatura[i].nombre, nombre) == 0)
            {
                contador++;
                printf("\t\tYa existe una asignatura con ese nombre\n");
            }
        }
    }
    while (contador != 0);

    printf("\t  Descripcion (max. 80 caracteres): ");
    fgets(descripcion, 81, stdin);
    comprobarSaltoLinea(descripcion);
    fflush(stdin);

    for(int k=0; k<N_TEMAS; k++) /* Este for cuenta el numero de temas que existen de la asignatura */
    {
        if(strcmp(grado[numGrado-1].asignatura[numReg-1].tema[k].identificador, "vacio") != 0)
        {
            numTemas++;
        }
    }
    printf("\t  Temas disponibles: %d", numTemas); /* Antes de aniadir el primer tema hay que aniadir la asignatura por lo que esto siempre sera = 0 */

    /* Estos codigos almacenan los datos introducidos en el vector de asignaturas */
    grado[numGrado-1].asignatura[numReg-1].numero = numReg;
    strcpy(grado[numGrado-1].asignatura[numReg-1].clave, clave);
    strcpy(grado[numGrado-1].asignatura[numReg-1].nombre, nombre);
    strcpy(grado[numGrado-1].asignatura[numReg-1].descripcion, descripcion);

    printf("\n\n\t\tLa asignatura ha sido registrada con exito!\n\n\n");

    system("pause");
    menuPpal();
    return 0;
}

void bajaAsignatura()
{
    char clave[3];
    int contador = 0;
    int contadorAs = 0;
    char opcion = ' ';
    int numA = 0;
    int numGrado = 0;

    system("cls");
    cabecera();

    printf("/****** BAJA DE UNA ASIGNATURA *******/\n\n");

    printf("Introduzca el numero de registro del grado (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    imprimirAsignaturas(); /* Imprime la lista de asignaturas existentes */

    contador = 0;
    for(int i=0; i<N_ASIGNATURAS; i++)
    {
        if(strcmp(grado[numGrado-1].asignatura[i].clave, "0") != 0)
        {
            contadorAs++;
        }
    }

    if(contadorAs != 0)
    {
        do
        {
            do{
                printf("\tIntroduzca la clave de la asignatura que desea eliminar: ");
                scanf("%s", clave);
                mayusculas(clave);
                fflush(stdin);

                if (strcmp(clave, "0") == 0)
                {
                    printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n\n");
                }
            }while(strlen(clave) > 2 || strcmp(clave, "0") == 0);

            contador = 0;
            for(int i=0; i<N_ASIGNATURAS; i++)
            {
                if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
                {
                    contador++;
                    numA = i; /* Borra el numero de asignatura segun la posicion en el vector asignaturas */
                }
            }

            if (contador == 0)
            {
                printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n\n");
            }
        }
        while (contador == 0);


        printf("\n\n\tATENCION! Con el borrado de la asignatura se suprimiran tambien todos los temas asociados a ella.\n");

        while(opcion != 'S' && opcion != 'N')
        {
            printf("\tEsta seguro de que quiere borrar la asignatura (S/N)? ");
            scanf(" %c", &opcion);
            opcion = toupper(opcion);
            fflush(stdin);

            switch(opcion)
            {
            case 'S': /* Inicializa los valores de la asignatura seleccionada */

                grado[numGrado-1].asignatura[numA].numero = numA;
                strcpy(grado[numGrado-1].asignatura[numA].clave, "0");
                strcpy(grado[numGrado-1].asignatura[numA].nombre, "vacio");
                strcpy(grado[numGrado-1].asignatura[numA].descripcion, "vacio");

                for(int j=0; j<N_TEMAS; j++)
                {
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].clave, "0");
                    grado[numGrado-1].asignatura[numA].tema[j].numeroTema = j+1;
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].identificador, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].titulo, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].descripcion, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].fechaAlta, "00/00/0000");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].profesor, "vacio");
                }

                printf("\n\n\t\tLa asignatura ha sido eliminada con exito!\n\n\n");

                break;
            case 'N':
                printf("\n\n\t\tLa asignatura no ha sido eliminada\n\n\n");
                break;
            }
        }

        system("pause");
        menuPpal();
        return 0;
    }
}

void nuevoTema()
{
    char clave[6];
    int numT = 0; /* Numero del tema */
    int numA = 0; /* Numero de la asignatura */
    int contador = 0;
    int contadorAs = 0;
    char titulo[81];
    char descripcion[81];
    char fechaAlta[11];
    int contFecha = 0;
    char profesor[41];
    int numGrado = 0;
    char idCompleta[10];

    system("cls");
    cabecera();

    printf("/****** NUEVO TEMA *******/\n\n");

    imprimirAsignaturas();

    printf("Introduzca el numero de registro del grado (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    for(int i=0; i<N_ASIGNATURAS; i++)
    {
        if(strcmp(grado[numGrado-1].asignatura[i].clave, "0") != 0)
        {
            contadorAs++;
        }
    }

    if(contadorAs != 0)
    {
        printf("\tATENCION! Esta operacion puede sobreescribir datos existentes.\n\n");
        printf("    Introduzca la siguiente informacion:\n");

        do
        {
            do{
                printf("\tClave de la asignatura a la que pertenece (max. 2 letras): ");
                scanf("%s", &clave);
                mayusculas(clave);
                fflush(stdin);

                if (strcmp(clave, "0") == 0)
                {
                    printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n");
                }
            }while(strlen(clave) > 2 || strcmp(clave, "0") == 0);

            contador = 0; // ERROR CORREGIDO: en el codigo anterior este contador estaba antes del do y no funcionaba
            for(int i=0; i<44; i++)
            {
                if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
                {
                    contador++;
                }
            }
            if (contador == 0)
            {
                printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n");
            }
        }
        while (contador == 0);

        for(int i=0; i<N_ASIGNATURAS; i++)
        {
            if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
            {
                numA = i; /* Encuentra la posicion en el vector de la asignatura con la clave introducida */
            }
        }

        while(isdigit(numT) != 1 && (numT <=0 || numT > 30))
        {
            printf("\tNumero de tema (1/30): ");
            scanf(" %d", &numT);
            fflush(stdin);
        }

        printf("\tProfesor (max. 40 caracteres): ");
        fgets(profesor, 41, stdin);
        comprobarSaltoLinea(profesor);
        fflush(stdin);

        printf("\tTitulo del tema (max. 80 caracteres): ");
        fgets(titulo, 81, stdin);
        comprobarSaltoLinea(titulo);
        fflush(stdin);

        printf("\tDescripcion (max. 80 caracteres): ");
        fgets(descripcion, 81, stdin);
        comprobarSaltoLinea(descripcion);
        fflush(stdin);

        do
        {
            contFecha = 0;
            printf("\tFecha de Alta (ej. 01/01/2000): ");
            fgets(fechaAlta, 11, stdin);
            comprobarSaltoLinea(fechaAlta);
            fflush(stdin);

            for (int i=0; i<10; i++)
            {
                if (isdigit(fechaAlta[i]) == 0 && fechaAlta[i] != '/')
                {
                    contFecha = 1;
                }
            }
        }
        while(strlen(fechaAlta) != 10 || contFecha == 1);

        /* A partir de aqui se aniaden los datos introducidos en el vector temas */
        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].clave, clave);
        grado[numGrado-1].asignatura[numA].tema[numT-1].numeroTema = numT;

        strcpy(idCompleta, grado[numGrado-1].id);
        strcat(idCompleta, "-");
        strcat(idCompleta, clave);
        strcat(idCompleta, "_");

        sprintf(clave, "%s%d", idCompleta, numT);
        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].identificador, idCompleta); // Este comando copia el valor de clave en el ID asignatura

        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].titulo, titulo);
        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].descripcion, descripcion);
        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].fechaAlta, fechaAlta);
        strcpy(grado[numGrado-1].asignatura[numA].tema[numT-1].profesor, profesor);

        printf("\n\t\tEl tema ha sido dado de alta con exito!\n");
        printf("\t\tEl identificador asignado es %s\n", grado[numGrado-1].asignatura[numA].tema[numT-1].identificador);

        printf("\n\n");
        system("pause");
        menuPpal();
        return 0;
    }
}

void eliminarTema()
{
    char clave[3];
    char id[6];
    int contador = 0;
    int contador2 = 0;
    int contadorAs = 0;
    int numA = 0;
    int numGrado = 0;

    system("cls");
    cabecera();

    printf("/****** ELIMINAR TEMA *******/\n\n");

    imprimirAsignaturas();

    printf("Introduzca el numero de registro del grado de la asignatura (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    for(int i=0; i<N_ASIGNATURAS; i++)
    {
        if(strcmp(grado[numGrado-1].asignatura[i].clave, "0") != 0)
        {
            contadorAs++;
        }
    }

    if(contadorAs != 0)
    {

        contador = 0;
        do
        {
            do{
                printf("\tClave de la asignatura a la que pertenece (max. 2 letras): ");
                scanf("%s", clave);
                mayusculas(clave);
                fflush(stdin);

                if (strcmp(clave, "0") == 0) // ERROR CORREGIDO: en el antiguo codigo al introducir 0 imprimia una lista
                {
                    printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n\n");
                }

            }while(strlen(clave) > 2 || strcmp(clave, "0") == 0);

            for(int i=0; i<N_ASIGNATURAS; i++)
            {
                if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
                {
                    contador++;
                }
            }
            if (contador == 0)
            {
                printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n\n");
            }
        }
        while (contador == 0);

        for(int i=0; i<44; i++)
        {
            if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
            {
                numA = i;
            }
        }

        system("cls");
        cabecera();
        printf("/****** ELIMINAR TEMA *******/\n\n");

        imprimirTemas();

        for(int i=0; i<N_TEMAS; i++){
            if(strcmp(grado[numGrado-1].asignatura[numA].tema[i].clave, "0") != 0) {
                contador2++;
            }
        }

        if(contador2 != 0){

            do
            {
                printf("\tIntroduzca el identificador del tema que desea eliminar: ");
                scanf(" %s", &id);
                mayusculas(id);
                fflush(stdin);
            }
            while(strlen(id) > 5);

            contador = 0;
            for(int j=0; j<N_TEMAS; j++)
            {
                if(strcmp(grado[numGrado-1].asignatura[numA].tema[j].identificador, id) == 0) /* Se inicializan los valores del tema seleccionado */
                {
                    contador++;
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].clave, "0");
                    grado[numGrado-1].asignatura[numA].tema[j].numeroTema = j;
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].identificador, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].titulo, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].descripcion, "vacio");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].fechaAlta, "00/00/0000");
                    strcpy(grado[numGrado-1].asignatura[numA].tema[j].profesor, "vacio");

                    printf("\n\n\t\tEl tema ha sido eliminado con exito!\n\n");
                }
            }

            if (contador == 0)
            {
                printf("\n\t\tEl identificador no se corresponde con ningun tema del registro\n\n\n");
            }

            printf("\n");
            system("pause");
            menuPpal();
            return 0;
        }
    }
}

void listadoRegistro()
{
    char opcion = ' ';
    int contador = 0;
    int numGrado = 0;

    system("cls");
    cabecera();

    printf("/****** LISTADO DE LAS ASIGNATURAS DISPONIBLES *******/\n\n");
    imprimirAsignaturas();

    printf("Introduzca el numero de registro al grado al que pertenece (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    contador = 0;
    for(int i=0; i<44; i++)
    {
        if(strcmp(grado[numGrado-1].asignatura[i].clave, "0") != 0)
        {
            contador++;
        }
    }

    if(contador != 0)
    {
        while(opcion != 'S' && opcion != 'N')
        {
            printf("\tQuiere ver los temas de alguna asignatura (S/N)? ");
            scanf(" %c", &opcion);
            opcion = toupper(opcion);
            fflush(stdin);

            switch(opcion)
            {
            case 'S':
                listadoTemas();
                return 0;
                break;
            case 'N':
                menuPpal();
                return 0;
                break;
            }
        }
    }
}

void listadoTemas()
{
    char clave[6];
    int contador = 0;
    int contador2 = 0;
    int numA = 0;
    int numGrado = 0;

    printf("Introduzca el numero de registro al grado al que pertenece (1/20): ");
    scanf("%d", &numGrado);
    fflush(stdin);

    do
    {
        do{
            printf("\tSeleccione la clave de la asignatura: ");
            scanf("%s", &clave); // El & puede ponerse o no, ya que los arrays se pasan siempre por referencia
            mayusculas(clave);
            fflush(stdin);

            if (strcmp(clave, "0") == 0)
            {
                printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n");
            }
        }while(strlen(clave) > 2 || strcmp(clave, "0") == 0);

        contador = 0;
        for(int i=0; i<44; i++)
        {
            if(strcmp(grado[numGrado-1].asignatura[i].clave, clave) == 0)
            {
                contador++;
                numA = i;
            }
        }

        if (contador == 0)
        {
            printf("\n\t\tLa clave no se corresponde con ninguna asignatura del registro\n\n");
        }
    }
    while(contador == 0);

    system("cls");
    cabecera();
    printf("/****** LISTADO DE TEMAS DE LA ASIGNATURA SELECCIONADA *******/\n\n");

    imprimirTemas();

    for(int i=0; i<N_TEMAS; i++){
        if(strcmp(grado[numGrado-1].asignatura[numA].tema[i].clave, "0") != 0) {
            contador2++;
        }
    }

    if(contador2 != 0){
        system("pause");
        listadoRegistro();
        return 0;
    }
}


/* Funcion principal, aqui empieza a funcionar el programa */
int main(void)
{
    inicializar_grados();
    inicializarAsignaturas();
    inicializarTemas();

    menuInicial();

    return 0;
}
