#include "Trie.h"
#include <algorithm>

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    deleteTrie(root);
}

void Trie::deleteTrie(TrieNode* node) {
    delete node;
}

void Trie::insert(const std::string& word, int frequency) {
    TrieNode* current = root;

    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }

    current->isEndOfWord = true;
    current->frequency = frequency;
}

bool Trie::search(const std::string& word) {
    TrieNode* current = root;

    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        current = current->children[ch];
    }

    return current->isEndOfWord;
}

bool Trie::startsWith(const std::string& prefix) {
    return getNode(prefix) != nullptr;
}

TrieNode* Trie::getNode(const std::string& prefix) {
    TrieNode* current = root;

    for (char ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return nullptr;
        }
        current = current->children[ch];
    }

    return current;
}

void Trie::dfsCollect(TrieNode* node, std::string& current, std::vector<std::pair<std::string, int>>& results) {
    if (node->isEndOfWord) {
        results.push_back({current, node->frequency});
    }

    for (auto& pair : node->children) {
        current.push_back(pair.first);
        dfsCollect(pair.second, current, results);
        current.pop_back();
    }
}

std::vector<std::pair<std::string, int>> Trie::getSuggestions(const std::string& prefix) {
    std::vector<std::pair<std::string, int>> results;

    TrieNode* prefixNode = getNode(prefix);
    if (prefixNode == nullptr) {
        return results;
    }

    std::string current = prefix;
    dfsCollect(prefixNode, current, results);

    std::sort(results.begin(), results.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    return results;
}

void Trie::updateFrequency(const std::string& word, int amount) {
    TrieNode* current = root;

    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            return;
        }
        current = current->children[ch];
    }

    if (current->isEndOfWord) {
        current->frequency += amount;
    }
}