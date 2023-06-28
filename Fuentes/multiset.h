#ifndef MULTISET_H_INCLUDED
#define MULTISET_H_INCLUDED
#include "lista.h"
#define MLT_ERROR_MEMORIA 4
#define MLT_NO_EXISTE_SIGUIENTE 5

struct trie;
typedef struct trie multiset_t;

/**
 * Se crea un nuevo multiset vacio.
**/
extern multiset_t *multiset_crear();

/**
 * @s palabra nueva @*m multiset
 * Se inserta la palabra una nueva palabra en el multiset.
**/
extern void multiset_insertar(multiset_t *m, char *s);

/**
 * @m multiset @s palabra
 * Retorna la cantidad de veces que est� presente una palabra dentro del multiset
**/
extern int multiset_cantidad(multiset_t *m, char *s);

/**
 * @m multiset @f funci�n comparaci�n
 * Retorna lista con los elementos almacenados en el multiset y si cantidad de apariciones.
**/
extern lista_t multiset_elementos(multiset_t *m);

/**
 * @m multiset
 * elimina el multiset y el espacio que este ocupa en memoria haciendo uso de la funci�n free.
**/
extern void multiset_eliminar(multiset_t **m);

#endif
