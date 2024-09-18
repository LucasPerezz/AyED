#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define minimo(x,y)(x <= y ? x : y)

typedef struct s_nodo {
    unsigned tam;
    void *info;
    struct s_nodo *siguiente;
} t_nodo;

typedef t_nodo *t_lista;


void crearLista(t_lista *lista) {
    *lista = NULL;
}


int listaVacia(const t_lista *lista) {
    return *lista == NULL;
}

void vaciarLista(t_lista *lista) {
    t_nodo *aux;
    while(*lista) {
        aux = *lista;
        *lista = aux->siguiente;
        free(aux->info);
        free(aux);
    }
}

int verPrimeroLista(const t_lista *lista, void *dato, unsigned cantBytes) {
    if(*lista == NULL) return 0;
    memcpy(dato, (*lista)->info, minimo(cantBytes, (*lista)->tam));
    return 1;
}

int verUltimoLista(const t_lista *lista, void *dato, unsigned cantBytes) {
    if(*lista == NULL) return 0;
    while((*lista)->siguiente) {
        lista = &(*lista)->siguiente;
    }
    memcpy(dato, (*lista)->info, minimo(cantBytes, (*lista)->tam));
    return 1;
}

int sacarPrimeroLista(t_lista *lista, void *dato, unsigned cantBytes) {
    t_nodo *aux = *lista;
    if(aux == NULL) return 0;
    *lista = aux->siguiente;
    memcpy(dato, aux->info, minimo(cantBytes, aux->tam));
    free(aux->info);
    free(aux);
    return 1;
}

int insertarAlComienzo(t_lista *lista, const void *dato, unsigned cantBytes) {
    t_nodo *nuevoNodo;
    nuevoNodo = (t_nodo*) malloc(sizeof(t_nodo));
    if(!nuevoNodo) return 0;
    nuevoNodo->info = malloc(cantBytes);
    if(!nuevoNodo->info) {
        free(nuevoNodo);
        return 0;
    }
    memcpy(nuevoNodo->info, dato, cantBytes);
    nuevoNodo->tam = cantBytes;
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
    return 1;
}

int comparar(const void *a, const void *b) {
    return *(int*) a - *(int*) b;
}


int insertarOrdenado(t_lista *lista, const void *dato, unsigned cantBytes, int (*comparar)(const void *a, const void *b), int duplicados) {
    t_nodo *nuevoNodo = (t_nodo*) malloc(sizeof(t_nodo));
    if (!nuevoNodo) return 0;

    nuevoNodo->info = malloc(cantBytes);
    if (!nuevoNodo->info) {
        free(nuevoNodo);
        return 0;
    }

    memcpy(nuevoNodo->info, dato, cantBytes);
    nuevoNodo->tam = cantBytes;

    if (listaVacia(lista)) {
        nuevoNodo->siguiente = NULL;
        *lista = nuevoNodo;
        return 1;
    }

    while ((*lista) && comparar((*lista)->info, nuevoNodo->info) < 0) {
        lista = &((*lista)->siguiente);
    }

    if ((*lista) && !duplicados && comparar((*lista)->info, nuevoNodo->info) == 0) {
        free(nuevoNodo->info);
        free(nuevoNodo);
        return 0;
    }

    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;

    return 1;
}


void map(t_lista *lista, void (*accion)(const void *dato)) {
    while(*lista) {
        accion((*lista)->info);
        lista = &(*lista)->siguiente;
    }
}

void mostrar(const void *dato) {
    int *num = (int*) dato;
    printf("%d\t", *num);
    return;
}

void testMap() {
    t_lista lista;
    int vec[] = {2, 3, 8, 1, 2};
    int i = 0;
    crearLista(&lista);
    while(i < sizeof(vec) / sizeof(vec[0])) {
        insertarOrdenado(&lista, &vec[i], sizeof(int), comparar, 0);
        i++;
    }
    map(&lista, mostrar);
    vaciarLista(&lista);
}



int main() {
    testMap();
    return 0;
}
