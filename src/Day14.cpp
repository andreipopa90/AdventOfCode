//
// Created by popaa on 14/12/2021.
//
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;


int main() {
    ifstream fin("../src/input.txt");
    string polymer;
    string insertion;
    string a;
    unordered_map<string, char> rules;
    unordered_map<string, unsigned long long> polymer_parts;
    unordered_map<string, unsigned long long> temporary;
    unordered_map<char, unsigned long long> result;
    char first_letter;
    char last_letter;

    fin >> polymer;
    first_letter = polymer[0];
    last_letter = polymer[polymer.size() - 1];

    for (int i = 0; i < polymer.size() - 1; i++) {
        polymer_parts[polymer.substr(i, 2)] += 1;
    }

    while (getline(fin, insertion)) {
        if (insertion != "") {
            rules[insertion.substr(0, 2)] = insertion[insertion.size() - 1];
        }
    }

    fin.close();

    for (int i = 0; i < 40; i++) {
        for (auto r: rules) {
            string part1 = r.first;
            part1[1] = r.second;
            string part2 = r.first;
            part2[0] = r.second;
            if (polymer_parts.find(r.first) != polymer_parts.end()) {
                temporary[part1] += polymer_parts[r.first];
                temporary[part2] += polymer_parts[r.first];
            }
        }
        polymer_parts = temporary;
        temporary.clear();
        if (i == 9) {
            for (auto p: polymer_parts) {
                result[p.first[0]] += p.second;
                result[p.first[1]] += p.second;
            }

            result[first_letter] += 1;
            result[last_letter] += 1;

            unsigned long long maximum = 1;
            unsigned long long minimum = 184467440737095516;

            for (auto p: result) {
                maximum = max(maximum, p.second / 2);
                minimum = min(minimum, p.second / 2);
            }

            cout << (maximum - minimum) << endl;
        }
    }

    result.clear();

    for (auto p: polymer_parts) {
        result[p.first[0]] += p.second;
        result[p.first[1]] += p.second;
    }

    result[first_letter] += 1;
    result[last_letter] += 1;

    unsigned long long maximum = 1;
    unsigned long long minimum = 184467440737095516;

    for (auto p: result) {
        maximum = max(maximum, p.second / 2);
        minimum = min(minimum, p.second / 2);
    }

    cout << (maximum - minimum) << endl;

    return 0;
}
