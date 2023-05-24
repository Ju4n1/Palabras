#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

// Macros con códigos de finalización
#define LST_NO_EXISTE_SIGUIENTE     1
#define LST_POSICION_INVALIDA       2
#define LST_ERROR_MEMORIA           3

typedef enum {
ELEM1_MAYOR_QUE_ELEM2,
ELEM1_IGUAL_QUE_ELEM2,
ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;

struct elemento {
int a;
char *b;
};
typedef struct elemento elemento_t;

typedef comparacion_resultado_t (funcion_comparacion_t) (
elemento_t *elem1, elemento_t *elem2
);

typedef struct celda celda_t;

struct lista {
celda_t* primera; //puntero a la primera celda de la lista
int cantidad; // cantidad de elementos de la lista
};
typedef struct lista lista_t;


// ---------------------------------------------------------------------------------------------
// Definición de prototipos y documentación de las funciones.
// Obs.: a todo efecto y en tanto no se indique lo contrario, toda posición parametrizada
// es considerada válida.
// ---------------------------------------------------------------------------------------------


/**
   Crea una lista nueva y la retorna.
**/
extern lista_t * lista_crear();


/**
   Inserta al elemento elem en la posición pos dentro de la lista  l.
**/
extern int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos);


/**
   Dada una posición pos, se elimina el elemento perteneciente a la lista referenciado por la posicion dada
   finalmente retorna el elemento que contiene la posicion eliminada.
**/
extern elemento_t * lista_eliminar(lista_t *l, unsigned int pos);


/**
   Retorna el elemento referenciado por la posicion pos dentro de la lista.
**/
extern elemento_t *lista_elemento(lista_t *l, unsigned int pos);


/**
  Ordena la lista l, usando como prioridad la función comparación dada.
**/
extern int lista_ordenar(lista_t *l, funcion_comparacion_t comparar);


/**
   Retorna la cantidad de elemento que almacena la lista.
**/
extern unsigned int lista_cantidad(lista_t *l);


/**
   Consulta si la lista está vacia, retornando 0 en caso de que posea al menos un elemento y distinto de 0 de lo contrario.
**/
extern int lista_vacia(lista_t lista);

#endif // LISTA_H_INCLUDED
