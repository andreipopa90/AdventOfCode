//
// Created by popaa on 06/12/2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    string input;
    char delim = ',';
    vector<unsigned long long> lantern_fish_part1;
    vector<unsigned long long> lantern_fish_part2;

    for (int i = 0; i <= 8; i++) {
        lantern_fish_part1.push_back(0);
        lantern_fish_part2.push_back(0);
    }

    ifstream fin("../src/input.txt");
    while (getline(fin, input, delim)) {
        lantern_fish_part1[stoi(input)] += 1;
        lantern_fish_part2[stoi(input)] += 1;
    }

    for (int i = 1; i <= 80; i++) {
        unsigned long long temp = lantern_fish_part1[0];
        for (int j = 1; j < lantern_fish_part1.size(); j++) {
            lantern_fish_part1[j - 1] = lantern_fish_part1[j];
        }
        lantern_fish_part1[8] = temp;
        lantern_fish_part1[6] += temp;
    }

    unsigned long long result = 0;
    for (unsigned long long fish: lantern_fish_part1) {
        result += fish;
    }
    cout << result << endl;

    for (int i = 1; i <= 256; i++) {
        unsigned long long temp = lantern_fish_part2[0];
        for (int j = 1; j < lantern_fish_part2.size(); j++) {
            lantern_fish_part2[j - 1] = lantern_fish_part2[j];
        }
        lantern_fish_part2[8] = temp;
        lantern_fish_part2[6] += temp;
    }

    result = 0;
    for (unsigned long long fish: lantern_fish_part2) {
        result += fish;
    }
    cout << result << endl;
}