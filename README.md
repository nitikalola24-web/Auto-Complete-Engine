# Autocomplete Engine

A feature-rich autocomplete engine built in C++ using a Trie data structure. This project progressively evolves from a brute-force prefix matcher to an adaptive, frequency-ranked suggestion system with persistent storage.

## Features

- Trie-based fast prefix matching
- DFS-powered suggestion generation
- Frequency-ranked suggestions using priority queue
- Adaptive learning system (boosts frequently searched words)
- Persistent frequency storage across sessions
- Search statistics dashboard
- Recent searches tracking
- Command-line interface

## Project Structure

autocomplete-engine/
├── README.md
├── dictionary.txt
├── frequency.txt
├── include/
│   ├── TrieNode.h
│   ├── Trie.h
│   └── AutocompleteEngine.h
├── src/
│   ├── TrieNode.cpp
│   ├── Trie.cpp
│   ├── AutocompleteEngine.cpp
│   └── main.cpp
└── docs/
└── design.md

## How to Build

```bash
g++ -std=c++17 -Iinclude src/TrieNode.cpp src/Trie.cpp src/AutocompleteEngine.cpp src/main.cpp -o autocomplete
```

## How to Run

```bash
./autocomplete
```

Make sure `dictionary.txt` is present in the root directory before running.

## Stages of Development

| Stage | Description |
|-------|-------------|
| 1 | Brute-force autocomplete with vector |
| 2 | Trie data structure (TrieNode + Trie) |
| 3 | Prefix search with startsWith() |
| 4 | Suggestion generation via DFS |
| 5 | AutocompleteEngine class (OOP separation) |
| 6 | File handling — load dictionary.txt |
| 7 | Command-line interface |
| 8 | Frequency ranking with unordered_map |
| 9 | Top-K suggestions via priority queue |
| 10 | Adaptive learning system |
| 11 | Persistent storage (frequency.txt) |
| 12 | Resume-level enhancements |

## Requirements

- C++17 or later
- A terminal / command-line environment

## Author

Built as a learning project to master Tries, OOP design, and systems thinking in C++.