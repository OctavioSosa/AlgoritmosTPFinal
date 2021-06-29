//
// Created by octa on 28/6/21.
//

#ifndef ALGORITMOSTPFINAL_GLOBAL_H
#define ALGORITMOSTPFINAL_GLOBAL_H

//Variables globales
extern int cantidadRouters;
extern int cantidadTerminales;

struct ip {
    int idRouter;   //Num del router.
    int idTerminal; //Num de la terminarl.
};

struct pag {
    int sizePag;
    struct ip ip_destino;
};

/* Los paquetes son un fragmento de una pagina. En la practica
 * son como una pagina pero tienen el size en 1.
 * Este seria el protocolo de transmision ya que no tenemos data real.
 * */
struct paquete {
    struct ip ip_destino;   //IP de destino
    struct ip ip_origen;    //IP de origen
    int numPaquete;         //Identificador del paquete. Va del 0 a sizePag-1
    int sizePag;            //Cantidad de paquetes que forman la página
};

#endif //ALGORITMOSTPFINAL_GLOBAL_H
