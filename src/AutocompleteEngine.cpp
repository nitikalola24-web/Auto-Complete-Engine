#include "AutocompleteEngine.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>

AutocompleteEngine::AutocompleteEngine(const std::string& dictionaryFile, const std::string& frequencyFile)
    : totalSearches(0), maxRecentSearches(10) {
    loadDictionary(dictionaryFile);
    loadFrequencies(frequencyFile);
}

AutocompleteEngine::~AutocompleteEngine() {}

void AutocompleteEngine::loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open dictionary file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            trie.insert(word, 1);
        }
    }

    file.close();
    std::cout << "Dictionary loaded successfully." << std::endl;
}

void AutocompleteEngine::loadFrequencies(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open frequency file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        int freq;
        if (iss >> word >> freq) {
            trie.insert(word, freq);
            searchStats[word] = freq;
        }
    }

    file.close();
    std::cout << "Frequencies loaded successfully." << std::endl;
}

void AutocompleteEngine::addToRecentSearches(const std::string& query) {
    for (auto it = recentSearches.begin(); it != recentSearches.end(); ++it) {
        if (*it == query) {
            recentSearches.erase(it);
            break;
        }
    }

    recentSearches.insert(recentSearches.begin(), query);

    if ((int)recentSearches.size() > maxRecentSearches) {
        recentSearches.pop_back();
    }
}

std::vector<std::string> AutocompleteEngine::getTopKSuggestions(const std::string& prefix, int k) {
    std::vector<std::pair<std::string, int>> allSuggestions = trie.getSuggestions(prefix);

    using PairType = std::pair<std::string, int>;
    auto cmp = [](const PairType& a, const PairType& b) {
        return a.second < b.second;
    };
    std::priority_queue<PairType, std::vector<PairType>, decltype(cmp)> pq(cmp);

    for (const auto& suggestion : allSuggestions) {
        pq.push(suggestion);
    }

    std::vector<std::string> topK;
    int count = 0;
    while (!pq.empty() && count < k) {
        topK.push_back(pq.top().first);
        pq.pop();
        count++;
    }

    return topK;
}

bool AutocompleteEngine::insertWord(const std::string& word) {
    if (trie.search(word)) {
        return false;
    }
    trie.insert(word, 1);
    return true;
}

void AutocompleteEngine::recordSearch(const std::string& word) {
    totalSearches++;
    searchStats[word]++;
    trie.updateFrequency(word, 1);
    addToRecentSearches(word);
}

void AutocompleteEngine::saveFrequencies(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save frequency file: " << filename << std::endl;
        return;
    }

    for (const auto& entry : searchStats) {
        file << entry.first << " " << entry.second << "\n";
    }

    file.close();
    std::cout << "Frequencies saved successfully." << std::endl;
}

void AutocompleteEngine::printRecentSearches() {
    if (recentSearches.empty()) {
        std::cout << "No recent searches." << std::endl;
        return;
    }

    std::cout << "\n=== Recent Searches ===" << std::endl;
    for (int i = 0; i < (int)recentSearches.size(); i++) {
        std::cout << i + 1 << ". " << recentSearches[i] << std::endl;
    }
}

void AutocompleteEngine::printSearchStats() {
    std::cout << "\n=== Search Statistics ===" << std::endl;
    std::cout << "Total searches made: " << totalSearches << std::endl;

    if (searchStats.empty()) {
        std::cout << "No search data available." << std::endl;
        return;
    }

    std::vector<std::pair<std::string, int>> stats(searchStats.begin(), searchStats.end());
    std::sort(stats.begin(), stats.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    std::cout << "\nTop searched words:" << std::endl;
    int limit = std::min((int)stats.size(), 5);
    for (int i = 0; i < limit; i++) {
        std::cout << i + 1 << ". " << stats[i].first << " (" << stats[i].second << " times)" << std::endl;
    }
}