//
// Created by jpricarte on 02/09/2020.
//

#ifndef AUTOMATA_AUTOMATON_H
#define AUTOMATA_AUTOMATON_H


#include <iostream>
#include <vector>

enum StateType {
    INITIAL,
    FINAL,
    INITIAL_FINAL,
    NONE
};

class State {
public:
    std::string state_name;
    std::vector< std::tuple<char, State*> > transitions;

    State(std::string state_name);

    void new_transition(char c, State* new_state);
    State *find_next(char symbol);
};

class Automaton {
public:
    Automaton();
    Automaton(std::string alphabet);

    void add_state(State* new_state, StateType state_type);
    State* find_state(std::string state_name);

    bool is_final(State* state);
    std::vector<State*> get_states(State* actual_state, char c);

    bool verify_word(std::string word);
    bool verify_word(std::string word, State* actual_state);

    /// Getters n Setters
    const std::string &getAlphabet() const;
    void setAlphabet(const std::string &alphabet);

    const std::vector<State *> &getStates() const;
    void setStates(const std::vector<State *> &states);

    State *getFirstState() const;
    void setFirstState(State *firstState);

    const std::vector<State *> &getFinalStates() const;
    void setFinalStates(const std::vector<State *> &finalStates);

private:
    std::string alphabet;
    std::vector< State* > states;
    State* first_state;
    std::vector< State* > final_states;
};


#endif //AUTOMATA_AUTOMATON_H
