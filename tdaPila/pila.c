#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y)(x <= y ? x : y)

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

int esPilaLlena(t_pila *pila, unsigned cantBytes) {
    t_nodo *nodo = (t_nodo*) malloc(sizeof(t_nodo));
    void *infoNodo = malloc(cantBytes);
    free(infoNodo);
    free(nodo);
    return infoNodo == NULL || nodo == NULL;
}

int apilar(t_pila *pila, const void *dato, unsigned cantBytes) {
    t_nodo *nuevoNodo;
    nuevoNodo = (t_nodo*) malloc(sizeof(t_nodo));
    if(!nuevoNodo) return 0;
    nuevoNodo->info = malloc(cantBytes);
    if(!nuevoNodo->info) {
        free(nuevoNodo);
        return 0;
    }
    memcpy(nuevoNodo->info, dato, cantBytes);
    nuevoNodo->siguiente = *pila;
    nuevoNodo->tamInfo = cantBytes;
    *pila = nuevoNodo;
    return 1;
}

int desapilar(t_pila *pila, void *dato, unsigned cantBytes) {
    t_nodo *aux = *pila;

    if(aux == NULL) {
        return 0;
    }

    *pila = aux->siguiente;
    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int verTope(const t_pila *pila, void *dato, unsigned cantBytes) {
    if(*pila == NULL) return 0;
    memcpy(dato, (*pila)->info, minimo(cantBytes, (*pila)->tamInfo));
    return 1;
}

void vaciarPila(t_pila *pila) {
    while(*pila) {
        t_nodo *nodo = *pila;
        *pila = nodo->siguiente;
        free(nodo->info);
        free(nodo);
    }
}

int main()
{
    printf("Hello world!\n");
    return 0;
}