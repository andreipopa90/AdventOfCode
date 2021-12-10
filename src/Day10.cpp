//
// Created by popaa on 09/12/2021.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isOpen(char ch){
    return ch == '(' || ch == '<' || ch == '{' || ch == '[';
}

bool isClose(char ch){
    return ch == ')' || ch == '>' || ch == '}' || ch == ']';
}

bool compareBrackets(char open, char close) {
    return open == '(' && close == ')' ||
           open == '[' && close == ']' ||
           open == '{' && close == '}' ||
           open == '<' && close == '>';
}

int getValue(char bracket) {
    switch (bracket) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        default:
            return 25137;
    }
}

int getScore(char bracket) {
    switch (bracket) {
        case '(':
            return 1;
        case '[':
            return 2;
        case '{':
            return 3;
        default:
            return 4;
    }
}

int main() {
    string line;
    ifstream fin("../src/input.txt");
    vector<char> input;
    vector<unsigned long long> scores;
    int result = 0;
    bool corrupted;
    unsigned long long score;

    while (getline(fin, line)) {
        input.clear();
        corrupted = false;
        score = 0;

        for (auto l: line) {
            if (isOpen(l)) {
                input.push_back(l);
            } else if (isClose(l)) {
                if (compareBrackets(input[input.size() - 1], l)) {
                    input.pop_back();
                } else {
                    result += getValue(l);
                    corrupted = true;
                    break;
                }
            }
        }

        if (input.size() >= 1 && !corrupted) {
            while (input.size() > 0) {
                score *= 5;
                score += (getScore(input[input.size() - 1]));
                input.pop_back();
            }
            scores.push_back(score);
        }

    }
    sort(scores.begin(), scores.end());
    cout << result << endl;
    cout << scores[scores.size() / 2] << endl;
    return 0;
}
