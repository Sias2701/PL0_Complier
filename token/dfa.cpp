#include "dfa.h"

void DFA::_add_transition(int start_state, char symbol, int end_state) {
    this->transitions[{start_state, symbol}] = end_state;
}

bool DFA::check_first(char symbol)  {
    return this->first.find(symbol) != this->first.end();
}