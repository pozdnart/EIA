// exception.hpp
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>

class IOException {
public:
    IOException() {
        cerr << "Jejda, IO chybka." << endl;
    }
};

class IllegalArgumentException {
public:
    IllegalArgumentException() {
        cerr << "Hups, spatny format argumentu." << endl
        << "./graph [string] ... Spusti program, nacte ze souboru." << endl
        << "./graph [string] [unsigned int] [unsigned int] ... Generuje graf do souboru, "
        << "druhy parametr je pocet uzlu a treti parametr pocet hran, ktere v prumeru"
        << "vedou z nejakeho uzlu." << endl;
    }
};

#endif
