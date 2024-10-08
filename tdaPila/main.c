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
    printf("%d\n", *(char*) dato);
}

int mostrarPila(t_pila *pila, size_t tam, Mostrar mostrar) {
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    while(!esPilaVacia(pila)) {
        desapilar(pila, buffer, sizeof(char));
        mostrar(buffer);
    }
    free(buffer);
    return 1;
}

int sumaPilas(t_pila *pila1, t_pila *pila2, t_pila *pilaResult, Suma sum) {
    void *num1 = malloc(sizeof(char));
    if(!num1) return 0;
    void *num2 = malloc(sizeof(char));
    if(!num2) {
        free(num1);
        return 0;
    }
    char sobrante = '1';
    char aux;

    while(!esPilaVacia(pila1) && !esPilaVacia(pila2)) {
        desapilar(pila1, num1, sizeof(char));
        desapilar(pila2, num2, sizeof(char));
        if(suma(num1, num2) > 9) {
            apilar(pilaResult, &sobrante, sizeof(char));
            aux = (char) suma(num1, num2) % 10;
            apilar(pilaResult, &aux, sizeof(char));
        } else {
           aux = (char) suma(num1, num2);
           apilar(pilaResult, &aux, sizeof(char));
        }
    }

    while(!esPilaVacia(pila1)) {
        desapilar(pila1, num1, sizeof(char));
        apilar(pilaResult, num1, sizeof(char));
    }

    while(!esPilaVacia(pila1)) {
        desapilar(pila2, num2, sizeof(char));
        apilar(pilaResult, num2, sizeof(char));
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

    char vecPila1[] = {"2316"};
    char vecPila2[] = {"7315"};
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
    mostrarPila(&pilaResult, sizeof(char), mostrar);

    vaciarPila(&pila1);
    vaciarPila(&pila2);
    vaciarPila(&pilaResult);
    return;
}

int main() {
    ejercicio_2_7();
    return 0;
}
