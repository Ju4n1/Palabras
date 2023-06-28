#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
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

void mostrar(lista_t *l){
   elemento_t *e;

   for(int i=1;i<=lista_cantidad(l);i++){
     e=lista_elemento(l,i);

     printf(" %i %s \n",e->a,e->b);
    }
}

int main()
{
 lista_t * l=lista_crear();

 elemento_t *e1=malloc(sizeof(struct elemento));
 char* c1=malloc(sizeof(char)*26);
 c1="uno";
 int i1=1;
 e1->a=i1;
 e1->b=c1;

 elemento_t *e2=malloc(sizeof(struct elemento));
 char* c2=malloc(sizeof(char)*26);
 c2="dos";
 int i2=1;
 e2->a=i2;
 e2->b=c2;

  elemento_t *e3=malloc(sizeof(struct elemento));
 char* c3=malloc(sizeof(char)*26);
 c3="tres";
 int i3=2;
 e3->a=i3;
 e3->b=c3;

  elemento_t *e4=malloc(sizeof(struct elemento));
 char* c4=malloc(sizeof(char)*26);
 c4="cuatro";
 int i4=1;
 e4->a=i4;
 e4->b=c4;

/*
free(e1);
free(e2);
free(e3);
free(e4);*/


 lista_insertar(l,*e1,1);
 lista_insertar(l,*e2,2);
 lista_insertar(l,*e3,1);
 lista_insertar(l,*e4,1);

/* Pruevo comparador
printf("comparo e1 e2 %i ",funcion_comparacion(e4,e1));

   if(funcion_comparacion(e3,e1)==ELEM1_MAYOR_QUE_ELEM2)
      printf(" 1 ");
    else
        if (funcion_comparacion(e3,e1)==ELEM1_MENOR_QUE_ELEM2)
          printf(" -1 ");
          else if(funcion_comparacion(e3,e1)==ELEM1_IGUAL_QUE_ELEM2)
                printf(" 0 ");
*/

 //mostrar(l);
  //printf("muestro e1 %i %s",e1->a,e1->b);
  //elemento_t  *e;
 // e=lista_elemento(l,4);

 //printf("comparo 1 y 2 %i ",strcmp(lista_elemento(l,1)->b,lista_elemento(l,2)->b));
  //mostrar(l);
  mostrar(l);
  lista_ordenar(l,funcion_comparacion);
  printf("\n");
  mostrar(l);
// printf("comapro 1 con 2 %i",funcion_comparacion(e1,e2));
 //printf("comparo resultados %i %i %i ",ELEM1_IGUAL_QUE_ELEM2,ELEM1_MAYOR_QUE_ELEM2,ELEM1_MENOR_QUE_ELEM2);
}
