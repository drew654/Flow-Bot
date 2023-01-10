#include "flow_board.h"

#include <iostream>
#include <fstream>

using std::cout, std::endl, std::string, std::vector, std::pair, std::ifstream;

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

void flow_board::solve() {
    // Map location of every pipe start and end
    vector<pair<int, int>> pipe_starts = vector<pair<int, int>>(16, {-1, -1});
    vector<pair<int, int>> pipe_ends = vector<pair<int, int>>(16, {-1, -1});
    vector<bool> nodes_present = vector<bool>(16, false);
    map_nodes(pipe_starts, pipe_ends, nodes_present);
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

void flow_board::map_nodes(vector<pair<int, int>>& pipe_starts, vector<pair<int, int>>& pipe_ends, vector<bool>& nodes_present) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            switch (nodes.at(row).at(col)) {
                case 'r':
                    if (pipe_starts.at(0).first == -1 && pipe_starts.at(0).second == -1) {
                        pipe_starts.at(0) = {row, col};
                    }
                    else {
                        pipe_ends.at(0) = {row, col};
                        nodes_present.at(0) = true;
                    }
                break;
                case 'g':
                    if (pipe_starts.at(1).first == -1 && pipe_starts.at(1).second == -1) {
                        pipe_starts.at(1) = {row, col};
                    }
                    else {
                        pipe_ends.at(1) = {row, col};
                        nodes_present.at(1) = true;
                    }
                break;
                case 'b':
                    if (pipe_starts.at(2).first == -1 && pipe_starts.at(2).second == -1) {
                        pipe_starts.at(2) = {row, col};
                    }
                    else {
                        pipe_ends.at(2) = {row, col};
                        nodes_present.at(2) = true;
                    }
                break;
                case 'y':
                    if (pipe_starts.at(3).first == -1 && pipe_starts.at(3).second == -1) {
                        pipe_starts.at(3) = {row, col};
                    }
                    else {
                        pipe_ends.at(3) = {row, col};
                        nodes_present.at(3) = true;
                    }
                break;
                case 'o':
                    if (pipe_starts.at(4).first == -1 && pipe_starts.at(4).second == -1) {
                        pipe_starts.at(4) = {row, col};
                    }
                    else {
                        pipe_ends.at(4) = {row, col};
                        nodes_present.at(4) = true;
                    }
                break;
                case 'c':
                    if (pipe_starts.at(5).first == -1 && pipe_starts.at(5).second == -1) {
                        pipe_starts.at(5) = {row, col};
                    }
                    else {
                        pipe_ends.at(5) = {row, col};
                        nodes_present.at(5) = true;
                    }
                break;
                case 'm':
                    if (pipe_starts.at(6).first == -1 && pipe_starts.at(6).second == -1) {
                        pipe_starts.at(6) = {row, col};
                    }
                    else {
                        pipe_ends.at(6) = {row, col};
                        nodes_present.at(6) = true;
                    }
                break;
                case 'w':
                    if (pipe_starts.at(7).first == -1 && pipe_starts.at(7).second == -1) {
                        pipe_starts.at(7) = {row, col};
                    }
                    else {
                        pipe_ends.at(7) = {row, col};
                        nodes_present.at(7) = true;
                    }
                break;
                case 'p':
                    if (pipe_starts.at(8).first == -1 && pipe_starts.at(8).second == -1) {
                        pipe_starts.at(8) = {row, col};
                    }
                    else {
                        pipe_ends.at(8) = {row, col};
                        nodes_present.at(8) = true;
                    }
                break;
                case 'h':
                    if (pipe_starts.at(9).first == -1 && pipe_starts.at(9).second == -1) {
                        pipe_starts.at(9) = {row, col};
                    }
                    else {
                        pipe_ends.at(9) = {row, col};
                        nodes_present.at(9) = true;
                    }
                break;
                case 'a':
                    if (pipe_starts.at(10).first == -1 && pipe_starts.at(10).second == -1) {
                        pipe_starts.at(10) = {row, col};
                    }
                    else {
                        pipe_ends.at(10) = {row, col};
                        nodes_present.at(10) = true;
                    }
                break;
                case 'l':
                    if (pipe_starts.at(11).first == -1 && pipe_starts.at(11).second == -1) {
                        pipe_starts.at(11) = {row, col};
                    }
                    else {
                        pipe_ends.at(11) = {row, col};
                        nodes_present.at(11) = true;
                    }
                break;
                case 'e':
                    if (pipe_starts.at(12).first == -1 && pipe_starts.at(12).second == -1) {
                        pipe_starts.at(12) = {row, col};
                    }
                    else {
                        pipe_ends.at(12) = {row, col};
                        nodes_present.at(12) = true;
                    }
                break;
                case 'n':
                    if (pipe_starts.at(13).first == -1 && pipe_starts.at(13).second == -1) {
                        pipe_starts.at(13) = {row, col};
                    }
                    else {
                        pipe_ends.at(13) = {row, col};
                        nodes_present.at(13) = true;
                    }
                break;
                case 't':
                    if (pipe_starts.at(14).first == -1 && pipe_starts.at(14).second == -1) {
                        pipe_starts.at(14) = {row, col};
                    }
                    else {
                        pipe_ends.at(14) = {row, col};
                        nodes_present.at(14) = true;
                    }
                break;
                case 'k':
                    if (pipe_starts.at(15).first == -1 && pipe_starts.at(15).second == -1) {
                        pipe_starts.at(15) = {row, col};
                    }
                    else {
                        pipe_ends.at(15) = {row, col};
                        nodes_present.at(15) = true;
                    }
                break;
            }
        }
    }
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
