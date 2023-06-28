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
      for(int i=0;i<strlen(s); i++){
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

 int multiset_cantidad(multiset_t *m, char *s)
{
    int pos, salida;
    multiset_t* p = m;

    for(int i = 0; i < strlen(s); i++){
        pos = s[i]-97;
        if(p->siguiente[pos] == NULL)
            salida=0;
        p = p->siguiente[pos];
    }
salida=p->cantidad;
return salida;}

/**
 * @m arbol a recorrer, @l lista a insertar elementos, @palabra palabra actual,@nivel nivel de recorrido.
 * Recorre el árbol en preOrden insertando en la lista las palabras pertenecientes al multiset
**/
void insertarPreOrdenAux(multiset_t *m, lista_t *l, char *palabra, int nivel){
    elemento_t *elemAux = malloc(sizeof(elemento_t));
    elemAux -> b = malloc(sizeof(char)*26);
    int aux=0;
    if(m -> cantidad>0 ){
        palabra [nivel] ='\0';
        elemAux->a = m-> cantidad;
        elemAux->b = strdup(palabra);
        // lista_insertar (l, *elemAux, lista_cantidad(l)+1); inserta todos los prefijos podría usarse en otro problema
       }
    for (int pos = 0; pos < 26; pos++){
        if(m -> siguiente[pos] != NULL){
            palabra [nivel]= 97 +pos;
            insertarPreOrdenAux(m ->siguiente [pos], l,palabra, nivel+1);
            aux=pos;
        }
    }
     //Espero a tener la palabra completa para insertarla sino, inserta todos sus prefijos tambien.
     if(m -> siguiente[aux] == NULL)
        lista_insertar (l, *elemAux, lista_cantidad(l)+1);
}



lista_t multiset_elementos(multiset_t *m){
        lista_t *l=lista_crear();
        char *palabra = malloc(sizeof(char)*26);
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
           for(int i = 0; i < 26; i++)
              {eliminar_aux(m->siguiente[i], destruir_elemento);}
}


void multiset_eliminar(multiset_t **m){
        eliminar_aux(*m,destruir_elemento);
        free(*m);

}


