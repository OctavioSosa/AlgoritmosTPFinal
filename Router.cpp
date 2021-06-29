//
// Created by octa on 28/6/21.
//

#include "global.h"
#include "Router.h"

Router::Router(int _idRouter, int _cantEnlaces, int _idTerminal)
{
    idRouter    = _idRouter;
    idTerminal  = _idTerminal;
    cantEnlaces = _cantEnlaces;
    //Inicializar colas
}

/* \brief   Esta funcion recibe una pagina entera de la terminal asociada al router y se encarga
 *          de dividirla en paquetes para luego colocarlos en la cola correspondiente
 */
void Router::transmitir( pag Pagina)
{
    //Comprueba que no se quiera llamar a este metodo desde un router que no tenga terminal asociada
    if(idTerminal == -1){
        return;
    }

    //-----Definicion variables-----
    int cantidadPaquetes;
    cantidadPaquetes = Pagina.sizePag;
    struct ip ip_origen;
    ip_origen.idRouter = idRouter;
    ip_origen.idTerminal = idTerminal;

    //-----Divide la pagina en paquetes-----
    //Crea los paquetes y los inicializa
    struct paquete arrayPaquetes[cantidadPaquetes];
    for (int i = 0; i < cantidadPaquetes; ++i) {
        arrayPaquetes[i].sizePag    = cantidadPaquetes;
        arrayPaquetes[i].ip_destino = Pagina.ip_destino;
        arrayPaquetes[i].ip_origen  = ip_origen;
        arrayPaquetes[i].numPaquete = i;
    }

    //-----Coloca los paquetes en la cola correspondiente------
    //TODO: hacer
    /*for (int i = 0; i < cantidadPaquetes; ++i) {
        cola.addPaquete(arrayPaquetes[i]);
    }*/



}

