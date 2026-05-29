#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <vector>
#include <string>

class Trie {
private:
    TrieNode* root;

    void dfsCollect(TrieNode* node, std::string& current, std::vector<std::pair<std::string, int>>& results);
    void deleteTrie(TrieNode* node);

public:
    Trie();
    ~Trie();

    void insert(const std::string& word, int frequency = 1);
    bool search(const std::string& word);
    bool startsWith(const std::string& prefix);
    TrieNode* getNode(const std::string& prefix);
    std::vector<std::pair<std::string, int>> getSuggestions(const std::string& prefix);
    void updateFrequency(const std::string& word, int amount = 1);
};

#endif