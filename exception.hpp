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
        << "./graph [string] [double] [unsigned int] ... Generuje graf do souboru, "
        << "pravdepodobnost spojeni uzlu hranou a pocet uzlu." << endl;
    }
};

#endif
