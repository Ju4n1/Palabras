#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct celda {
elemento_t *elem;
struct celda *siguiente;
};

/**
   Crea una lista vacia y la referencia a la misma.
**/
lista_t* crear_lista(){
    lista_t * nueva= malloc(sizeof (struct lista));
    if(nueva==NULL)
        exit(LST_ERROR_MEMORIA);
     nueva->cantidad=0;
     nueva->primera=NULL;
return nueva;}


/**
   Inserta un nuevo elemento en la lista retornando 0 si la operacion no se puso realizar y
   distinto de 0 de lo contrario;
**/
int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos){
     int salida=0;
     if(pos==0&&pos>l->cantidad+1)
        exit(LST_POSICION_INVALIDA);
        else salida=1;
     celda_t * nueva=malloc(sizeof(struct celda));
     nueva->elem=(&elem);
     nueva->siguiente=NULL;

     if(pos==1)
        {nueva->siguiente=l->primera;
         l->primera=nueva;
         l->cantidad++;}
     else{
         celda_t * recorrido=l->primera;
         int pos_aux=0;
         for(int i=0;i<l->cantidad;i++)
              if(i<l->cantidad)
                 {recorrido=recorrido->siguiente;
                  pos_aux=i;}
         if(pos_aux<l->cantidad)
            {nueva->siguiente=recorrido;
             recorrido->elem=nueva->elem;
             l->cantidad++;}
            else if(pos_aux==l->cantidad+1)
                   {recorrido->siguiente=nueva;
                    l->cantidad++;}
                    else exit(LST_POSICION_INVALIDA);

         }
return salida;}


elemento_t * lista_eliminar(lista_t *l, unsigned int pos){
    elemento_t* salida=NULL;
    if(pos==0&&pos>l->cantidad)
       exit(LST_POSICION_INVALIDA);
    celda_t * lee=l->primera;
    int pos_aux=0;
    for(int i=0;i<l->cantidad;i++){
       if(i!=pos)
         lee=lee->siguiente;
       pos_aux=i;}

    if(pos_aux==l->cantidad)
       salida=lee->elem;

    else{
        lee->elem=(lee->siguiente)->elem;
        lee=lee->siguiente;}

l->cantidad--;
free(lee);
return salida;}


elemento_t *lista_elemento(lista_t *l, unsigned int pos){
    if(pos==0&&pos==l->cantidad)
        exit(LST_POSICION_INVALIDA);
    celda_t * lee=l->primera;
    for(int i=0;i<l->cantidad;i++)
       if(i!=pos)
         lee=lee->siguiente;

return lee->elem;}


int lista_ordenar(lista_t *l, funcion_comparacion_t comparar){
return 1;}


unsigned int lista_cantidad(lista_t *l){
return l->cantidad;}


int lista_vacia(lista_t *l){

return (l->cantidad==0);}

