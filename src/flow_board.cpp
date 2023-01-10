#include "flow_board.h"

#include <iostream>
#include <fstream>

using std::cout, std::endl, std::string, std::vector, std::ifstream;

flow_board::flow_board() {
    rows = -1;
    cols = -1;
    possible_lines = vector<vector<vector<char>>>(16);
    nodes = vector<vector<char>>();
}

flow_board::flow_board(std::string file_name) {
    ifstream inFS;
    string line;
    inFS.open(file_name);

    // Get the rows and columns from the first line of the input file
    getline(inFS, line);
    string r = line.substr(0, line.find(' '));
    string c = line.substr(line.find(' ') + 1);
    rows = stoi(r);
    cols = stoi(c);

    vector<vector<char>> vec(rows, vector<char>(cols, ' '));
    nodes = vec;

    // Sets the values of the graph indexes
    char index = 'X';
    for (int row = 0; row < rows; ++row) {
        getline(inFS, line);
        for (int col = 0; col < cols; ++col) {
            index = line.at(col);
            nodes.at(row).at(col) = index;
        }
    }
    inFS.close();
}

void flow_board::print_graph(bool letters) {
    // Print upper border
    cout << "┌";
    for (int col = 0; col < cols + 2; ++col) {
        cout << "─";
        if (col < cols - 1) {
            cout << "─";
        }
    }
    cout << "┐" << endl;

    // Print graph and side borders
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (col == 0) {
                cout << "│ ";
            }
            if (letters) {
                cout << color_string(string(1, nodes.at(row).at(col)), tolower(nodes.at(row).at(col)));
            }
            else {
                if (nodes.at(row).at(col) == ' ') {
                    cout << ' ';
                }
                else if (nodes.at(row).at(col) == tolower(nodes.at(row).at(col))) {
                    cout << color_string("+", tolower(nodes.at(row).at(col)));
                }
                else {
                    cout << color_string("⬤", tolower(nodes.at(row).at(col)));
                }
            }
            cout << " ";
            if (col == cols - 1) {
                cout << "│";
            }
        }
        cout << endl;
    }

    // Print bottom border
    cout << "└";
    for (int col = 0; col < cols + 2; ++col) {
        cout << "─";
        if (col < cols - 1) {
            cout << "─";
        }
    }
    cout << "┘" << endl;
}

string flow_board::color_string(string input, char color) {
    string result = "";
    switch (color) {
        // Red
        case 'r':
            result += "\x1b[38;2;255;0;0m";
            break;
        // Green
        case 'g':
            result += "\x1b[38;2;0;175;0m";
            break;
        // Blue
        case 'b':
            result += "\x1b[38;2;0;0;255m";
            break;
        // Yellow
        case 'y':
            result += "\x1b[38;2;255;255;0m";
            break;
        // Orange
        case 'o':
            result += "\x1b[38;2;255;175;0m";
            break;
        // Cyan
        case 'c':
            result += "\x1b[38;2;0;215;255m";
            break;
        // Magenta
        case 'm':
            result += "\x1b[38;2;215;0;175m";
            break;
        // Brown
        case 'w':
            result += "\x1b[38;2;95;95;0m";
            break;
        // Purple
        case 'p':
            result += "\x1b[38;2;175;0;255m";
            break;
        // White
        case 'h':
            result += "\x1b[38;2;255;255;255m";
            break;
        // Gray
        case 'a':
            result += "\x1b[38;2;128;128;128m";
            break;
        // Lime
        case 'l':
            result += "\x1b[38;2;0;255;0m";
            break;
        // Beige
        case 'e':
            result += "\x1b[38;2;215;215;175m";
            break;
        // Navy
        case 'n':
            result += "\x1b[38;2;0;0;175m";
            break;
        // Teal
        case 't':
            result += "\x1b[38;2;0;135;135m";
            break;
        // Pink
        case 'k':
            result += "\x1b[38;2;255;175;215m";
            break;
    }
    
    result += input;
    result += "\x1b[0m";

    return result;
}
