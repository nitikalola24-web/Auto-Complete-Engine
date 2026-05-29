#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    int frequency;

    TrieNode();
    ~TrieNode();
};

#endif