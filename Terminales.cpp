//
// Created by octa on 28/6/21.
//
#include "global.h"
#include <cstdlib>
#include "Terminales.h"

using namespace std;


/* \brief Constructor de la clase Terminal.
 */
Terminal::Terminal(int _idTerminal, int _idRouter)
{
    ip.idTerminal = _idTerminal;
    ip.idRouter   = _idRouter;
}

/* \brief Crea una pagina a enviar. El destinatario y el tamaño de la
 *        pagina se designan aleatoriamente.
 *        El id de cada pagina es unico e incrementa: comienza en 0 y
 *        aumenta en 1 cada vez que se crea una página. No importa desde
 *        que terminal se cree.
 */
pag Terminal::crearPagina()
{
    struct pag Pagina;
    do {
        Pagina.sizePag  = rand() % 10;                              //Va de 0 a 9
        Pagina.ip_destino.idRouter   = rand() % cantidadRouters;    //Va de 0 a cantidadRouters-1
        Pagina.ip_destino.idTerminal = rand() % cantidadTerminales; //Va de 0 a cantidadTerminales-1
        Pagina.idPagina = idPagina_global;                          //Identificador de la pagina.
    }
    while (Pagina.ip_destino.idRouter != ip.idRouter && Pagina.ip_destino.idTerminal != ip.idTerminal);    //Para que no se envie un archivo a si mismo

    idPagina_global++;          //Aumento el identificador para que la proxima pagina tenga uno distinto

    return Pagina;
}