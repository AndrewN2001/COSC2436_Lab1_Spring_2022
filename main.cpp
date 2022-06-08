#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

bool word_search(vector<vector<char>>&board, string command, int command_pos, int x_pos, int y_pos, int x_max, int y_max){
    if (x_pos < 0 || y_pos < 0 || x_pos > x_max || y_pos > y_max){
        return false;
    } else if (board[x_pos][y_pos] != command[command_pos]) {
        return false;
    } else if (command_pos == command.length() - 1)
        return true;

    char char_test = board[x_pos][y_pos];
    board[x_pos][y_pos] = '-';
    if (word_search(board, command, command_pos + 1, x_pos + 1, y_pos, x_max, y_max))
        return true;
    if (word_search(board, command, command_pos + 1, x_pos - 1, y_pos, x_max, y_max))
        return true;
    if (word_search(board, command, command_pos + 1, x_pos, y_pos + 1, x_max, y_max))
        return true;
    if (word_search(board, command, command_pos + 1, x_pos, y_pos - 1, x_max, y_max))
        return true;

    board[x_pos][y_pos] = char_test;
    return false;
}

bool exists(vector<vector<char>>&board, string word){
    for (int w = 0; w < board.size(); w++)
        for (int h = 0; h < board[w].size(); h++)
            if (board[w][h] == word[0])
                if (word_search(board, word, 0, w, h, board.size() - 1, board[w].size() - 1))
                    return true;
    return false;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");
    ifstream input(infilename);
    ofstream output(outfilename);

    int width, height;
    char value;
    string command;
    input >> height >> width;
    vector<vector<char>>board;

    for (int h = 0; h < height; h++){
        vector<char>temp;
        for (int w = 0; w < width; w++){
            input >> value;
            temp.push_back(value);
        }
        board.push_back(temp);
    }
    input >> command;
    if (exists(board, command)){
        cout << "True" << endl;
    } else{
        cout << "False" << endl;
    }
}
