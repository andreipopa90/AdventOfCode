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

void filterBits(vector<string> &bitsVector, vector<string> &dumpBits, char value, int index) {
    for (string o: bitsVector) {
        if (o[index] != value) {
            dumpBits.push_back(o);
        }
    }
    for (string d: dumpBits) {
        bitsVector.erase(bitsVector.begin() + distance(bitsVector.begin(),
                                                       find(bitsVector.begin(), bitsVector.end(), d)));
    }
}

bitset<SIZE> stringToBits(string bitString) {
    bitset<SIZE> result;
    for (int index = 0; index < bitString.size();  index++) {
        result.set(bitString.size() - index - 1, bitString[index] == '1');
    }
    return result;
}

int main(){
    ifstream fin("../src/partTwo.txt");
    ifstream rin("../src/partTwo.txt");
    string bitString;
    bitset<SIZE> gamma;
    bitset<SIZE> epsilon;
    vector<string> strings;
    char value;
    vector<string> oxygen;
    vector<string> carbon;
    bitset<SIZE> o2;
    bitset<SIZE> co2;
    vector<string> dump;
    bool found = false;

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
    strings.clear();

    if (rin.is_open()) {

        while (rin >> bitString) {
            strings.push_back(bitString);
        }
    }
    rin.close();

    calculateFrequency(frequency, strings);
    oxygen = strings;
    for (int i = 0; i < SIZE && !found; i++) {
        dump.clear();
        if (i >= 1) {
            calculateFrequency(frequency, oxygen);
        }
        value = (frequency[i][0] > frequency[i][1]) ? '0' : '1';
        filterBits(oxygen, dump, value, i);
        if (oxygen.size() == 1) {
            found = true;
            o2 = stringToBits(oxygen[0]);
        }
    }

    found = false;
    calculateFrequency(frequency, strings);
    carbon = strings;
    for (int i = 0; i < SIZE && !found; i++) {
        dump.clear();
        if (i >= 1) {
            calculateFrequency(frequency, carbon);
        }
        value = (frequency[i][0] <= frequency[i][1]) ? '0' : '1';
        filterBits(carbon, dump, value, i);
        if (carbon.size() == 1) {
            found = true;
            co2 = stringToBits(carbon[0]);
        }
    }
    cout << o2.to_ulong() * co2.to_ulong() << endl;

    return 0;
}
