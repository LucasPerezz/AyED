#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*Suma)(void *a, void *b);
typedef void (*Mostrar)(const void *dato);

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

    for(int i = 0; i < sizeof(vecPila1) / sizeof(vecPila1[0]; i++)) {
        apilar(&pila1, &vecPila1[i], sizeof(vecPila1[0]));
    };

    for(int i = 0; i < sizeof(vecPila2) / sizeof(vecPila2[0]; i++)) {
        apilar(&pila2, &vecPila2[i], sizeof(vecPila2[0]));
    };

    sumaPilas(&pila1, &pila2, &pilaResult, suma);
    mostrarPila(&pilaResult, sizeof(char));

    vaciarPila(&pila1);
    vaciarPila(&pila2);
    vaciarPila(&pilaResult);
    return;
}

void mostrar(const void *dato) {
    printf("%d\n", *(int*) dato);
}

int mostrarPila(t_pila *pila, size_t tam, Mostrar mostrar) {
    void *buffer = malloc(tam);
    if(!buffer) return 0;
    while(!esPilaVacia(pila)) {
        desapilar(pila, buffer, sizeof(char));

    }
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

int suma(void *a, void *b) {
    return *(int*) a + *(int*) b;
}

