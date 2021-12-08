//
// Created by popaa on 07/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <math.h>
#include <chrono>

using namespace std;

bool sortFunction(string a, string b) {
    return a.size() < b.size();
}

int main() {
    ifstream fin("../src/input.txt");
    string input_sequence;
    string pattern;
    string unique;
    string delimiter = " | ";
    vector<string> patterns;
    vector<string> output;
    map<string, int> mapping;
    int count_unique = 0;
    unsigned long long total_sum = 0;

    auto time1 = chrono::high_resolution_clock::now();

    while (getline(fin, input_sequence)) {
        pattern = input_sequence.substr(0, input_sequence.find(delimiter));
        unique = input_sequence.substr(input_sequence.find(delimiter) + delimiter.size(), input_sequence.size());
        output.clear();
        patterns.clear();

        stringstream ss(unique);
        while (getline(ss, unique, ' ')) {
            output.push_back(unique);
            count_unique = (unique.size() == 2 ||
                    unique.size() == 4 ||
                    unique.size() == 3 ||
                    unique.size() == 7) ? count_unique + 1 : count_unique;
        }

        stringstream ss2(pattern);
        while (getline(ss2, pattern, ' ')) {
            patterns.push_back(pattern);
        }

        sort(patterns.begin(), patterns.end(), sortFunction);

        string one = patterns[0], four = patterns[2], seven = patterns[1], eight = patterns[patterns.size() - 1];
        string five, six, zero, nine, three, two;
        sort(one.begin(), one.end());
        sort(four.begin(), four.end());
        sort(seven.begin(), seven.end());
        sort(eight.begin(), eight.end());
        mapping[one] = 1;
        mapping[four] = 4;
        mapping[seven] = 7;
        mapping[eight] = 8;

        string temp = four;
        temp.erase(remove(temp.begin(), temp.end(), one[0]), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), one[1]), temp.end());

        for (auto p: patterns) {
            sort(p.begin(), p.end());
            if (p.size() == 5 && p.find(temp[0]) != p.npos && p.find(temp[1]) != p.npos) {
                five = p;
                mapping[five] = 5;
            } else if (p.size() == 5 && p.find(one[0]) != p.npos && p.find(one[1]) != p.npos) {
                three = p;
                mapping[three] = 3;
            } else if (p.size() == 5) {
                two = p;
                mapping[two] = 2;
            } else if (p.size() == 6 && p.find(four[0]) != p.npos && p.find(four[1]) != p.npos
            && p.find(four[2]) != p.npos && p.find(four[3]) != p.npos) {
                nine = p;
                mapping[nine] = 9;
            } else if (p.size() == 6 && p.find(one[0]) != p.npos && p.find(one[1]) != p.npos) {
                zero = p;
                mapping[zero] = 0;
            } else if (p.size() == 6) {
                six = p;
                mapping[six] = 6;
            }
        }

        int number = 0;

        for (int index = 0; index < output.size(); index++) {
            sort(output[index].begin(), output[index].end());
            number += pow(10, output.size() - index - 1) * mapping[output[index]];
        }
        total_sum += number;
    }
    cout << count_unique << endl;
    cout << total_sum << endl;
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = time2 - time1;
    cout << ms_double.count() << "ms" << endl;
    return 0;
}
