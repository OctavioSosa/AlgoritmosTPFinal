//
// Created by octa on 29/6/21.
//
#include <list>
#include "Cola.h"
#include "global.h"
#include <stdio.h>
#include <cstdlib>


using namespace std;

/* \brief Constructor inicializa las variables privadas de la clase cola.
 *        El ancho de banda se designa aleatoriamente.
 */
Cola::Cola( int _routerOrigen, int _routerDestino, int _bandWidth )
{
    routerOrigen  = _routerOrigen;
    routerDestino = _routerDestino;
    bandWidth     = _bandWidth;         //Es la cantidad de paquetes que pueden pasar por ese enlace en un ciclo//aleatorio:(rand()%5)+1;
    //list<struct paq> cola;            //Ya esta creada en los atributos privados
}


/* \brief Hace lo mismo que el contructor. Se utiliza cuando se contruyo con el constructor vacio.
 */
void Cola::setAll( int _routerOrigen, int _routerDestino, int _bandWidth )
{
    routerOrigen  = _routerOrigen;
    routerDestino = _routerDestino;
    bandWidth     = _bandWidth;         //Es la cantidad de paquetes que pueden pasar por ese enlace en un ciclo//aleatorio:(rand()%5)+1;
    //list<struct paq> cola;            //Ya esta creada en los atributos privados
}


/* \brief Imprime todos los paquetes de la cola
 */
void Cola::print(){

    list<struct paquete>::iterator it;

    printf("IP DESTINO \t IP ORIGEN \t No PAQUETE \t ID PAG \t SIZE PAGINA\n");

    it = cola.begin();    //retorna un puntero al primer elemento

    for ( ; it != cola.end(); it++){
        printf("  %d.%d  \t  %d.%d  \t  %d  \t  %d  \t  %d  \n", it->ip_destino.idRouter, it->ip_destino.idTerminal, it->ip_origen.idRouter, it->ip_origen.idTerminal, it->numPaquete, it->idPagina, it->sizePag );
    }

}

/* \brief Agrega el paquete paq a la cola.
 * \param paq: paquete que se desea agregar.
 */
void Cola::agregarPaquete(struct paquete paq)
{
    cola.push_front(paq);   //Hacemos front por que debe consumir un poco menos de tiempo que back //igual esta clase debe tener punteros
}

/* \brief Agrega todos los paquetes, contenidos en un array, a la cola.
 * \param paq_q: puntero al primer elemento del array de paquetes.
 * \param sizeArray: cantidad de elementos del array de paquetes.
 */
void Cola::agregarArrayPaquetes(paquete * paq_p, int sizeArray)
{
    for (int i = 0; i < sizeArray && paq_p != NULL; ++i) {
        cola.push_front(*paq_p);
        paq_p++;
    }
}


/* \brief   Esta funcion devuelve el paquete correspondiente a la posicion indicePaquete. No elimina el paquete.
 * \param   indicePaqute: es un entero que indica la posicion del elemento (paquete) que se quiere obtener.
 * \param   paq: Es un puntero a un paquete, aquí se devolverá el paquete solicitado.
 * \return  Retorna 0 en caso de exito. -1 en caso contrario (por ejemplo si el índice es incorrecto)
 * */
int Cola::leerPaquete(int indicePaquete, struct paquete * paq_p)
{
    int cantidadElementos;
    list<struct paquete>::iterator it;
    cantidadElementos = cola.size();
    it = cola.begin();
    struct paquete paq;

    //Comprobacion de error de indice
    if(indicePaquete > cantidadElementos){
        return -1;
    }

    for (int i = 0; i < indicePaquete; ++i) {
        it++;
    }

    paq.ip_origen   = it->ip_origen;
    paq.ip_destino  = it->ip_destino;
    paq.numPaquete  = it->numPaquete;
    paq.idPagina    = it->idPagina;
    paq.sizePag     = it->sizePag;

    *paq_p = paq;
    //Comprobacion de error de asignacion
    if(paq_p == NULL){
        return -1;
    }

    return 0;
}


/* \brief   Esta funcion devuelve el paquete correspondiente a la posicion indicePaquete. Elimina el paquete.
 * \param   indicePaqute: es un entero que indica la posicion del elemento (paquete) que se quiere obtener.
 * \param   paq: Es un puntero a un paquete, aquí se devolverá el paquete solicitado.
 * \return  Retorna 0 en caso de exito. -1 en caso contrario (por ejemplo si el índice es incorrecto)
 * */
int Cola::getPaquete(int indicePaquete, struct paquete * paq_p)
{
    int cantidadElementos;
    list<struct paquete>::iterator it;
    cantidadElementos = cola.size();
    it = cola.begin();
    struct paquete paq;

    //Comprobacion de error de indice
    if(indicePaquete > cantidadElementos){
        return -1;
    }

    for (int i = 0; i < indicePaquete; ++i) {
        it++;
    }

    paq.ip_origen   = it->ip_origen;
    paq.ip_destino  = it->ip_destino;
    paq.numPaquete  = it->numPaquete;
    paq.idPagina    = it->idPagina;
    paq.sizePag     = it->sizePag;

    *paq_p = paq;

    //Comprobacion de error de asignacion
    if(paq_p == NULL){
        return -1;
    }

    it = cola.erase(it);    //Borra el paquete it, y devuelve el paquete siguiente que se vuelve a guardar en it

    return 0;
}


/* \brief Devuelve un puntero al primer elemento de la lista
 *        No elimina el elemento
 */
void Cola::leerFront(struct paquete * paq)
{
    *paq = cola.front();
}

/* \brief Devuelve un puntero al ultimo elemento de la lista
 *        No elimina el elemento
 */
void Cola::leerBack(struct paquete * paq)
{
    *paq = cola.back();
}

/* \brief Elimina el primer elemento de la lista*/
void Cola::popFront()
{
    cola.pop_front();
}

/* \brief Elimina el ultimo elemento de la lista*/
void Cola::popBack()
{
    cola.pop_back();
}

/* \brief Retorna la cantidad de elementos de la lista*/
int Cola::sizeCola()
{
    return cola.size();
}

/* \brief Setea la variable bandWidth (Ancho de banda)
 * \param bandW: entero que se quiere setear
 */
void Cola::setBandWidth(int bandW)
{
    bandWidth = bandW;
}

/* \brief retorna la variable bandWidth (Ancho de banda)*/
int Cola::getBandWidth()
{
    return bandWidth;
}


/* \brief retorna la variable routerDestino*/
int Cola::getRouterDestino()
{
   return routerDestino;
}


/* \brief retorna la variable routerOrigen
 * */
int Cola::getRouterOrigen()
{
    return routerOrigen;
}
