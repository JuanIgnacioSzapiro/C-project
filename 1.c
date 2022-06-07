/**
 * @file 1.c
 * @author Juan Ignacio Szapiro (juanignacioszapiro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 * leer un archivo de texto con nombres, pasarlos al struct "datos" y reescribir esa información en un archivo binario. Luego hacer un menu con el cual se pueda agregar al final, modificar y eliminar (de manera lógica)
 * 
typedef struct{
    int activo;
    int codigo;
    char apellido[81];
    char nombre[81];
}datos;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef struct{
    int activo;
    int codigo;
    char apellido[81];
    char nombre[81];
}datos;
void to_main();
void menu();
void mostrarMenu();
void mostrarArchivoTexto();
void mostrarArchivoBinario();
void extenderBinario();
void tokenning();
void actualizar();
int buscarXcodigo();
int validarBinarioVacio();
int main(){
    printf("\nINICIO DEL PROGRAMA\n");
    to_main();
    printf("\nFIN DEL PROGRAMA\n");
    return 0;
}
void to_main(){
    char nombre_archivoT_0[81]="Nombres.txt";
    char nombre_archivoB_0[81]="Registro.dat";
    FILE *archivoT_0;
    FILE *archivoB_0;
    //Apertura de archivo texto
    archivoT_0=fopen(nombre_archivoT_0, "r+t");
    while(archivoT_0==NULL){
        printf("\nHubo un error en la apertura del archivo \"%s\"\n", nombre_archivoT_0);
        archivoT_0=fopen(nombre_archivoT_0, "w+t");
    }
    printf("\n\"%s\" abierto correctamente\n", nombre_archivoT_0);
    //Apertura de archivo binario
    archivoB_0=fopen(nombre_archivoB_0, "r+b");
    while(archivoB_0==NULL){
        printf("\nHubo un error en la apertura del archivo \"%s\"\n", nombre_archivoB_0);
        archivoB_0=fopen(nombre_archivoB_0, "w+b");
        fclose(archivoB_0);
        archivoB_0=fopen(nombre_archivoB_0, "r+b");
    }
    printf("\n\"%s\" abierto correctamente\n", nombre_archivoB_0);
    menu(archivoT_0, archivoB_0);
    //Cierre de archivo de texto
    fclose(archivoT_0);
    //Cierre de archivo binario
    fclose(archivoB_0);
}
void menu(FILE *archT, FILE *archB){
    int opcion=0;
    do{
        mostrarMenu(0);
        scanf("%i", &opcion);
        if(opcion<0||opcion>4){
            printf("\nEl valor tiene que estasr entre 0 y 4\n");
        }
        else{
            switch(opcion){
                case 0:{
                    return;
                }
                case 1:{
                    printf("\nOPCION: %i\n", opcion);
                    mostrarArchivoTexto(archT);
                    break;
                }
                case 2:{
                    printf("\nOPCION: %i\n", opcion);
                    mostrarArchivoBinario(archB, 0);
                    break;
                }
                case 3:{
                    printf("\nOPCION: %i\n", opcion);
                    do{
                        mostrarMenu(1);
                        scanf("%i", &opcion);
                        if(opcion<0||opcion>3){
                            printf("\nEl valor tiene que estasr entre 0 y 3\n");
                        }
                        else{
                            switch(opcion){
                                case 0:{
                                    break;
                                }
                                case 1:{
                                    printf("\nOPCION: %i\n", opcion);
                                    if(validarBinarioVacio(archB)==0){
                                        mostrarArchivoBinario(archB, (int)1);
                                        actualizar(archB, (int)0);
                                    }
                                    
                                    break;
                                }
                                case 2:{
                                    printf("\nOPCION: %i\n", opcion);
                                    if(validarBinarioVacio(archB)==0){
                                        mostrarArchivoBinario(archB, (int)1);
                                        actualizar(archB,(int)1);
                                    }
                                    
                                    break;
                                }
                                case 3:{
                                    printf("\nOPCION: %i\n", opcion);
                                    if(validarBinarioVacio(archB)==0){
                                        mostrarArchivoBinario(archB, (int)1);
                                        actualizar(archB,(int)2);
                                    }
                                    
                                    break;
                                }
                            }
                        }
                    }while(opcion!=0);
                    opcion=-1;
                    break;
                }
                case 4:{
                    printf("\nOPCION: %i\n", opcion);
                    extenderBinario(archT, archB);
                    break;
                }
            }
        }
    }while(opcion!=0);
}
void mostrarMenu(int menuAmostrar){
    switch(menuAmostrar){
        case 0:{
            printf("\nMENU:");
            printf("\n  1.Mostrar archivo de texto");
            printf("\n  2.Mostrar archivo de binario");
            printf("\n  3.Modificar una persona (en el archivo binario)");
            printf("\n  4.Actualizar archivo binario");
            printf("\n  0.Salir");
            printf("\n  Ingrese su eleccion: ");
            break;
        }
        case 1:{
            printf("\nMENU MODIFICAIONES:");
            printf("\n  1.Activo");
            printf("\n  2.Nombre");
            printf("\n  3.Apellido");
            printf("\n  0.Salir");
            printf("\n  Ingrese su eleccion: ");
            break;
        }
    }
}
/**
 * @brief 
 * 
 * @param archT -> arch a mostrar
 */
void mostrarArchivoTexto(FILE *archT){
    rewind(archT);
    char cadena[81];
    // printf("\n%i\n", (sizeof(cadena)/sizeof(char)));
    if(feof(archT)){
        printf("\nEl archivo esta vacio\n");
    }
    while(!feof(archT)){
        fgets(cadena, sizeof(cadena)/sizeof(char), archT);
        printf("%s", cadena);
    }
}
/**
 * @brief 
 * 
 * @param archB -> arch a mostrar
 */
void mostrarArchivoBinario(FILE *archB, int opcion){
    datos pers;
    validarBinarioVacio(archB);
    while(!feof(archB)){
        //Si la persona esta vigente, entoces la imprime
        if((pers.activo==1)&&(opcion==0)){
            printf("\nCodigo: %i\n  Activo?: %i\n   Nombre y apellido: %s %s\n", pers.codigo, pers.activo, pers.nombre, pers.apellido);
        }
        else if(opcion==1){
            printf("\nCodigo: %i\n  Activo?: %i\n   Nombre: %s\n    Apellido: %s\n", pers.codigo, pers.activo, pers.nombre, pers.apellido);
        }
        fread(&pers, sizeof(datos), 1, archB);
    }
}
/**
 * @brief 
 * 
 * @param archT archivo de texto
 * @param archB archivo binario
 */
void extenderBinario(FILE *archT, FILE *archB){
    datos pers;    
    datos anterior;
    rewind(archT);
    rewind(archB);
    while(!feof(archT)){
        tokenning(archT, &pers);
        fread(&anterior, sizeof(datos), 1, archB);
        if(!feof(archB)){
            //SE VUELVEN 2 PORQUE EL EOF CUENTA COMO UN DATO BINARIO Y EL QUE QUEREMOS SABER NO ES UN DATO VACIO, SINO UNO ESCRITO
            fseek(archB, (long int)sizeof(datos)*(-2L), SEEK_END);
            fread(&anterior, sizeof(datos), 1, archB);
        }
        else{
            anterior.codigo=-1;
        }
        // printf("\nANTERIOR\nCodigo: %i\n  Activo?: %i\n   Nombre y apellido: %s %s\n", anterior.codigo, anterior.activo, anterior.nombre, anterior.apellido);
        pers.activo=1;
        pers.codigo=anterior.codigo+1;
        printf("\nCodigo: %i\n  Activo?: %i\n   Nombre y apellido: %s %s\n", pers.codigo, pers.activo, pers.nombre, pers.apellido);
        //SE VUELVEN 1 PORQUE EL EOF CUENTA COMO UN DATO BINARIO Y EL QUE NOS INTERESA SOBREESCRIBIR ES EL VACIO
        fseek(archB, (long int)sizeof(datos)*(-1L), SEEK_END);
        fwrite(&pers, sizeof(datos), 1, archB);
    }
}
void tokenning(FILE *archT, datos *pers){
    int contador=0;
    char cadena[81];
    char *token;
    fgets(cadena, sizeof(cadena)/sizeof(char), archT);
    //expresion regular
    sscanf(cadena, "%[a-zA-Z ,]", cadena);
    //sscanf(cadena, "%[^\n]", cadena);
    //'sscanf' copia UNICAMENTE lo especificado entre corchetes
    //(origen, parametros, destino)
    token=strtok(cadena, ",");
    // printf("\n%s", cadena);
    while(token!=NULL){
        // printf("\n%s", token);
        switch(contador){
            case 0:{
                strcpy(pers->apellido, token);
                break;
            }
            case 1:{
                strcpy(pers->nombre, token);
                break;
            }
        }
        contador++;
        token=strtok(NULL, ",");
    }
}
/**
 * @brief 
 * 
 * @param archB 
 * @param opcion Activo?->0 / Nombre->1 / Apellido->2
 */
void actualizar(FILE *archB, int opcion){
    int codIngresado=0;
    char cadena[81];
    datos pers;
    do{
        printf("\nIngresar codigo  de persona a buscar: ");
        fflush(stdin);
        scanf("%i", &codIngresado);
        fflush(stdin);
    }while(buscarXcodigo(archB, codIngresado, &pers)==0);
    // printf("\nENTRA");
    switch(opcion){
        case 0:{
            if(pers.activo==0){
                pers.activo=1;
            }
            else if(pers.activo==1){
                pers.activo=0;
            }
            fseek(archB, (long int)sizeof(datos)*(-1L), SEEK_CUR);
            fwrite(&pers, sizeof(datos), 1, archB);
            break;
        }
        case 1:{
            printf("\nIngresar nuevo nombre de persona la persona con codigo %i: ", pers.codigo);
            fflush(stdin);
            fgets(cadena, sizeof(cadena)/sizeof(char), stdin);
            sscanf(cadena, "%[a-zA-Z ]", pers.nombre);
            fflush(stdin);
            fseek(archB, (long int)sizeof(datos)*(-1L), SEEK_CUR);
            fwrite(&pers, sizeof(datos), 1, archB);
            break;
        }
        case 2:{
            printf("\nIngresar nuevo apellido de persona la persona con codigo %i: ", pers.codigo);
            fflush(stdin);
            fgets(cadena, sizeof(cadena)/sizeof(char), stdin);
            sscanf(cadena, "%[a-zA-Z ]", pers.apellido);
            fflush(stdin);
            fseek(archB, (long int)sizeof(datos)*(-1L), SEEK_CUR);
            fwrite(&pers, sizeof(datos), 1, archB);
            break;
        }
    }
}
/**
 * @brief 
 * 
 * @param archB ARCHIVO BINARIO
 * @param codIng CODIGO INGRESADO
 * @param pers DATOS
 * @return int false->0 / true->1
 */
int buscarXcodigo(FILE *archB, int codIng, datos *pers){
    rewind(archB);
    fread(pers, sizeof(datos), 1, archB);
    //al ser puntero NO se pone '&' porque da como resultado la direccion
    while(!feof(archB)){
        if(codIng==(pers->codigo)){
            return 1;
        }
        else{
            fread(pers, sizeof(datos), 1, archB);
        }
    }
    printf("\nCodigo %i no encontrado, ingresar nuevamente", codIng);
    return 0;
}
/**
 * @brief 
 * 
 * @return int false->0 / true->1
 */
int validarBinarioVacio(FILE *archB){
    datos pers;
    rewind(archB);
    fread(&pers, sizeof(datos), 1, archB);
    if(feof(archB)){
        printf("\nEl archivo esta vacio\n");
        return 1;
    }
    return 0;
}