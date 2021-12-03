//
// Created by popaa on 12/2/2021.
//
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

#define SIZE 12
using namespace std;

void calculateFrequency(int (&frequency)[SIZE][2], vector<string> strings) {
    for (int i = 0; i < SIZE; i++) {
        frequency[i][0] = frequency[i][1] = 0;
    }
    int index;
    for (string s: strings) {
        index = 0;
        for (char c: s) {
            frequency[index][1] = (c == '1') ? frequency[index][1] + 1 : frequency[index][1];
            frequency[index][0] = (c == '0') ? frequency[index][0] + 1 : frequency[index][0];
            index += 1;
        }
    }
}

int main(){
    ifstream fin("../src/partTwo.txt");
    ifstream rin("../src/partTwo.txt");
    string bitString;
    bitset<SIZE> gamma;
    bitset<SIZE> epsilon;
    vector<string> strings;
    char mostValue;
    char leastValue;
    vector<string> oxygen;
    vector<string> carbon;
    bitset<SIZE> o2;
    bitset<SIZE> co2;

    int frequency[SIZE][2];
    int index;
    if (fin.is_open()) {
        while (fin >> bitString) {
            strings.push_back(bitString);
        }
    }
    fin.close();
    calculateFrequency(frequency, strings);

    for (int i = 0; i < SIZE; i++) {
        if (frequency[i][0] > frequency[i][1]) {
            gamma.set(SIZE - i - 1, false);
            epsilon.set(SIZE - i - 1, true);
        } else {
            gamma.set(SIZE - i - 1, true);
            epsilon.set(SIZE - i - 1, false);
        }
    }
    cout << gamma.to_ulong() * epsilon.to_ulong() << endl;
    cout << "--------------------------------------------\n";


    if (rin.is_open()) {
        strings.clear();
        while (rin >> bitString) {
            strings.push_back(bitString);
        }
        calculateFrequency(frequency, strings);

        bool found = false;
        for (int i = 0; i < SIZE && !found; i++) {
            if (i >= 1) {
                calculateFrequency(frequency, oxygen);
            }
            oxygen.clear();
            for (string s: strings) {
                int equalOxygen = 0;
                for (int j = 0; j <= i; j++) {
                    mostValue = (frequency[j][0] > frequency[j][1]) ? '0' : '1';
                    if (s[j] == mostValue) {
                        equalOxygen += 1;
                    }
                }
                if (equalOxygen == i + 1) {
                    oxygen.push_back(s);
                }
            }
            if (oxygen.size() == 1) {
                found = true;
                for (index = 0; index < oxygen[0].size(); index++) {
                    o2.set(oxygen[0].size() - index - 1, oxygen[0][index] == '1');
                }
            }

        }

        for (string s: strings) {
            index = 0;
            for (char c: s) {
                frequency[index][1] = (c == '1') ? frequency[index][1] + 1 : frequency[index][1];
                frequency[index][0] = (c == '0') ? frequency[index][0] + 1 : frequency[index][0];
                index += 1;
            }
        }

        found = false;
        for (int i = 0; i < SIZE && !found; i++) {
            if (i >= 1) {
                calculateFrequency(frequency, carbon);
            }
            carbon.clear();
            for (string s: strings) {
                int equalCarbon = 0;
                for (int j = 0; j <= i; j++) {
                    leastValue = (frequency[j][0] <= frequency[j][1]) ?
                                 (frequency[j][0] > 0) ? '0' : '1' :
                                 (frequency[j][1] > 0) ? '1' : '0';
                    if (s[j] == leastValue) {
                        equalCarbon += 1;
                    }
                }
                if (equalCarbon == i + 1) {
                    carbon.push_back(s);
                }
            }
            if (carbon.size() == 1) {
                found = true;
                for (index = 0; index < carbon[0].size();  index++) {
                    co2.set(carbon[0].size() - index - 1, carbon[0][index] == '1');
                }
            }
        }

        cout << o2.to_ulong() * co2.to_ulong() << endl;

    }
    rin.close();
    return 0;
}
