//
// Created by octa on 30/6/21.
//

#ifndef ALGORITMOSTPFINAL_ALGORITMOS_H
#define ALGORITMOSTPFINAL_ALGORITMOS_H

void dijkstra(int * arrayCaminos, int sizeArray, int src, int _cantNodos, int *cost );
void display (int dist[] , int par[] );
void getCamino(int * arrayC, int sizeArray, int par[] );
int getMin(int dist[] , bool visited[]);

#endif //ALGORITMOSTPFINAL_ALGORITMOS_H
