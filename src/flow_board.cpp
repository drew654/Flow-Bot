#include "flow_board.h"

#include <iostream>
#include <fstream>

using std::cout, std::endl, std::string, std::vector, std::pair, std::ifstream;

flow_board::flow_board() {
    rows = -1;
    cols = -1;
    possible_paths = vector<vector<vector<vector<char>>>>(16);
    nodes = vector<vector<char>>();
    vector<pair<int, int>> pipe_starts = vector<pair<int, int>>(16, {-1, -1});
    vector<pair<int, int>> pipe_ends = vector<pair<int, int>>(16, {-1, -1});
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

    possible_paths = vector<vector<vector<vector<char>>>>(16);
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
    vector<pair<int, int>> vec2(16, {-1, -1});
    pipe_starts = vec2;
    pipe_ends = vec2;
}

void flow_board::solve() {
    // Map location of every pipe start and end
    map_nodes();

    // Find possible paths for each pipe
    for (unsigned int i = 0; i < pipe_starts.size(); ++i) {
        // If there is a pipe start
        if (pipe_starts.at(i).first != -1 && pipe_starts.at(i).second != -1) {
            // Find possible paths
            vector<vector<char>> cur = vector<vector<char>>(nodes);
            build_paths_at(pipe_starts.at(i).first, pipe_starts.at(i).second, int_to_color(i), cur);
        }
    }

    for (unsigned int r = 0; r < possible_paths.at(color_to_int('r')).size(); ++r) {
        for (unsigned int g = 0; g < possible_paths.at(color_to_int('g')).size(); ++g) {
            for (unsigned int b = 0; b < possible_paths.at(color_to_int('b')).size(); ++b) {
                for (unsigned int y = 0; y < possible_paths.at(color_to_int('y')).size(); ++y) {
                    for (unsigned int o = 0; o < possible_paths.at(color_to_int('o')).size(); ++o) {
                        for (unsigned int c = 0; c < possible_paths.at(color_to_int('c')).size(); ++c) {
                            for (unsigned int m = 0; m < possible_paths.at(color_to_int('m')).size(); ++m) {
                                for (unsigned int w = 0; w < possible_paths.at(color_to_int('w')).size(); ++w) {
                                    for (unsigned int p = 0; p < possible_paths.at(color_to_int('p')).size(); ++p) {
                                        for (unsigned int h = 0; h < possible_paths.at(color_to_int('h')).size(); ++h) {
                                            for (unsigned int a = 0; a < possible_paths.at(color_to_int('a')).size(); ++a) {
                                                for (unsigned int l = 0; l < possible_paths.at(color_to_int('l')).size(); ++l) {
                                                    for (unsigned int e = 0; e < possible_paths.at(color_to_int('e')).size(); ++e) {
                                                        for (unsigned int n = 0; n < possible_paths.at(color_to_int('n')).size(); ++n) {
                                                            for (unsigned int t = 0; t < possible_paths.at(color_to_int('t')).size(); ++t) {
                                                                for (unsigned int k = 0; k < possible_paths.at(color_to_int('k')).size(); ++k) {
                                                                    vector<vector<vector<char>>> set_of_paths = {
                                                                        possible_paths.at(color_to_int('r')).at(r),
                                                                        possible_paths.at(color_to_int('g')).at(g),
                                                                        possible_paths.at(color_to_int('b')).at(b),
                                                                        possible_paths.at(color_to_int('y')).at(y),
                                                                        possible_paths.at(color_to_int('o')).at(o),
                                                                        possible_paths.at(color_to_int('c')).at(c),
                                                                        possible_paths.at(color_to_int('m')).at(m),
                                                                        possible_paths.at(color_to_int('w')).at(w),
                                                                        possible_paths.at(color_to_int('p')).at(p),
                                                                        possible_paths.at(color_to_int('h')).at(h),
                                                                        possible_paths.at(color_to_int('a')).at(a),
                                                                        possible_paths.at(color_to_int('l')).at(l),
                                                                        possible_paths.at(color_to_int('e')).at(e),
                                                                        possible_paths.at(color_to_int('n')).at(n),
                                                                        possible_paths.at(color_to_int('t')).at(t),
                                                                        possible_paths.at(color_to_int('k')).at(k)
                                                                    };
                                                                    if (paths_compatible(set_of_paths)) {
                                                                        cout << "Found solution." << endl;
                                                                    }
                                                                    else {
                                                                        cout << "No solution." << endl;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
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

void flow_board::map_nodes() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            switch (nodes.at(row).at(col)) {
                case 'R':
                    if (pipe_starts.at(0).first == -1 && pipe_starts.at(0).second == -1) {
                        pipe_starts.at(0) = {row, col};
                    }
                    else {
                        pipe_ends.at(0) = {row, col};
                    }
                break;
                case 'G':
                    if (pipe_starts.at(1).first == -1 && pipe_starts.at(1).second == -1) {
                        pipe_starts.at(1) = {row, col};
                    }
                    else {
                        pipe_ends.at(1) = {row, col};
                    }
                break;
                case 'B':
                    if (pipe_starts.at(2).first == -1 && pipe_starts.at(2).second == -1) {
                        pipe_starts.at(2) = {row, col};
                    }
                    else {
                        pipe_ends.at(2) = {row, col};
                    }
                break;
                case 'Y':
                    if (pipe_starts.at(3).first == -1 && pipe_starts.at(3).second == -1) {
                        pipe_starts.at(3) = {row, col};
                    }
                    else {
                        pipe_ends.at(3) = {row, col};
                    }
                break;
                case 'O':
                    if (pipe_starts.at(4).first == -1 && pipe_starts.at(4).second == -1) {
                        pipe_starts.at(4) = {row, col};
                    }
                    else {
                        pipe_ends.at(4) = {row, col};
                    }
                break;
                case 'C':
                    if (pipe_starts.at(5).first == -1 && pipe_starts.at(5).second == -1) {
                        pipe_starts.at(5) = {row, col};
                    }
                    else {
                        pipe_ends.at(5) = {row, col};
                    }
                break;
                case 'M':
                    if (pipe_starts.at(6).first == -1 && pipe_starts.at(6).second == -1) {
                        pipe_starts.at(6) = {row, col};
                    }
                    else {
                        pipe_ends.at(6) = {row, col};
                    }
                break;
                case 'W':
                    if (pipe_starts.at(7).first == -1 && pipe_starts.at(7).second == -1) {
                        pipe_starts.at(7) = {row, col};
                    }
                    else {
                        pipe_ends.at(7) = {row, col};
                    }
                break;
                case 'P':
                    if (pipe_starts.at(8).first == -1 && pipe_starts.at(8).second == -1) {
                        pipe_starts.at(8) = {row, col};
                    }
                    else {
                        pipe_ends.at(8) = {row, col};
                    }
                break;
                case 'H':
                    if (pipe_starts.at(9).first == -1 && pipe_starts.at(9).second == -1) {
                        pipe_starts.at(9) = {row, col};
                    }
                    else {
                        pipe_ends.at(9) = {row, col};
                    }
                break;
                case 'A':
                    if (pipe_starts.at(10).first == -1 && pipe_starts.at(10).second == -1) {
                        pipe_starts.at(10) = {row, col};
                    }
                    else {
                        pipe_ends.at(10) = {row, col};
                    }
                break;
                case 'L':
                    if (pipe_starts.at(11).first == -1 && pipe_starts.at(11).second == -1) {
                        pipe_starts.at(11) = {row, col};
                    }
                    else {
                        pipe_ends.at(11) = {row, col};
                    }
                break;
                case 'E':
                    if (pipe_starts.at(12).first == -1 && pipe_starts.at(12).second == -1) {
                        pipe_starts.at(12) = {row, col};
                    }
                    else {
                        pipe_ends.at(12) = {row, col};
                    }
                break;
                case 'N':
                    if (pipe_starts.at(13).first == -1 && pipe_starts.at(13).second == -1) {
                        pipe_starts.at(13) = {row, col};
                    }
                    else {
                        pipe_ends.at(13) = {row, col};
                    }
                break;
                case 'T':
                    if (pipe_starts.at(14).first == -1 && pipe_starts.at(14).second == -1) {
                        pipe_starts.at(14) = {row, col};
                    }
                    else {
                        pipe_ends.at(14) = {row, col};
                    }
                break;
                case 'K':
                    if (pipe_starts.at(15).first == -1 && pipe_starts.at(15).second == -1) {
                        pipe_starts.at(15) = {row, col};
                    }
                    else {
                        pipe_ends.at(15) = {row, col};
                    }
                break;
            }
        }
    }
}

void flow_board::build_paths_at(int row, int col, char color, vector<vector<char>> cur) {    
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }
    if (nodes.at(row).at(col) == toupper(color)) {
        // If (row, col) is the pipe end
        if (row == pipe_ends.at(color_to_int(color)).first && col == pipe_ends.at(color_to_int(color)).second) {
            // Add cur to possible_paths
            possible_paths.at(color_to_int(color)).push_back(cur);
            return;
        }
    }
    else if (cur.at(row).at(col) != ' ') {
        return;
    }

    if (row == pipe_starts.at(color_to_int(color)).first && col == pipe_starts.at(color_to_int(color)).second) {
        int line_size = 0;
        for (int i = 0; i < cur.size(); ++i) {
            for (int j = 0; j < cur.at(i).size(); ++j) {
                if (cur.at(i).at(j) == color) {
                    ++line_size;
                }
            }
        }
        if (line_size > 0) {
            return;
        }
    }
    else {
        cur.at(row).at(col) = color;
    }

    build_paths_at(row + 1, col, color, cur);
    build_paths_at(row, col - 1, color, cur);
    build_paths_at(row, col + 1, color, cur);
    build_paths_at(row - 1, col, color, cur);
}

// TODO: Complete this
bool flow_board::paths_compatible(vector<vector<vector<char>>> set_of_paths) {
    return false;
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

int flow_board::color_to_int(char color) {
    switch (color) {
        case 'r': return 0;
        case 'g': return 1;
        case 'b': return 2;
        case 'y': return 3;
        case 'o': return 4;
        case 'c': return 5;
        case 'm': return 6;
        case 'w': return 7;
        case 'p': return 8;
        case 'h': return 9;
        case 'a': return 10;
        case 'l': return 11;
        case 'e': return 12;
        case 'n': return 13;
        case 't': return 14;
        case 'k': return 15;
    }
    return -1;
}

char flow_board::int_to_color(int color) {
    switch (color) {
        case 0: return 'r';
        case 1: return 'g';
        case 2: return 'b';
        case 3: return 'y';
        case 4: return 'o';
        case 5: return 'c';
        case 6: return 'm';
        case 7: return 'w';
        case 8: return 'p';
        case 9: return 'h';
        case 10: return 'a';
        case 11: return 'l';
        case 12: return 'e';
        case 13: return 'n';
        case 14: return 't';
        case 15: return 'k';
    }
    return 'X';
}
