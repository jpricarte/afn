//
// Created by Jordi Pujol Ricarte on 02/09/2020.
//

#include "Automaton.h"
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

State::State(std::string state_name) {
    this->state_name = move(state_name);
    this->transitions = {};
}

void State::new_transition(char c, State *new_state) {
    this->transitions.emplace_back(c, new_state);
}

State *State::find_next(char symbol) {
    for(auto it = this->transitions.begin(); it < this->transitions.end(); it++) {
        if (get<0>(*it) == symbol) {
            return get<1>(*it);
        }
    }
    return nullptr;
}

Automaton::Automaton() {
    this->alphabet = "";
    this->states = {};
    this->first_state = nullptr;
    this->final_states = {};
}

Automaton::Automaton(string alphabet) {
    this->alphabet = move(alphabet);
    this->states = {};
    this->first_state = nullptr;
    this->final_states = {};
}

void Automaton::add_state(State *new_state, StateType state_type) {
    this->states.push_back(new_state);

    switch (state_type) {
        case StateType::INITIAL:
            if (this->first_state == nullptr)
                this->first_state = new_state;
            break;

        case StateType::INITIAL_FINAL:
            if (this->first_state == nullptr)
                this->first_state = new_state;
            // without break because the second part is equal

        case StateType::FINAL:
            this->final_states.push_back(new_state);
            break;

        case StateType::NONE:
        default:
            break;
    }
}

bool Automaton::is_final(State* state) {
    for (auto * final_state : this->final_states) {
        if (final_state == state) {
            return true;
        }
    }
    return false;
}

State* Automaton::find_state(string state_name) {
    for (auto & state : this->states) {
        if(state->state_name == state_name) {
            return state;
        }
    }
    return nullptr;
}

bool Automaton::verify_word(string word){
    return verify_word(word, this->first_state);
}

bool Automaton::verify_word(std::string word, State* actual_state){
    if (word.empty()) {
        if (this->is_final(actual_state))
            return true;
        else
            return false;
    }

    char first_char = word[0];
    string tail_word = word.substr(1);
    vector<State*> next_states = Automaton::get_states(actual_state, first_char);

    if (!next_states.empty())
        for (auto state : next_states) {
            if (verify_word(tail_word, state))
                return true;
        }
    return false;
}

vector<State *> Automaton::get_states(State *actual_state, char c) {
    vector<State*> next_states = {};

    for (auto transition : actual_state->transitions) {
        if (get<0>(transition) == c)
            next_states.push_back(get<1>(transition));
    }

    return next_states;
}

/// Getters n Setters

const string &Automaton::getAlphabet() const {
    return alphabet;
}

void Automaton::setAlphabet(const string &alphabet) {
    Automaton::alphabet = alphabet;
}

const vector<State *> &Automaton::getStates() const {
    return states;
}

void Automaton::setStates(const vector<State *> &states) {
    Automaton::states = states;
}

State *Automaton::getFirstState() const {
    return first_state;
}

void Automaton::setFirstState(State *firstState) {
    first_state = firstState;
}

const vector<State *> &Automaton::getFinalStates() const {
    return final_states;
}

void Automaton::setFinalStates(const vector<State *> &finalStates) {
    final_states = finalStates;
}