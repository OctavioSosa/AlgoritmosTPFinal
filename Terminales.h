//
// Created by octa on 28/6/21.
//

#ifndef ALGORITMOSTPFINAL_TERMINALES_H
#define ALGORITMOSTPFINAL_TERMINALES_H

using namespace std;


//Objeto que representa una pc conectada a un unico router
class Terminal {
private:
    struct ip ip;         //direccion IP
    int * terminalesEnlace; //Es un array con los id de los routers de cada terminal

public:
    Terminal(){};
    Terminal(int _idTerminal, int _idRouter, int * _terminalesEnlace);
    void setAll(int _idTerminal, int _idRouter, int * _terminalesEnlace);
    int getIdRouter();
    void crearPagina( pag * Pag);
    void recibirPagina(pag Pagina);
};

extern int idPagina_global;



#endif //ALGORITMOSTPFINAL_TERMINALES_H
