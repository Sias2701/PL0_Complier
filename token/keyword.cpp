#include "token/keyword.h"

KeywordMatcher::KeywordMatcher() {
    this->root = std::make_shared<TrieNode>();
    this->_insert_trie("var");
    this->_insert_trie("const");
    this->_insert_trie("begin");
    this->_insert_trie("end");
    this->_insert_trie("return");
    this->_insert_trie("typedef");
    this->_insert_trie("procedure");
    this->_insert_trie("operation");
    this->_insert_trie("if");
    this->_insert_trie("then");
    this->_insert_trie("else");
    this->_insert_trie("for");
    this->_insert_trie("until");
    this->_insert_trie("step");
    this->_insert_trie("repeat");
    this->_insert_trie("do");
    this->_insert_trie("while");
    this->_insert_trie("odd");
    this->_insert_trie("read");
    this->_insert_trie("write");
    this->_insert_trie("call");
}

void KeywordMatcher::_insert_trie(std::string keyword) {

    std::shared_ptr<TrieNode> current = root;
    
    for (char ch : keyword) {
        if (current->next.find(ch) == current->next.end()) {
            current->next[ch] = std::make_shared<TrieNode>();
        }
        current = current->next[ch];
    }
    current->word_status = true;

}

bool KeywordMatcher::match(std::string text) {
    std::shared_ptr<TrieNode> current = root;
    for (char ch : text) {
        if (current->next.find(ch) == current->next.end()) {
            return false;
        }
        current = current->next[ch];
    }
    return current->word_status;
}