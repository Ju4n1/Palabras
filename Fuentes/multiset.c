#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "multiset.h"
#include <string.h>

struct trie{
int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
struct trie *siguiente[26];
};

multiset_t * multiset_crear(){

   multiset_t *m=malloc(sizeof(struct trie));
   if(m==NULL)
       exit(MLT_ERROR_MEMORIA);

   //Inicializo.
   for(int i=0;i<26;i++)
     m->siguiente[i]=NULL;
   m->cantidad=0;

return m;}


 void multiset_insertar(multiset_t *m, char *s){
      multiset_t* leo=m;
      int pos=0;
      for(int i=0;s[i]=='\0'; i++){
          pos=s[i];
          pos=pos-97; //siguiente[0]!=NULL significa que "a" está presente, [25]=NULL lo mismo para "z"
          if(leo->siguiente[pos]==NULL)
             {leo->siguiente[pos]=multiset_crear();
              leo->siguiente[pos]->cantidad=1;
              leo=leo->siguiente[pos];
             }
             else{
                 (leo->siguiente[pos])->cantidad=(leo->siguiente[pos])->cantidad+1;
                 leo=leo->siguiente[pos];
                 }

       }

 }


 int multiset_cantidad(multiset_t *m, char *s){
        int cantidad= 0;
        multiset_t *leo = malloc(sizeof(multiset_t));
        leo =m;

        //Cantidad apariciones primer letra palabra.
        if(s[0] !='\0' && leo -> siguiente[s[0] -97]!= NULL)
              cantidad = (leo -> siguiente[s[0]-97]) -> cantidad;

       //La ultima letra de la palabra tiene cantidad de apariciones,
      // las letras anteriores pueden contener prefijos.
       for(int i = 0; s[i] != '\0' && cantidad; i++){
            if(leo -> siguiente[s[i] -97]!= NULL){
               if( ((leo -> siguiente[s[i]-97]) -> cantidad) < cantidad )
                    cantidad = (leo -> siguiente[s[i]-97]) -> cantidad;}
                 else cantidad = 0;}


return cantidad;}

/**
 * @m arbol a recorrer, @l lista a insertar elementos, @palabra palabra actual,@nivel nivel de recorrido.
 * Recorre el árbol en preOrden insertando en la lista las palabras pertenecientes al multiset
**/
void insertarPreOrdenAux(multiset_t *m, lista_t *l, char *palabra, int nivel){
    elemento_t *elemAux = malloc(sizeof(elemento_t));
    elemAux -> b = malloc(sizeof(char));

    if(m -> cantidad>0 ){
        palabra [nivel] ='\0';
        elemAux->a = m-> cantidad;
        elemAux->b = strdup(palabra);
        lista_insertar (l, *elemAux, lista_cantidad(l));
    }
    for (int pos = 0; pos < 26; pos++){
        if(m -> siguiente[pos] != NULL){
            palabra [nivel]= 97 +pos;
            insertarPreOrdenAux(m ->siguiente [pos], l,palabra, nivel +1);
        }
    }
}



lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t* t1,elemento_t* t2)){
        lista_t *l=lista_crear();
        char *palabra = malloc(sizeof(char));
        insertarPreOrdenAux(m, l, palabra, 0);

return (*l);}


/**
 * @e elemento a destruir.
 * Libera el espacio reservado para e.
**/
void destruir_elemento(void*e){
free(e);}

/**
 * @m multiset @destruir_elemento funcion destruir
 *Función cascaron de eliminar.
**/
void eliminar_aux(multiset_t *m,void(destruir_elemento(void*))){

         if(m != NULL)
           {for(int i = 0; i < 26; i++)
              {eliminar_aux(m->siguiente[i], destruir_elemento);}

            free(m);}
}


void multiset_eliminar(multiset_t **m){
           eliminar_aux(*m,destruir_elemento);
           free(*m);

}


