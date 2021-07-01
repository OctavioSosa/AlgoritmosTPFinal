//
// Created by octa on 30/6/21.
//

#include "Files.h"
//#include <iostream>
#include <fstream>
#include<bits/stdc++.h>

using namespace std;

/* \brief   Esta funcion copia la matriz contenida en el archivo "nombreArchivo" y la coloca en
 *          la matriz de enteros "matriz". Ademas devuelve la cantidad de Aristas que tiene el
 *          grafo que corresponde a la matriz del archivo.
 *          El archivo debe tener un formato especial. Debe contener una matriz de nxn que contenga numeros,
 *          correspodientes al peso de las aristas de los n nodos o '-' en caso de que no haya aristas
 *          entre esos nodos.
 * \param[in]   nombreArchivo: Nombre o path del archivo que se quiere abrir.
 * \param[out]  *matriz: puntero a una matriz de enteros donde se cargaran los datos del archivo.
 * \param[out]  *cantAristas: puntero a un entero donde se devolverá la cantidad de aristas que tiene el grafo
 *              correspondiente a la matriz
 * */
void getMatrizFromFile(string nombreArchivo, int * matriz, int * cantAristas)
{
    char buff;
    int cantidadAristas = 0;
    //int cantidadRouters = 0;
    int i;
    ifstream fileHandle;


    fileHandle.open( nombreArchivo, ios::in);    //Abrimos el archivo

    i = 0;
    fileHandle>>buff;   //Lee el primer char del archivo
    while( !fileHandle.eof()){
        if (buff == '\n'){          //Si llego al fin de linea, no hago nada
            //cantidadRouters++;        //La cantidad de routers es igual a la cantidad de lineas del archivo.
                                        // En la ultima linea no hay un '\n', asi que a esto es la cantidad de Routers - 1
        } else if (buff != '-'){    //Si el caracter es un numero y no es '-', pone ese numero en la matriz
             matriz[i]= buff - 48;      //Coloco el numero en la matriz. Para convertir el char en entero: buff - ((int)'0'), pero ((int)'0')=48
             if(matriz[i] != 0){
                 cantidadAristas++;      //Cuento la cantidad de aristas. Esto va a dar el doble de aristas porque cuenta en [i][j] y en [j][i]
             }
        } else {                    //Sino pone infinito en la matriz
            matriz[i] = INT_MAX;
        }

        i++;
        fileHandle>>buff;       //Va leyendo los caracteres sucesivos
    }

    cantidadAristas /= 2;   //Ahora si obtengo la cantidad de aristas
    //cantidadRouters++;      //Ahora si obtengo la cantidad de Routers

    fileHandle.close();

    *cantAristas = cantidadAristas;
}


/* \brief Retorna la cantidad de lineas que tiene el archivo "nombreArchivo"
 * \param[in]   nombreArchivo: Nombre o path del archivo que se quiere abrir.
 * \return      int: Retorna la cantidad de lineas del archivo
 * */
int getNuberLines(string nombreArchivo)
{
    int i = 0;
    string a;
    ifstream fileHandle;
    fileHandle.open( nombreArchivo, ios::in);    //Abrimos el archivo
    while (getline(fileHandle, a)){
        i++;
    }

    return i;
}



/* \brief   Esta funcion copia los numeros columna del archivo "nombreArchivo" y los coloca en
 *          un array de enteros llamado "matriz".
 * \param[in]   nombreArchivo: Nombre o path del archivo que se quiere abrir.
 * \param[out]  *matriz: puntero a un array de enteros donde se cargaran los datos del archivo.
 * */
void getTerminalesFromFile(string nombreArchivo, int * matriz)
{
    char buff;
    int i;
    ifstream fileHandle;


    fileHandle.open( nombreArchivo, ios::in);    //Abrimos el archivo

    i = 0;
    fileHandle>>buff;   //Lee el primer char del archivo
    while( !fileHandle.eof()){
        if (buff == '\n'){          //Si llego al fin de linea, no hago nada

        } else {                    //Sino pone infinito en la matriz
            matriz[i] = buff - 48;
        }

        i++;
        fileHandle>>buff;   //Lee los caracteres sucesivos
    }

    fileHandle.close();
}