//
// Created by Jordi Pujol Ricarte on 02/09/2020.
//

#include "Reader.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Automaton *Reader::read_automata(std::string file_name) {

    //File pointer n line string
    ifstream file (file_name);
    if (!file.is_open())
        return nullptr;
    string line;

    //Automaton Created, auxiliaries pointer n StateType.
    auto* automaton = new Automaton();
    State* aux_state = nullptr;
    StateType state_type;

    //Auxiliary vars
    string state_name;

    //Flag to control begin of automata
    bool inScope = false;

    while (getline(file, line)) {

        // Remove unnecessary spaces
        string::iterator end_pos = remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        end_pos = remove(line.begin(), line.end(), '\t');
        line.erase(end_pos, line.end());

        // Check if the line is start/end_automaton
        inScope = check_scope(line, inScope);

        // If is out of scope of automaton, go to next line
        if (!inScope)
            continue;

        switch (line[0]) {
            case '$':
                state_name = Reader::get_name(line);
                state_type = Reader::get_type(line);
                aux_state = new State(state_name);
                automaton->add_state(aux_state, state_type);
                break;

            case '&':
                state_name = line.substr(1);
                aux_state = automaton->find_state(state_name);
                break;

            case '-':
                read_transition(line, automaton, aux_state);
                break;

            default:
                break;
        }

    }

    file.close();
    return automaton;
}


string Reader::get_name(std::string line) {
    string return_string;

    //Using while instead foreach 'cause then we can use $ in the state name
    int i = 1;
    int size = line.size();
    while (i < size && line[i] != ':') {
        return_string+=line[i];
        i++;
    }

    return return_string;
}


StateType Reader::get_type(const std::string& line) {

    StateType state_type;

    if (line.find("initial,final") != string::npos)
        state_type = StateType::INITIAL_FINAL;
    else if (line.find("initial") != string::npos)
        state_type = StateType::INITIAL;
    else if (line.find("final") != string::npos)
        state_type = StateType::FINAL;
    else
        state_type = StateType::NONE;

    return state_type;
}

void Reader::read_transition(const string& line, Automaton* automaton, State* aux_state) {
    size_t end_symbols = line.find(':');
    string transition_symbols = line.substr(1, end_symbols);

    // Arrival state
    State* arrival_state = automaton->find_state(line.substr(end_symbols+1));

    if (arrival_state != nullptr) {
        for (char transition_symbol : transition_symbols) {
            aux_state->new_transition(transition_symbol, arrival_state);
        }
    }
}

bool Reader::check_scope(const std::string& line, bool inScope) {
    if (line == "start_automaton") {
        return true;
    }

    if (line=="end_automaton") {
        return false;
    }

    else return inScope;
}
