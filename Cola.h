//
// Created by octa on 29/6/21.
//

#ifndef ALGORITMOSTPFINAL_COLA_H
#define ALGORITMOSTPFINAL_COLA_H

#include "global.h"
#include <list>
#include <iostream>

using namespace std;

class Cola{
private:
    int routerOrigen;
    int routerDestino;
    int bandWidth;
    list<struct paquete> cola;
public:
    Cola( int _routerOrigen, int _routerDestino);
    void print();
    void agregarPaquete(paquete paq);
    int leerPaquete(int indicePaquete, struct paquete * paq_p);
    int getPaquete(int indicePaquete, struct paquete * paq_p);
    void leerFront(struct paquete * paq);
    void leerBack(struct paquete * paq);
    void popFront();
    void popBack();

    //Ver estas funciones
    void crearColas(int o,int r,int d,int e,int p,int t);
    void Ordenar();
    int estadoCola();
    void  setanchoBanda(int aBanda);
    int   getanchoBanda();
    int tasaCola();
};

#endif //ALGORITMOSTPFINAL_COLA_H
