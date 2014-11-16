// exception.hpp
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>

using namespace std;

class IOException {
public:
    IOException() {
        cerr << "Jejda, IO chybka." << endl;
    }
};

class IllegalArgumentException {
public:
    IllegalArgumentException() {
        cerr << "Hups, spatny format argumentu." << endl;
        cerr << "./graph [string] ... Spusti program, nacte ze souboru." << endl;
        cerr << "./graph [string] [unsigned int] [unsigned int] ... Generuje graf do souboru, " << endl;
        cerr << "druhy parametr je pocet uzlu a treti parametr pocet hran, ktere v prumeru" << endl;
        cerr << "vedou z nejakeho uzlu." << endl;
    }
};

#endif
