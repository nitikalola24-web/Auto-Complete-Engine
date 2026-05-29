#include <iostream>
#include <string>
#include "AutocompleteEngine.h"

void printMenu() {
    std::cout << "\n=== Autocomplete Engine ===" << std::endl;
    std::cout << "1. Get suggestions" << std::endl;
    std::cout << "2. Insert a word" << std::endl;
    std::cout << "3. Search a word" << std::endl;
    std::cout << "4. Recent searches" << std::endl;
    std::cout << "5. Search statistics" << std::endl;
    std::cout << "6. Save & Exit" << std::endl;
    std::cout << "Enter choice: ";
}

int main() {
    AutocompleteEngine engine("dictionary.txt", "frequency.txt");

    int choice;
    std::string input;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::cout << "Enter prefix: ";
                std::getline(std::cin, input);

                if (input.empty()) {
                    std::cout << "Prefix cannot be empty." << std::endl;
                    break;
                }

                std::vector<std::string> suggestions = engine.getTopKSuggestions(input, 5);

                if (suggestions.empty()) {
                    std::cout << "No suggestions found for \"" << input << "\"." << std::endl;
                } else {
                    std::cout << "\nTop suggestions for \"" << input << "\":" << std::endl;
                    for (int i = 0; i < (int)suggestions.size(); i++) {
                        std::cout << i + 1 << ". " << suggestions[i] << std::endl;
                    }
                }
                break;
            }

            case 2: {
                std::cout << "Enter word to insert: ";
                std::getline(std::cin, input);

                if (input.empty()) {
                    std::cout << "Word cannot be empty." << std::endl;
                    break;
                }

                bool inserted = engine.insertWord(input);
                if (inserted) {
                    std::cout << "\"" << input << "\" inserted successfully." << std::endl;
                } else {
                    std::cout << "\"" << input << "\" already exists in the dictionary." << std::endl;
                }
                break;
            }

            case 3: {
                std::cout << "Enter word to search: ";
                std::getline(std::cin, input);

                if (input.empty()) {
                    std::cout << "Word cannot be empty." << std::endl;
                    break;
                }

                engine.recordSearch(input);
                std::cout << "\"" << input << "\" searched and frequency updated." << std::endl;
                break;
            }

            case 4: {
                engine.printRecentSearches();
                break;
            }

            case 5: {
                engine.printSearchStats();
                break;
            }

            case 6: {
                engine.saveFrequencies("frequency.txt");
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }

            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }

    return 0;
}