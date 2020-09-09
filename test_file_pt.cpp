#include <iostream>
#include <tuple>
#include "automaton/Automaton.h"
#include "automaton/Reader.h"

using namespace std;
int main(int argc, char** argv) {

    string file_name, word, question;

    if (argc != 2) {
        cout << "Arquivo do automato > ";
        cin >> file_name;
    }
    else file_name = argv[1];

    Automaton* automata = Reader::read_automata(file_name);

    bool continue_running = true;
    do {
        cout << endl << "Palavra para verificar > ";
        cin >> word;

        if (automata->verify_word(word) )
            cout << endl << "Palavra aprovada" << endl;
        else
            cout << endl << "Palavra reprovada" << endl;

        cout << "Outra palavra? [s/N] > ";
        cin >> word;

        if (word.compare("s") == 0 || word.compare("S") == 0)
            continue_running = true;
        else
            continue_running = false;

    } while (continue_running);

    return 0;
}
