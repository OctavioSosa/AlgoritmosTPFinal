//
// Created by octa on 30/6/21.
//

#include "Algoritmos.h"
#include<bits/stdc++.h>

using namespace std ;

int cantNodos;    //TODO: ver de hacer cost[cantNodos][cantNodos]


void dijkstra(int src, int _cantNodos, int *cost ){
    cantNodos = _cantNodos;     //Seteo la variable global cantidad de nodos

    int dist[cantNodos];        //Distancia entre el nodo source y cada uno de los nodos
    int par[cantNodos];         //Contiene el nodo anterior por el cual se debe llegar hasta el nodo actual para seguir el camino mas corto
   //int cost[cantNodos][cantNodos]; //Es una matriz que explicita el peso de las aristas entre nodos. Si es infinito no hay aristas, si es 0 es el mismo
                                     // nodo, si hay un numero en cost[i][j] es el peso de la arista entre el nodo i y el nodo j (cost[i][j] = cost[j][i])
                                     //Aclaracion: como recibimos un puntero: cost[i][j] = cost [i*cantNodos + j]
    bool visited[100] = {0} ;   //Array de nodos visitados, inicializa todos en cero (ningun nodo fue visitado)

    fill(dist , dist+cantNodos  , INT_MAX ) ; //Llena el rango desde dist hasta dist+cantidad de aristas con el maximo valor para un entero

    dist[src] = 0 ;     //No hay distancia con sigo mismo
    par[src]  = -1 ;

    for(int g = 0  ; g < cantNodos-1 ; g++){
        int u = getMin( dist, visited);     //Obtengo el indice del nodo de menor distancia
        visited[u] = true ;                 //Coloco este nodo como visitado
        //cout<< " min = " << u <<endl;
        for(int v = 0 ; v < cantNodos ; v++){
            if(!visited[v] && (dist[u]+cost[u*cantNodos + v]) <  dist[v] && cost[u*cantNodos + v] != INT_MAX) {    //Pregunto si el nodo no fue visitado &&
                                                                                             //Compruebo que la distancia del nodo v(nodo adyacente (el nodo que estoy evaluando)), es mayor que la distancia del nodo u (nodo mas cercano) + el costo
                                                                                             // que tiene ir de u a v (Es decir comprueba que no te conviene ir al nodo v directamente, en lugar de ir al nodo u y de ahi al v) &&
                                                                                             //Pregunto si el nodo v es el nodo adyacente al nodo de menor distancia && C
                par[v] = u ;                    //Le digo que u es el nodo anterior a v
                dist[v] = dist[u] + cost[u*cantNodos + v]; //Corrijo la distancia que tengo al nodo v
            }
        }
    }

    display(dist , par) ;
}


/* \brief   Obtiene el nodo que tiene la distancia mínima. Solo tiene en cuenta
 *          los nodos que no han sido visitados
 *  \param  dist: Array de las distancias entre los nodos y el nodo source
 *  \param  visited: Nodos que han sido visitados                   //todo ver que es visitados
 *  \return Retorna el indice del nodo que tiene la menor distancia.
 * */
int getMin(int dist[] , bool visited[]){
    int key = 0 ;           //Indice del nodo que corresponde a la menor distancia
    int min = INT_MAX ;     //Minimo valor de distancia. Empieza en Infinito y se va disminuyendo hasta encontrar el minimo

    for(int i = 0; i < cantNodos ; i++){  //Recorro todoo el array dist, hasta encontrar el menor
        if( !visited[i] && dist[i] < min){  //Pregunto cual es el nodo que tiene menor distancia, que no haya sido visitado
            min = dist[i] ;
            key = i ;
        }
    }
    return key ;
}

/* \brief   Imprime la distancia y el camino mas corto para llegar de src a todos los nodos
*/
void display(int dist[] , int par[] ){
    for(int i = 0 ; i < cantNodos ; i++){
        int temp = par[i] ;
        cout<<i << " <- " ;
        while(temp!=-1)
        {
            cout<< temp << " <- " ;
            temp = par[temp] ;
        }
        cout<<endl;
        cout<<"::::Distance = " << dist[i] ;
        cout<<endl;
    }
}



/*int main(void) {
    cout<<"Enter cantidadNodos : " ;
    cin>>cantNodos ;
    cout<<"Enter cost matrix : \n" ;
    for(int i = 0 ;i < cantNodos ; i++){
        for(int j = 0 ; j< cantNodos ; j++){
            cin>>cost[i][j] ;
        }
    }
    int src ;
    cout<<"\nEnter source : " ;  cin>>src ;
    dijkstra(src) ;
}*/