#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>


struct celda {
elemento_t *elem;
struct celda *siguiente;
};
/**
   Crea una lista vacia y la referencia a la misma.
**/
lista_t* lista_crear(){
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
     elemento_t *e=malloc(sizeof(struct elemento));
     e->a=(&elem)->a;
     e->b=(&elem)->b;
     nueva->elem=e;
     nueva->siguiente=NULL;

     if(pos==1)
        {nueva->siguiente=(l->primera);
         l->primera=nueva;
         l->cantidad++;}
     else{
         celda_t * recorrido=l->primera;
         for(int i=1; i!=pos;i++)
              if(recorrido->siguiente!=NULL)
                  recorrido=recorrido->siguiente;
         if(pos<=l->cantidad)
           {nueva->siguiente->elem=recorrido->elem;
            recorrido->elem=e;
            l->cantidad++;}
            else if(pos==l->cantidad+1)
                   {recorrido->siguiente=nueva;
                    l->cantidad++;}



         }

return salida;}


elemento_t * lista_eliminar(lista_t *l, unsigned int pos){
    elemento_t* salida=NULL;
    if(pos==0||pos>l->cantidad)
       exit(LST_POSICION_INVALIDA);

    celda_t * lee=l->primera;
    if(pos==1)
     {l->primera=lee->siguiente;
      l->cantidad--;
      free(lee->elem);
      free(lee);}
    else{
         for(int i=1; i<pos-1;i++)
              if(lee->siguiente!=NULL)
                  lee=lee->siguiente;
         if(pos<l->cantidad)
            {celda_t *eliminar=lee->siguiente;
             lee->siguiente=lee->siguiente->siguiente;
             free(eliminar->elem);
             free(eliminar);
             l->cantidad--;}
            else if(pos==l->cantidad)
                   {celda_t *eliminar=lee->siguiente;
                    lee->siguiente=NULL;
                    free(eliminar->elem);
                    free(eliminar);
                    l->cantidad--;}
         }


return salida;}

elemento_t *lista_elemento(lista_t *l, unsigned int pos){
    if(pos==0||pos>l->cantidad)
        exit(LST_POSICION_INVALIDA);

    celda_t * lee=l->primera;
    for(int i=1;i<pos;i++)
       lee=lee->siguiente;
return lee->elem;}


int lista_ordenar(lista_t *l, funcion_comparacion_t comparar){
        lista_t* laux=lista_crear();
        celda_t* lee;
        celda_t* menor;

        while(!lista_vacia(l)){
             lee=l->primera;
             menor=l->primera;
             int pos=1;
             int posMenor=1;

             while(pos<=lista_cantidad(l)){
                   if(comparar(lee->elem,menor->elem)==ELEM1_MENOR_QUE_ELEM2)
                     {posMenor=pos;
                      menor=lee;
                      }
                   lee=lee->siguiente;
                   pos++;
                   }
             elemento_t* nuevo=malloc(sizeof(struct elemento));
             nuevo->a=menor->elem->a;
             nuevo->b=menor->elem->b;
             lista_insertar(laux,*nuevo,lista_cantidad(laux)+1);
             lista_eliminar(l,posMenor);
             }
*l=*laux;
return 1;}


unsigned int lista_cantidad(lista_t *l){
return l->cantidad;}


int lista_vacia(lista_t *l){

return (l->cantidad==0);}

