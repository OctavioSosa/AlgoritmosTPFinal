//
// Created by octa on 9/7/21.
//

#include <fstream>
#include <iostream>
#include "Prints.h"
#include "global.h"
#include "Router.h"

using namespace std;

void printMatrizNxN(string title, int * matrix, int n)
{
    cout<<" "<<title<<": "<<endl;
    for (int i = 0; i < n; ++i) {
        cout<<" ";
        for (int j = 0; j < n; ++j) {
            if(matrix[i * n + j] == 2147483647){
                cout << "- ";
            } else {
                cout << matrix[i * n + j] << " ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void printArray(string title, int * array, int sizeArray)
{
    cout<<" "<<title<<": "<<endl<<" ";
    for (int i = 0; i < sizeArray; ++i) {
        cout<<array[i]<<" ";
    }
    cout<<endl<<endl;
}

void printVar(string titleVar, int valueVar)
{
    cout<<" "<<titleVar<<": \t"<<valueVar<<endl;
}

void printSeparador()
{
    cout<<"------------------------------"<<endl<<endl;
}


void printPagina(pag * Pagina)
{
    cout<<"Pagina "<<Pagina->idPagina<<" (size "<<Pagina->sizePag<<") -> "<<Pagina->ip_destino.idRouter<<"."<<Pagina->ip_destino.idTerminal<<endl;
}

void printColas(Router * arrayRou, int idRouter)
{
    int cantColas = arrayRou[idRouter].getCantidadEnlaces()+1;
    Cola auxColas[cantColas];
    int maxSize = 0;//Guarda el size de la cola de mayor tamaño
    paquete paqAux;


    //Guardo todos los paquetes de las colas, en el array de colas auxiliares
    for (int i = 0; i < cantColas; ++i) {
        int sizeC = arrayRou[idRouter].getSizeCola(i);
        if(sizeC > 0) {
            if (maxSize < sizeC){
                maxSize = sizeC;        //Guardo el mayor size de las colas
            }
            paquete auxPaquetes[sizeC];
            arrayRou[idRouter].getCola(&auxPaquetes[0], sizeC, i);  //Pongo todos los paquetes de la cola en el array aux de paquetes
            auxColas[i].agregarArrayPaquetes( &auxPaquetes[0], sizeC);    //Pongo el array de paquetes en la cola auxiliar i
        }
    }

    //Imprimo el nombre del router
    cout<<"Router "<<idRouter<<": "<<endl;

    for (int i = 0; i < cantColas; ++i) {
        cout<<"  Cola "<<i<<" \t\t";
    }
    cout<<endl;
    for (int i = 0; i < cantColas; ++i) {
        cout<<"PagID|NumPaq"<<" \t";
    }
    cout<<endl;

    //Imprimo todas las colas
    for (int k = 0; k < maxSize; ++k) {
        for (int i = 0; i < cantColas; ++i) {
            if(auxColas[i].sizeCola() > k){
                auxColas[i].leerPaquete(k, &paqAux);
                cout<<"\t"<<paqAux.idPagina<<" \t"<<paqAux.numPaquete<<" \t\t";
            }

        }
        cout<<endl;
    }
    cout<<endl;

}




void printColasRouters(Router * arrayRou, int sizeArray)
{
    int cantColas[sizeArray];
    Cola arrayAuxColas [sizeArray][sizeArray];
    int maxSize = 0;//Guarda el size de la cola de mayor tamaño
    paquete paqAux;

    for (int i = 0; i < sizeArray; ++i) {
        cantColas[i] = arrayRou[i].getCantidadEnlaces() + 1;
    }


    //Guardo todos los paquetes de las colas, en el array de colas auxiliares
    for (int i = 0; i < sizeArray; ++i) {
        for (int j = 0; j < cantColas[i]; ++j) {

            int sizeC = arrayRou[i].getSizeCola(j);
            if (sizeC > 0) {
                if (maxSize < sizeC) {
                    maxSize = sizeC;        //Guardo el mayor size de las colas
                }
                paquete auxPaquetes[sizeC];
                arrayRou[i].getCola(&auxPaquetes[0], sizeC, j);  //Pongo todos los paquetes de la cola en el array aux de paquetes
                arrayAuxColas[i][j].agregarArrayPaquetes(&auxPaquetes[0], sizeC);    //Pongo el array de paquetes en la cola auxiliar i
            }

        }
    }

    //Imprimo el nombre del router
    for (int i = 0; i < sizeArray; ++i) {
        cout << "Router " << i << ": \t\t" ;
        for (int j = 0; j < arrayRou[i].getCantidadEnlaces(); ++j) {
            cout<<"\t\t\t\t";
        }
    }
    cout << endl;

    //Imprimo los nombres de las colas
    for (int i = 0; i < sizeArray; ++i) {
        for (int j = 0; j < cantColas[i]; ++j) {
            cout << "  Cola " << j << " \t\t";
        }
    }
    cout << endl;

    //Imprimo que es cada columna
    for (int i = 0; i < sizeArray; ++i) {
        for (int j = 0; j < cantColas[i]; ++j) {
            cout << "PagID|NumPaq" << " \t";
        }
    }
    cout << endl;

    //Imprimo todas las colas
    for (int k = 0; k < maxSize; ++k) {

        for (int i = 0; i < sizeArray; ++i) {
            for (int j = 0; j < cantColas[i]; ++j) {
                if (arrayAuxColas[i][j].sizeCola() > k) {
                    arrayAuxColas[i][j].leerPaquete(k, &paqAux);
                    cout << "\t" << paqAux.idPagina << " \t" << paqAux.numPaquete << " \t\t";
                } else {
                    cout<< "\t  \t  \t\t";
                }
            }
        }
        cout << endl;

    }

    cout << endl;
}