#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

std::vector<std::string> read_wordle_js(std::istream&& is)
{
    std::vector<std::string> words;
    auto word = std::string{};
    while (is) { // check for EOF and potential I/O errors
        if (is.peek() == '"') { // look for an opening quote
            is >> std::quoted(word); // read the word in quotes and remove quotes
            if (word.length() == 5 && // must be 5-letter word
                std::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
                            [](char c) { return std::isalpha(c) && std::islower(c); }))
                words.push_back(word);
        } else
            is.get(); // skip one character
    }
    std::sort(std::begin(words), std::end(words));
    words.erase(std::unique(std::begin(words), std::end(words)), words.end());
    return words;
}

std::vector<std::string> filter(std::vector<std::string> words, const std::string pattern)
{
    auto pos = 0;
    for (int i = 0; i < pattern.length(); i++){
        if (std::isalpha(pattern[i])){ // if an alphabetic letter
            auto it = std::remove_if(std::begin(words), std::end(words),
                                     [pos, c=pattern[i]](const std::string& s) { return s[pos] != c; }); // letter not in place
            words.erase(it, std::end(words));
        }
        else if (pattern[i] == '+' && std::isalpha(pattern[++i])){
            auto it = std::remove_if(std::begin(words), std::end(words),
                                     [pos, c=pattern[i]](const std::string& s) {
                                            return (s[pos] == c) || // not in place
                                            std::find(std::begin(s), std::end(s), c) == std::end(s); // not present
            });
            words.erase(it, std::end(words));
        }
        else if (pattern[i] == '-' && std::isalpha(pattern[++i])){
            auto it = std::remove_if(std::begin(words), std::end(words),
                                     [c=pattern[i]](const std::string& s) {
                                            return std::find(std::begin(s), std::end(s), c) !=std::end(s); // has letter
            });
            words.erase(it, std::end(words));
        }
        pos++;
    }

    return std::move(words);
}

int main()
{
    std::string filename = "C:\\Users\\sebas\\OneDrive\\Billeder\\Dokumenter\\GitHub\\AAU\\SelectedTopicsInProgramming\\L3\\wordle.txt";
    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';

    const auto database = read_wordle_js(std::move(istrm)); /* read the database from the javascript file */
    auto words = database; // make a copy of the database
    auto word = words.front();
    auto guess = std::string{}; // allocate memory to store guess patterns
    while (words.size() > 1) {
        std::cout << words.size() << " words remaining\n";
        bool good = true;
        do {
            std::cout << "Enter a guess pattern: ";
            std::cin >> guess;
            /* sanitize: set good to false if input fails to follow the pattern */

        } while (!good);

        /* apply the filter on the words */
        words = filter(std::move(words), guess);

        /* pick and announce one of the words for the user to try */
        std::cout << "Remaining words: " << words.size() << "\n";
        std::cout << "Next word to try is: " << words.front() << "\n";
    }

    if (words.size() == 1) {
        std::cout << "Congratulations: " << words.front() << "\n";
    } else {
        std::cerr << "Something got messed up :-(\n";
    }
}