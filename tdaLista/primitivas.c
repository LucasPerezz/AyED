#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y)(x <= y ? x : y)

typedef struct sNodo {
    void *info;
    unsigned tamInfo;
    struct sNodo *siguiente;
}tNodo;

typedef tNodo *tLista;

void crearLista(tLista *lista) {
    *lista = NULL;
}

int esListaVacia(const tLista *lista) {
    return *lista == NULL;
}

int esListaLlena(tLista *lista, unsigned tamInfo) {
    tNodo *aux = (tNodo*) malloc(sizeof(tNodo));
    void *info = malloc(tamInfo);
    free(info);
    free(aux);
    return aux == NULL || info == NULL;
}

void vaciarLista(tLista *lista) {
    while(*lista) {
        tNodo *aux = *lista;
        *lista = aux->siguiente;
        free(aux->info);
        free(aux);
    }
}

int ponerAlComienzo(tLista *lista, const void *info, unsigned tamInfo) {
    tNodo *nuevoNodo = (tNodo*) malloc(sizeof(tNodo));
    if(!nuevoNodo) return 0;
    nuevoNodo->info = malloc(tamInfo);
    if(!nuevoNodo->info) {
        free(nuevoNodo);
        return 0;
    }
    memcpy(nuevoNodo->info, info, tamInfo);
    nuevoNodo->tamInfo = tamInfo;
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
    return 1;
}

int sacarPrimeroLista(tLista *lista, void *info, unsigned tamInfo) {
    tNodo *aux = *lista;
    if(!aux) return 0;
    *lista = aux->siguiente;
    memcpy(info, aux->info, minimo(tamInfo, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int verPrimeroLista(const tLista *lista, void *info, unsigned tamInfo) {
    if(*lista == NULL) return 0;
    memcpy(info, (*lista)->info, minimo(tamInfo, (*lista)->tamInfo));
    return 1;
}

int ponerAlFinal(tLista *lista, const void *info, unsigned tamInfo) {
    tNodo *nuevoNodo;

    while(*lista) {
        lista = &(*lista)->siguiente;
    }

    nuevoNodo = (tNodo*) malloc(sizeof(tNodo));
    if(!nuevoNodo) return 0;
    nuevoNodo->info = malloc(tamInfo);
    if(!nuevoNodo->info) {
        free(nuevoNodo);
        return 0;
    }
    memcpy(nuevoNodo->info, info, tamInfo);
    nuevoNodo->tamInfo = tamInfo;
    nuevoNodo->siguiente = NULL;
    *lista = nuevoNodo;
    return 1;
}

int sacarUltimoLista(tLista *lista, void *info, unsigned tamInfo) {
    while((*lista)->siguiente) {
        lista = &(*lista)->siguiente;
    }
    memcpy(info, (*lista)->info, minimo((*lista)->tamInfo, tamInfo));
    free((*lista)->info);
    free(*lista);
    *lista = NULL;
    return 1;
}

int verUltimoLista(tLista *lista, void *info, unsigned tamInfo) {
    if(*lista == NULL) return 0;
    while((*lista)->siguiente) {
        lista = &(*lista)->siguiente;
    }
    memcpy(info, (*lista)->info, minimo(tamInfo, (*lista)->tamInfo));
    return 1;
}