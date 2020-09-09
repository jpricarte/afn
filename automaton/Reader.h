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

    static StateType get_type(const std::string& line);

    static void read_transition(const std::string& line, Automaton* automaton, State* aux_state);

    static bool check_scope(const std::string& line, bool inScope);
};


#endif //AUTOMATA_READER_H
