#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "multiset.h"
#include <string.h>
#include <dirent.h>
#define MAX_BUF 200

/**
 * @elem1 @elem2 elementos a comparar
 * La siguiente funcion comparacion da la prioridad del orden de nuestra aplicación
**/
comparacion_resultado_t funcion_comparacion(elemento_t *elem1, elemento_t *elem2){
     //Inicializo la salida no influye en el resultado final.
     int salida=3;

     //Primera prioridad de comparación es la cantidad de apariciones.
     if(elem1->a > elem2->a)
        salida=ELEM1_MAYOR_QUE_ELEM2;
        else {if(elem2->a > elem1->a)
                salida=ELEM1_MENOR_QUE_ELEM2;
              else{
                  // Uso el comparador de la libreria str, se podria implementar
                 //  uno pero no es el objetivo del proyecto.
                  if(elem1->a==elem2->a)
                      {if(strcmp(elem1->b,elem2->b)>0)
                         salida=ELEM1_MAYOR_QUE_ELEM2;
                         else
                            {if(strcmp(elem1->b,elem2->b)<0)
                               salida=ELEM1_MENOR_QUE_ELEM2;
                               else salida=ELEM1_IGUAL_QUE_ELEM2;}}}}


return salida;}

/**
  * Como uso la lista como estructura adicional y no tiene destriur implemento uno
  * a fin de que el codigo sea más legible y no repertir el sgte fragmento de código.
**/
void lista_destruir(lista_t*l){
     while(!lista_vacia(l)){
         lista_eliminar(l,1);}
free(l);}

/**
* Menu de ayudas al usuario.
**/
void help(){
       printf("-----------///*Bievenido-a-la-Guia-de-usuario*////-----------\n\n\n");
       printf("El siguiente programa permite analisis palabras almacenadas en archivos dados por el usuario.\n");
       printf("Recuerde que debe proporcionar directorio donde se encuentren los archivos a analizar.\n");
       printf("Ejemplo: cuentapalabras.exe h- directorio,  h- es opcional y directorio apunta a la carpeta donde almacena los archivos.\n");
       printf("Cuando ingrese un directorio utilice barras de separador ejemplo c:\\disco\\archivos \n\n\n\n");
}

/**
 * Este codigo lo dio la cátedra, recupera nombres de los archivos txt
 * en caso que haya alguno.
**/
void nombres_archivos(char * c,lista_t* l){
  //char cadena[]="";
  //strcat(cadena,c);
  DIR *dir;
  struct dirent *ent;



    dir = opendir(c);

    if (dir != NULL){
            ent = readdir (dir);
        while (ent!= NULL) {
            // Verifica que el archivo a procesar no es invalido
            if ( (strcmp(ent->d_name, ".")!=0)
                && (strcmp(ent->d_name, "..")!=0)){

                    elemento_t*e=malloc(sizeof(struct elemento));
                    char* c1=malloc(sizeof(char)*26);
                    strcpy(c1,ent->d_name);
                    e->a=1;
                    e->b=c1;
                    lista_insertar(l,*e,lista_cantidad(l)+1);

                }
              ent = readdir (dir);
        }

        closedir (dir);

    }
    else {
        perror("No se pudo acceder al directorio");}
}


/**
 * De una lista de palabras genero el archivo de salida;
**/
void lista_a_archivo(FILE* salida,lista_t *l){

       // rewind(salida);
        if(salida==NULL)
            {printf("El archivo salida no existe. \n");}

        for(int i=1;i<=lista_cantidad(l);i++){
                fprintf(salida," %i %s \n",lista_elemento(l,i)->a,lista_elemento(l,i)->b);}


}
/**
 * Accede al contenido del archivo f1 y lo muestra en pantalla.
**/
void mostrar_arc(FILE* f1){
      rewind(f1);
     char* c=malloc(sizeof(char)*26);
     int i=0;
       while(!feof(f1)){

          fscanf(f1,"%s ",c);
          printf(" %s ",c);
          i++;
          //Salto de linea para leer de a pares
          if(i==2)
            {printf("\n");
            i=0;}

     }
}
/**
  *Genero el archivo de salida totales.out, ordenando todas las palabras
  * a partir de los archivos del directoria pasado.
**/
void salida_total(FILE* f1,lista_t* nombres,char*dir,char*dir2){

      multiset_t *m=multiset_crear();
      strcat(dir,"\\");  strcat(dir,"\\");
      strcat(dir2,"\\");strcat(dir2,"\\");
      for(int i=1;i<=lista_cantidad(nombres);i++){
            strcat(dir,lista_elemento(nombres,i)->b);
            FILE* f2=fopen(dir,"r");

            while(!feof(f2)){
                 char* pal=malloc(sizeof(char)*26);
                 fscanf(f2,"%s",pal);
                 multiset_insertar(m,pal);}
                 fclose(f2); strcpy(dir,dir2);
                 }

      //Paso todo a una lista ordena y desp a un archivo
      lista_t* aux=lista_crear();
      *aux=multiset_elementos(m);
       lista_ordenar(aux,funcion_comparacion);
       lista_a_archivo(f1,aux);

///-------Libero memoria--------///

multiset_eliminar(&m);
lista_destruir(aux);
}
/**
 * Genera el archivo de salida cadauno.out, ordenando las palabras de cada
 * archivo distinguiendo a cual pertenece cada una, a partir del directorio
 * que aporto el usuario.
**/
void salida_cada_uno(FILE* f1, lista_t* nombres,char*dir,char* dir2){
      rewind(f1);
      strcat(dir,"\\");  strcat(dir,"\\");
      strcat(dir2,"\\");strcat(dir2,"\\");
      lista_t *total=lista_crear();

      for(int i=1;i<=lista_cantidad(nombres);i++){
            multiset_t *m=multiset_crear();
            strcat(dir,lista_elemento(nombres,i)->b);
            FILE* f2=fopen(dir,"r");

            while(!feof(f2)){
                 char* pal=malloc(sizeof(char)*26);
                 fscanf(f2,"%s",pal);
                 multiset_insertar(m,pal);}
                 fclose(f2);
                 strcpy(dir,dir2);

           lista_t* aux=lista_crear();
           *aux=multiset_elementos(m);
           lista_ordenar(aux,funcion_comparacion);

           elemento_t* nom_archivo=malloc(sizeof(struct elemento));
           char* n=malloc(sizeof(char)*26);
           n=lista_elemento(nombres,i)->b;
           nom_archivo->a=1;
           nom_archivo->b=n;
           lista_insertar(aux,*nom_archivo,1);

           for(int i=1;i<=lista_cantidad(aux);i++)
                 lista_insertar(total,*lista_elemento(aux,i),lista_cantidad(total)+1);
           //lista_a_archivo(f1,aux);


           ///-------Libero memoria---------///
           multiset_eliminar(&m);
           lista_destruir(aux);

            }

lista_a_archivo(f1,total);

}
/**
 * Menu de operaciones.
**/
void menu(){
    printf("\n Para salir ingrese 0 \n\n");
    printf("\n Para analizar palabras por archivo separados ingrese 1 \n\n");
    printf("\n Para analizar palabras de todos los archivos ingrese 2 \n\n");

}
/**
 * Ejecuta cada una de las funcionalidades de la aplicacion.
**/
void programa(char* directorio){
      lista_t* nombres=lista_crear();
      nombres_archivos(directorio,nombres);

      char* dir_aux=malloc(sizeof(char)*80);
      strcpy(dir_aux,directorio);
      if(lista_vacia(nombres))
         printf("\n El directorios es valido pero no contiene archivos,asegurese que contenga los archivos y vuelva a intentar\n");
         else{
              int continuar=100;
              while(continuar!=0){
              menu();
              scanf("%i",&continuar);

              if(continuar==1)
                {FILE* f1=fopen("cadauno.out.txt","w+");
                 salida_cada_uno(f1,nombres,directorio,dir_aux);
                 mostrar_arc(f1);
                }
              if(continuar==2)
                {FILE* f2=fopen("totales.out.txt","w+");
                 salida_total(f2,nombres,directorio,dir_aux);
                 mostrar_arc(f2);
                 }
              if(continuar==0)
                    printf("\n\n La aplicacion se ejecuto con exito!!!\n");
              }
              }
lista_destruir(nombres);
}


/**
 *Administra la entrada por linea de comandos.
**/
int main(int argc, char* argv[]){

if(argc==1)
    printf("no ingreso ningun argumento, ingresando '-h' ejecuta la ayuda!!! ");
   else
      if(argc==1)
         {if (strcmp(argv[0],"-h")==0)
             help();}
          else{
              help();
              char* pal=malloc(sizeof(char)*80);//directorio
              if(argc==2)
                  {pal=argv[1]; }
                  else {pal=argv[2];}
                  programa(pal);
            }

return 0;}
