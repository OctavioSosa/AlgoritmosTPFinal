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
    void agregarArrayPaquetes(paquete * paq_p, int sizeArray);
    int leerPaquete(int indicePaquete, struct paquete * paq_p);
    int getPaquete(int indicePaquete, struct paquete * paq_p);
    void leerFront(struct paquete * paq);
    void leerBack(struct paquete * paq);
    void popFront();
    void popBack();
    void setBandWidth(int bandW);
    int  getBandWidth();
    int sizeCola();

    ///TODO: Ver estas funciones
    //void Ordenar();
    //int tasaCola();
};

#endif //ALGORITMOSTPFINAL_COLA_H
