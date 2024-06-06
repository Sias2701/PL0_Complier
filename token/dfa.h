#ifndef __PL0_DFA__
#define __PL0_DFA__

#include "token.h"
#include "stream/input_stream.h"

#include <unordered_set>
#include <unordered_map>
#include <utility>

class DFA : virtual public AbstractTokenParser {
protected:
    std::unordered_set<int> states;
    std::unordered_set<char> alphabet;
    std::unordered_set<char> first;
    std::unordered_set<int> accept_states;
    int start_state;
    int current_state;

    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    std::unordered_map<std::pair<int, char>, int, pair_hash> transitions;
    void _add_transition(int start_state, char symbol, int end_state);

public:
    DFA() = default;
    ~DFA() = default;
    virtual Token parse(std::shared_ptr<InputStream> stream) {
        Token ret;
        ret.type = TokenType::VOID;
        return ret;
    };

    void reset() { this->current_state = this->start_state; };

    bool check_first(char symbol);
};

#endif