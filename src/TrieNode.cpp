#include "TrieNode.h"

TrieNode::TrieNode() : isEndOfWord(false), frequency(0) {}

TrieNode::~TrieNode() {
    for (auto& pair : children) {
        delete pair.second;
    }
    children.clear();
}