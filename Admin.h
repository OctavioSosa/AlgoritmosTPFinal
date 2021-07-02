//
// Created by octa on 1/7/21.
//

#ifndef ALGORITMOSTPFINAL_ADMIN_H
#define ALGORITMOSTPFINAL_ADMIN_H

#include "global.h"
#include "Terminales.h"


using namespace std;



class Admin{
private:
    int cantRouters;
    int * matrizCaminos;        //Contiene la info del router siguiente para llegar al cada router
    int * matrizCostos;         //Matriz igual a la del grafo pero se tienen los costos en lugar del bandWidth
    int * matrizPaquetesEnColas;//Matriz igual a la del grafo pero se tiene la cantidad de paquetes que hay en cada colas
    int * grafo;                //Matriz que representa el grafo de routers y enlaces

public:
    Admin(int * grafo, int _cantidadRouters);
    Admin(){};
    void setMatrizPaquetesEnColas();
    void setMatrizCaminos();
    void getCaminosRouter(int * arrayCam, int idRouter);
    int getCaminoRouterADestino(int idRouter, int idRouDestino);
    void setMatrizCostos(int * matrizCost, int * matizGrafo, int * matrizPaqColas);

};

//Funciones de envios
void enviarPaginaATerminal(pag * Pagina, Terminal * term);


#endif //ALGORITMOSTPFINAL_ADMIN_H
