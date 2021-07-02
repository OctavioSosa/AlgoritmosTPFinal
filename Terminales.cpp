//
// Created by octa on 28/6/21.
//
#include "global.h"
#include <cstdlib>
#include "Terminales.h"

using namespace std;


/* \brief Constructor de la clase Terminal.
 */
Terminal::Terminal(int _idTerminal, int _idRouter, int * _terminalesEnlace)
{
    ip.idTerminal = _idTerminal;
    ip.idRouter   = _idRouter;

    terminalesEnlace = _terminalesEnlace;

}

/* \brief Hace lo mismo que el contructor. Se utiliza cuando se contruyo con el constructor vacio.*/
void Terminal::setAll(int _idTerminal, int _idRouter, int * _terminalesEnlace)
{
    ip.idTerminal = _idTerminal;
    ip.idRouter   = _idRouter;

    terminalesEnlace = _terminalesEnlace;
}


/* \brief Crea una pagina a enviar. El destinatario y el tamaño de la
 *        pagina se designan aleatoriamente.
 *        El id de cada pagina es unico e incrementa: comienza en 0 y
 *        aumenta en 1 cada vez que se crea una página. No importa desde
 *        que terminal se cree.
 */
void Terminal::crearPagina( pag * Pag)
{
    struct pag Pagina;
    do {
        Pagina.sizePag  = rand()%8 + 2;                              //Va de 2 a 9
        Pagina.ip_destino.idTerminal = rand() % cantidadTerminales; //Va de 0 a cantidadTerminales-1
        Pagina.idPagina = idPagina_global;                          //Identificador de la pagina.
        Pagina.ip_destino.idRouter   = terminalesEnlace[Pagina.ip_destino.idTerminal];    //Va de 0 a cantidadRouters-1
    }
    while (Pagina.ip_destino.idTerminal == ip.idTerminal);    //Para que no se envie un archivo a si mismo


    idPagina_global++;          //Aumento el identificador para que la proxima pagina tenga uno distinto

    //Cargo los datos en la pagina return
    Pag->idPagina = Pagina.idPagina;
    Pag->sizePag  = Pagina.sizePag;
    Pag->ip_destino.idTerminal  = Pagina.ip_destino.idTerminal;
    Pag->ip_destino.idRouter    = Pagina.ip_destino.idRouter;
    return;
}

/* \brief   Devuelve el id del router asociado a esta terminal*/
int Terminal::getIdRouter()
{
    return ip.idRouter;
}


/* \brief Recibe una pagina y la descarta. No hace nada realmente*/
void Terminal::recibirPagina(pag Pagina)
{

}

