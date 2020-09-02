//
// Created by jpricarte on 02/09/2020.
//

#ifndef AUTOMATA_READER_H
#define AUTOMATA_READER_H


#include "Automaton.h"

class Reader {
public:
    static Automaton* read_automata(std::string file_name);

    static std::string get_name(std::string line);

    static StateType get_type(std::string line);
};


#endif //AUTOMATA_READER_H
