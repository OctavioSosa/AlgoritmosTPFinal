//
// Created by octa on 28/6/21.
//

#ifndef ALGORITMOSTPFINAL_ROUTER_H
#define ALGORITMOSTPFINAL_ROUTER_H

using namespace std;


class Router {
private:
    int idRouter;   //Num del router, es parte de la ip
    int idTerminal; //Num de la terminarl, es parte de la ip. Si no tiene es -1
    int cantEnlaces;//Cantidad de enlaces con otros routers y terminales
    //Cola * colas[cantEnlaces];    //Una cola por cada enlace
    //tablaForwarding tabla;

public:
    Router(int _idRouter, int _cantEnlaces, int _idTerminal);
    void transmitir( pag Pagina);
};





#endif //ALGORITMOSTPFINAL_ROUTER_H
