//
// Created by popaa on 12/2/2021.
//
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("../src/partOne.txt");
    string command;
    int steps;
    int horizontal = 0;
    int depth = 0;
    if (fin.is_open()) {
        while (fin>>command>>steps) {
            switch(command[0]) {
                case 'u':
                    depth -= steps;
                    break;
                case 'd':
                    depth += steps;
                    break;
                case 'f':
                    horizontal += steps;
                    break;
            }
        }
        cout << horizontal * depth << endl;
    }

    ifstream rin("../src/partTwo.txt");
    horizontal = 0;
    depth = 0;
    int aim = 0;
    if (rin.is_open()) {
        while (rin>>command>>steps) {
            switch(command[0]) {
                case 'u':
                    aim -= steps;
                    break;
                case 'd':
                    aim += steps;
                    break;
                case 'f':
                    horizontal += steps;
                    depth += (aim * steps);
                    break;
            }
        }

        cout << horizontal * depth << endl;
    }
    fin.close();
    rin.close();
    return 0;
}
