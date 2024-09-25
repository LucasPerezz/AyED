#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_nodo {
    void *info;
    unsigned tamInfo;
    struct s_nodo *siguiente;
} t_nodo;

typedef t_nodo *t_pila;


void crearPila(t_pila *pila) {
    *pila = NULL;
}

int esPilaVacia(const t_pila *pila) {
    return *pila == NULL;
}