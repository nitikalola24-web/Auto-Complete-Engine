# Autocomplete Engine — Design Document

## Overview

The Autocomplete Engine is a C++ application that provides fast, frequency-ranked word suggestions based on a given prefix. It uses a Trie data structure at its core, layered with an adaptive learning system, persistent storage, and a clean OOP design.

---

## Architecture

main.cpp
└── AutocompleteEngine
└── Trie
└── TrieNode

Each layer has a single responsibility:

- **TrieNode** — holds character links, end-of-word flag, and frequency
- **Trie** — handles insert, search, prefix traversal, and DFS suggestion collection
- **AutocompleteEngine** — business logic: file I/O, ranking, recent searches, stats
- **main.cpp** — user interaction via CLI menu

---

## Data Structures Used

| Structure | Purpose |
|-----------|---------|
| Trie | Fast prefix matching and word storage |
| unordered_map | Child node mapping in TrieNode |
| unordered_map | Search statistics tracking |
| vector | Suggestion collection and recent searches |
| priority_queue | Top-K suggestion ranking |

---

## Core Algorithms

### Insert — O(L)
Traverses the Trie character by character, creating nodes where needed. Marks the final node as end-of-word and stores frequency.

### Search — O(L)
Traverses the Trie for the full word. Returns true only if the final node is marked as end-of-word.

### Prefix Traversal — O(L)
Traverses to the prefix node using `getNode()`. Returns nullptr if the prefix does not exist.

### DFS Suggestion Collection — O(N)
Performs a depth-first search from the prefix node, collecting all complete words below it along with their frequencies.

### Top-K Ranking — O(N log K)
Uses a max priority queue to extract the top K suggestions by frequency from the DFS results.

---

## File Formats

### dictionary.txt
One word per line. Loaded at startup and inserted into the Trie with a default frequency of 1.

apple
application
search
...

### frequency.txt
One word-frequency pair per line, space separated. Loaded at startup to override default frequencies. Saved on exit.

search 15
find 12
filter 10
...

---

## Feature Breakdown

### Frequency Ranking
Every word in the Trie stores a frequency count. Suggestions are sorted by frequency so more popular words appear first.

### Adaptive Learning
Every time a user searches a word via option 3, its frequency is incremented in both the Trie and the stats map. This makes the engine progressively smarter over sessions.

### Persistent Storage
On exit (option 6), all frequency data is written back to `frequency.txt`. On the next launch, these frequencies are reloaded, preserving the learned state.

### Recent Searches
The engine maintains a list of the last 10 unique searches. Duplicate entries are moved to the top rather than duplicated.

### Search Statistics Dashboard
Tracks total number of searches and displays the top 5 most searched words with their counts.

### Top-K Suggestions
Rather than returning all matches, the engine uses a priority queue to efficiently return only the top K results (default K=5).

---

## How to Build & Run

```bash
g++ -std=c++17 -Iinclude src/TrieNode.cpp src/Trie.cpp src/AutocompleteEngine.cpp src/main.cpp -o autocomplete
./autocomplete
```

---

## Possible Future Improvements

- Persistent storage for the full Trie (serialization)
- Multi-language dictionary support
- Web or GUI frontend
- Smarter ranking using recency + frequency combined score