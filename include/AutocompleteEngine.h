#ifndef AUTOCOMPLETEENGINE_H
#define AUTOCOMPLETEENGINE_H

#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>

class AutocompleteEngine {
private:
    Trie trie;
    std::vector<std::string> recentSearches;
    std::unordered_map<std::string, int> searchStats;
    int totalSearches;
    int maxRecentSearches;

    void loadDictionary(const std::string& filename);
    void loadFrequencies(const std::string& filename);
    void addToRecentSearches(const std::string& query);

public:
    AutocompleteEngine(const std::string& dictionaryFile, const std::string& frequencyFile);
    ~AutocompleteEngine();

    std::vector<std::string> getTopKSuggestions(const std::string& prefix, int k = 5);
    bool insertWord(const std::string& word);
    void recordSearch(const std::string& word);
    void saveFrequencies(const std::string& filename);

    void printRecentSearches();
    void printSearchStats();
};

#endif