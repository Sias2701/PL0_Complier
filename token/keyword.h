#ifndef __PL0_KEYWORD__
#define __PL0_KEYWORD__

#include <string>
#include <memory>
#include <map>

class TrieNode {
public:
    bool word_status = false;
    std::map<char, std::shared_ptr<TrieNode>> next;
    TrieNode() = default;
    ~TrieNode() = default;
};

class KeywordMatcher final{
private:
    std::shared_ptr<TrieNode> root;
    void _insert_trie(std::string keyword);
public:
    bool match(std::string text);
    KeywordMatcher();
    ~KeywordMatcher() = default;
};

#endif