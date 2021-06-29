//
// Created by octa on 28/6/21.
//

#ifndef ALGORITMOSTPFINAL_TERMINALES_H
#define ALGORITMOSTPFINAL_TERMINALES_H


//Objeto que representa una pc conectada a un unico router
class Terminal {
private:
    struct ip ip;         //direccion IP

public:
    Terminal(int _idTerminal, int _idRouter);
    pag crearPagina();
};



#endif //ALGORITMOSTPFINAL_TERMINALES_H
