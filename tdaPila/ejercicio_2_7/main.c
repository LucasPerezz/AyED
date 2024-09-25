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


typedef int (*Suma)(void *a, void *b);
typedef void (*Mostrar)(const void *dato);

int suma(void *a, void *b) {
    return *(int*) a + *(int*) b;
}


void mostrar(const void *dato) {
    printf("%d\n", *(int*) dato);
}

int mostrarPila(t_pila *pila, size_t tam, Mostrar mostrar) {
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    while(!esPilaVacia(pila)) {
        verTope(pila, buffer, tam);
        mostrar(buffer);
        desapilar(pila, buffer, sizeof(int));
    }
    free(buffer);
    return 1;
}

int sumaPilas(t_pila *pila1, t_pila *pila2, t_pila *pilaResult, Suma sum) {
    void *num1 = malloc(sizeof(int));
    if(!num1) return 0;
    void *num2 = malloc(sizeof(int));
    if(!num2) {
        free(num1);
        return 0;
    }
    int sobrante = 1;
    int aux;

    while(!esPilaVacia(pila1) && !esPilaVacia(pila2)) {
        desapilar(pila1, num1, sizeof(int));
        desapilar(pila2, num2, sizeof(int));
        if(suma(num1, num2) > 9) {
            apilar(pilaResult, &sobrante, sizeof(int));
            aux = suma(num1, num2) % 10;
            apilar(pilaResult, &aux, sizeof(int));
        } else {
           aux =  suma(num1, num2);
           apilar(pilaResult, &aux, sizeof(int));
        }
    }

    while(!esPilaVacia(pila1)) {
        desapilar(pila1, num1, sizeof(int));
        apilar(pilaResult, num1, sizeof(int));
    }

    while(!esPilaVacia(pila1)) {
        desapilar(pila2, num2, sizeof(int));
        apilar(pilaResult, num2, sizeof(int));
    }

    free(num1);
    free(num2);
    return 1;
}



void ejercicio_2_7() {
/********

    Resuelva el cálculo de la suma de dos números enteros de muchos dígitos (30 o muchos más)
    haciendo uso de dos pilas en las que almacena sólo los dígitos. Tenga en cuenta que debe utilizar una
    tercera pila en la que irá cargando los resultados parciales. Compruebe que obtiene idénticos
    resultados con ambas implementaciones de Pila (estática y dinámica).

*********/

    int vecPila1[] = {6, 1, 3, 2, 7};
    int vecPila2[] = {5, 1, 3, 7};
    t_pila pila1;
    t_pila pila2;
    t_pila pilaResult;

    crearPila(&pila1);
    crearPila(&pila2);
    crearPila(&pilaResult);

    for(int i = 0; i < sizeof(vecPila1) / sizeof(vecPila1[0]); i++) {
        apilar(&pila1, &vecPila1[i], sizeof(vecPila1[0]));
    };

    for(int i = 0; i < sizeof(vecPila2) / sizeof(vecPila2[0]); i++) {
        apilar(&pila2, &vecPila2[i], sizeof(vecPila2[0]));
    };

    sumaPilas(&pila1, &pila2, &pilaResult, suma);
    mostrarPila(&pilaResult, sizeof(int), mostrar);

    vaciarPila(&pila1);
    vaciarPila(&pila2);
    vaciarPila(&pilaResult);
    return;
}

int main() {
    ejercicio_2_7();
    return 0;
}
