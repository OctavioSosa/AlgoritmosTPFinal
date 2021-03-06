//
// Created by octa on 28/6/21.
//

#ifndef ALGORITMOSTPFINAL_ROUTER_H
#define ALGORITMOSTPFINAL_ROUTER_H

#include "Cola.h"

using namespace std;


class Router {
private:
    int idRouter;   //Num del router, es parte de la ip
    int idTerminal; //Num de la terminarl, es parte de la ip. Si no tiene es -1
    int cantEnlaces;//Cantidad de enlaces con otros routers y terminales
    Cola * colas_p; //Puntero a la primera cola del Array. El Array de colas
                    //se crea en el constructor. Hay una cola por cada enlace
    int * enlaces;  //Array con los enlaces directos del roter
    int * bWEnlaces;//Array con los bandWidth de cada enlace directo del roter
    //tablaForwarding tabla;

//Funciones privadas
    int getIndiceCola (int rDest);


public:
    Router(){};
    Router(int _idRouter, int _idTerminal, int _cantEnlaces, int * matrizEnlaces, int * matrizBandWidth);
    void setAll(int _idRouter, int _idTerminal, int _cantEnlaces, int * matrizEnlaces, int * matrizBandWidth);
    void transmitir( pag Pagina);
    void recibirPagina (pag Pagina);
    //void recibirPaquetes (paquete * paquetes);
    void ordenarColas();
    void reordenarColas(int * arrayCami);
    int armarPaginasRecibidas(pag * Pagina);
    int getTerminalId();
    int getCantidadEnlaces();
    int getBandWidthCola(int idCola);
    void getCola(paquete * arrayPaquetes, int sizeArray, int idCola);
    void enviarPaqueteACola(paquete paq, int idCola);
    int getSizeCola( int idCola);
    void borrarNPaquetesCola( int n, int idCola);
    int  getIdRouterFromCola(int idCola);
};


int getCantidadDeEnlaces(int idRout, int * matriz);
void getEnlaces(int * matrizEnlaces, int sizeMatrizEnlaces, int idRout, int * matriz);
void getBandWidthEnlaces(int * matrizBandWidth, int sizeMatrizBandWidth, int idRout, int * matriz);
int getIdTerminal(int idRout, int * arrayTermi);


#endif //ALGORITMOSTPFINAL_ROUTER_H
