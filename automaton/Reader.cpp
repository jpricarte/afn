//
// Created by jpricarte on 02/09/2020.
//

#include "Reader.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Automaton *Reader::read_automata(std::string file_name) {

    //File pointer n line string
    ifstream File(file_name);
    string line;

    //Automaton Created n auxiliar pointers
    Automaton* automaton = new Automaton();
    State* aux_state = nullptr;

    //Auxiliar vars
    string state_name = "";

    //Flag to control begin of automata
    bool isAutomaton = false;

    while (getline(File, line)) {

        // Remove unnecessary spaces
        string::iterator end_pos = remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        end_pos = remove(line.begin(), line.end(), '\t');
        line.erase(end_pos, line.end());

        // Don't read lines before start_automaton
        if (line == "start_automaton") {
            isAutomaton = true;
            continue;
        }
        else if (!isAutomaton)
            continue;

        //Jump Comments (Just in first char)]
        if (line[0] == '#')
            continue;

        //State Declaration
        else if (line[0] == '$') {
            state_name = Reader::get_name(line);
            StateType state_type = Reader::get_type(line);

            aux_state = new State(state_name);
            automaton->add_state(aux_state, state_type);
        }

        //Set state for next lines
        else if (line[0] == '&') {
            state_name = line.substr(1);
            aux_state = automaton->find_state(state_name);
        }

        else if (line[0] == '-') {
            // Isolate transition symbols
            size_t end_symbols = line.find(":");
            string transition_symbols = line.substr(1, end_symbols);

            // Arrival state
            State* arrival_state = automaton->find_state(line.substr(end_symbols+1));

            if (arrival_state != nullptr) {
                for (char transition_symbol : transition_symbols) {
                    aux_state->new_transition(transition_symbol, arrival_state);
                }
            }
        }

        // End file automaton
        if (line=="end_automaton") {
            break;
        }
    }

    File.close();
    return automaton;
}


string Reader::get_name(std::string line) {
    string return_string="";

    //Using while instead foreach 'cause then we can use $ in the state name
    int i = 1;
    int size = line.size();
    while (i < size && line[i] != ':') {
        return_string+=line[i];
        i++;
    }

    return return_string;
}


StateType Reader::get_type(std::string line) {

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
