#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostrar(lista_t *l){
   elemento_t *e;

   for(int i=0;i<lista_cantidad(l);i++){
     e=lista_elemento(l,i+1);
     int a=e->a;
     printf(" %i \n",a);}
}

int main()
{
 lista_t * l=crear_lista();

 elemento_t *e1=( elemento_t*)malloc(sizeof(struct elemento));
 e1->a=1;
 e1->b='a';

 elemento_t *e2=( elemento_t*)malloc(sizeof(struct elemento));
 e2->a=2;
 e2->b='b';

 elemento_t *e3=( elemento_t*)malloc(sizeof(struct elemento));
 e3->a=3;
 e3->b='c';

 elemento_t *e4=( elemento_t*)malloc(sizeof(struct elemento));
 e4->a=4;
 e4->b='d';

 lista_insertar(l,*e1,1);
 lista_insertar(l,*e2,1);
 lista_insertar(l,*e3,1);
 printf("inserte \n");
 mostrar(l);
}
