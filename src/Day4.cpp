//
// Created by popaa on 12/4/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#define SIZE 5

using namespace std;

struct boardNumber {
    int value;
    bool chosen;
};

struct bingo {
    vector<boardNumber> board;
    int place;
};

bool has_line(vector<boardNumber> board) {
    int amount;
    for (int i = 0; i <= SIZE * (SIZE - 1); i += SIZE) {
        amount = 0;
        for (int j = i; j < SIZE + i; j++) {
            if (board[j].chosen) amount += 1;
        }
        if (amount == SIZE) return true;
    }
    return false;
}

bool has_column(vector<boardNumber> board) {
    int amount;
    for (int i = 0; i < SIZE; i++) {
        amount = 0;
        for (int j = i; j <= SIZE * (SIZE - 1) + i; j += SIZE) {
            if (board[j].chosen) amount += 1;
        }
        if (amount == SIZE) return true;
    }
    return false;

}

int main() {

    ifstream fin("../src/input.txt");
    string inputNumbers;
    string stringNumber;
    int number;
    char delim = ',';
    vector<int> drawn;
    vector<bingo> boards;
    vector<boardNumber> line;
    int place = 1;
    vector<boardNumber> result;
    vector<boardNumber> loser;
    int loserCall;
    int finalCall;
    bool found = false;

    if (fin.is_open()) {
        getline(fin, inputNumbers);
        stringstream ss(inputNumbers);
        while (getline(ss, stringNumber, delim)) {
            drawn.push_back(stoi(stringNumber));
        }
        while (fin >> number) {
            boardNumber bn;
            bn.value = number;
            bn.chosen = false;
            line.push_back(bn);
            if (line.size() == SIZE * SIZE) {
                bingo bingoBoard;
                bingoBoard.board = line;
                bingoBoard.place = 0;
                boards.push_back(bingoBoard);
                line.clear();
            }
        }

        for (int d: drawn) {
            for (auto &board: boards) {
                if (board.place == 0) {
                    for (auto &number: board.board) {
                        if (number.value == d) {
                            number.chosen = true;
                        }
                    }
                    if (has_line(board.board) || has_column(board.board)) {
                        board.place = place;
                        if (board.place == boards.size()) {
                            loserCall = d;
                            loser = board.board;
                            found = true;
                            break;
                        }
                        else if (board.place == 1) {
                            result = board.board;
                            finalCall = d;
                        }
                        place += 1;
                    }
                }
            }
            if (found) break;
        }
        int sum = 0;
        long output;
        for (auto value: result) {
            sum = (value.chosen) ? sum : sum + value.value;
        }
        output = sum * finalCall;
        cout << output << endl;
        sum = 0;
        for (auto value: loser) {
            sum = (value.chosen) ? sum : sum + value.value;
        }
        output = sum * loserCall;
        cout << output << endl;
    }
    fin.close();
    return 0;
}
