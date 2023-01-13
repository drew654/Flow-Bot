#include "flow_board.h"

#include <iostream>
#include <fstream>
#include <thread>

using std::cout, std::endl, std::string, std::vector, std::pair, std::ifstream;
using namespace std::chrono_literals;

flow_board::flow_board() {
    rows = -1;
    cols = -1;
    color_count = 0;
    solved = false;
    possible_paths = vector<vector<pair<vector<vector<char>>, int>>>(16);
    nodes = vector<vector<char>>();
    solution = vector<vector<char>>();
    solve_cursor = vector<vector<char>>();
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
    color_count = 0;
    solved = false;

    possible_paths = vector<vector<pair<vector<vector<char>>, int>>>(16);
    vector<vector<char>> vec(rows, vector<char>(cols, ' '));
    nodes = vec;
    solution = vec;
    solve_cursor = vec;

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
    find_possible_paths();

    // Sort the paths by length to weed out necessarily long ones
    sort_possible_paths();

    // Test every possible path with each other
    vector<vector<vector<char>>> smaller_set_of_paths;
    for (unsigned int r = 0; r <= possible_paths.at(color_to_int('r')).size(); ++r) {
        vector<vector<vector<char>>> set_of_paths(16);
        if (r == possible_paths.at(color_to_int('r')).size()) {
            set_of_paths.at(color_to_int('r')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
        }
        else {
            set_of_paths.at(color_to_int('r')) = possible_paths.at(color_to_int('r')).at(r).first;
        }
        for (unsigned int g = 0; g <= possible_paths.at(color_to_int('g')).size(); ++g) {
            if (g == possible_paths.at(color_to_int('g')).size()) {
                set_of_paths.at(color_to_int('g')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
            }
            else {
                set_of_paths.at(color_to_int('g')) = possible_paths.at(color_to_int('g')).at(g).first;
                smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('g') + 1);
                if (!paths_compatible(smaller_set_of_paths, color_to_int('g') + 1)) {
                    continue;
                }
            }
            for (unsigned int b = 0; b <= possible_paths.at(color_to_int('b')).size(); ++b) {
                if (b == possible_paths.at(color_to_int('b')).size()) {
                    set_of_paths.at(color_to_int('b')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                }
                else {
                    set_of_paths.at(color_to_int('b')) = possible_paths.at(color_to_int('b')).at(b).first;
                    smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('b') + 1);
                    if (!paths_compatible(smaller_set_of_paths, color_to_int('b') + 1)) {
                        continue;
                    }
                }
                for (unsigned int y = 0; y <= possible_paths.at(color_to_int('y')).size(); ++y) {
                    if (y == possible_paths.at(color_to_int('y')).size()) {
                        set_of_paths.at(color_to_int('y')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                    }
                    else {
                        set_of_paths.at(color_to_int('y')) = possible_paths.at(color_to_int('y')).at(y).first;
                        smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('y') + 1);
                        if (!paths_compatible(smaller_set_of_paths, color_to_int('y') + 1)) {
                            continue;
                        }
                    }
                    for (unsigned int o = 0; o <= possible_paths.at(color_to_int('o')).size(); ++o) {
                        if (o == possible_paths.at(color_to_int('o')).size()) {
                            set_of_paths.at(color_to_int('o')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                        }
                        else {
                            set_of_paths.at(color_to_int('o')) = possible_paths.at(color_to_int('o')).at(o).first;
                            smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('o') + 1);
                            if (!paths_compatible(smaller_set_of_paths, color_to_int('o') + 1)) {
                                continue;
                            }
                        }
                        for (unsigned int c = 0; c <= possible_paths.at(color_to_int('c')).size(); ++c) {
                            if (c == possible_paths.at(color_to_int('c')).size()) {
                                set_of_paths.at(color_to_int('c')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                            }
                            else {
                                set_of_paths.at(color_to_int('c')) = possible_paths.at(color_to_int('c')).at(c).first;
                                smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('c') + 1);
                                if (!paths_compatible(smaller_set_of_paths, color_to_int('c') + 1)) {
                                    continue;
                                }
                            }
                            for (unsigned int m = 0; m <= possible_paths.at(color_to_int('m')).size(); ++m) {
                                if (m == possible_paths.at(color_to_int('m')).size()) {
                                    set_of_paths.at(color_to_int('m')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                }
                                else {
                                    set_of_paths.at(color_to_int('m')) = possible_paths.at(color_to_int('m')).at(m).first;
                                    smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('m') + 1);
                                    if (!paths_compatible(smaller_set_of_paths, color_to_int('m') + 1)) {
                                        continue;
                                    }
                                }
                                for (unsigned int w = 0; w <= possible_paths.at(color_to_int('w')).size(); ++w) {
                                    if (w == possible_paths.at(color_to_int('w')).size()) {
                                        set_of_paths.at(color_to_int('w')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                    }
                                    else {
                                        set_of_paths.at(color_to_int('w')) = possible_paths.at(color_to_int('w')).at(w).first;
                                        smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('w') + 1);
                                        if (!paths_compatible(smaller_set_of_paths, color_to_int('w') + 1)) {
                                            continue;
                                        }
                                    }
                                    for (unsigned int p = 0; p <= possible_paths.at(color_to_int('p')).size(); ++p) {
                                        if (p == possible_paths.at(color_to_int('p')).size()) {
                                            set_of_paths.at(color_to_int('p')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                        }
                                        else {
                                            set_of_paths.at(color_to_int('p')) = possible_paths.at(color_to_int('p')).at(p).first;
                                            smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('p') + 1);
                                            if (!paths_compatible(smaller_set_of_paths, color_to_int('p') + 1)) {
                                                continue;
                                            }
                                        }
                                        for (unsigned int h = 0; h <= possible_paths.at(color_to_int('h')).size(); ++h) {
                                            if (h == possible_paths.at(color_to_int('h')).size()) {
                                                set_of_paths.at(color_to_int('h')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                            }
                                            else {
                                                set_of_paths.at(color_to_int('h')) = possible_paths.at(color_to_int('h')).at(h).first;
                                                smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('h') + 1);
                                                if (!paths_compatible(smaller_set_of_paths, color_to_int('h') + 1)) {
                                                    continue;
                                                }
                                            }
                                            for (unsigned int a = 0; a <= possible_paths.at(color_to_int('a')).size(); ++a) {
                                                if (a == possible_paths.at(color_to_int('a')).size()) {
                                                    set_of_paths.at(color_to_int('a')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                }
                                                else {
                                                    set_of_paths.at(color_to_int('a')) = possible_paths.at(color_to_int('a')).at(a).first;
                                                    smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('a') + 1);
                                                    if (!paths_compatible(smaller_set_of_paths, color_to_int('a') + 1)) {
                                                        continue;
                                                    }
                                                }
                                                for (unsigned int l = 0; l <= possible_paths.at(color_to_int('l')).size(); ++l) {
                                                    if (l == possible_paths.at(color_to_int('l')).size()) {
                                                        set_of_paths.at(color_to_int('l')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                    }
                                                    else {
                                                        set_of_paths.at(color_to_int('l')) = possible_paths.at(color_to_int('l')).at(l).first;
                                                        smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('l') + 1);
                                                        if (!paths_compatible(smaller_set_of_paths, color_to_int('l') + 1)) {
                                                            continue;
                                                        }
                                                    }
                                                    for (unsigned int e = 0; e <= possible_paths.at(color_to_int('e')).size(); ++e) {
                                                        if (e == possible_paths.at(color_to_int('e')).size()) {
                                                            set_of_paths.at(color_to_int('e')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                        }
                                                        else {
                                                            set_of_paths.at(color_to_int('e')) = possible_paths.at(color_to_int('e')).at(e).first;
                                                            smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('e') + 1);
                                                            if (!paths_compatible(smaller_set_of_paths, color_to_int('e') + 1)) {
                                                                continue;
                                                            }
                                                        }
                                                        for (unsigned int n = 0; n <= possible_paths.at(color_to_int('n')).size(); ++n) {
                                                            if (n == possible_paths.at(color_to_int('n')).size()) {
                                                                set_of_paths.at(color_to_int('n')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                            }
                                                            else {
                                                                set_of_paths.at(color_to_int('n')) = possible_paths.at(color_to_int('n')).at(n).first;
                                                                smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('n') + 1);
                                                                if (!paths_compatible(smaller_set_of_paths, color_to_int('n') + 1)) {
                                                                    continue;
                                                                }
                                                            }
                                                            for (unsigned int t = 0; t <= possible_paths.at(color_to_int('t')).size(); ++t) {
                                                                if (t == possible_paths.at(color_to_int('t')).size()) {
                                                                    set_of_paths.at(color_to_int('t')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                                }
                                                                else {
                                                                    set_of_paths.at(color_to_int('t')) = possible_paths.at(color_to_int('t')).at(t).first;
                                                                    smaller_set_of_paths = shrink_set_of_paths(set_of_paths, color_to_int('t') + 1);
                                                                    if (!paths_compatible(smaller_set_of_paths, color_to_int('t') + 1)) {
                                                                        continue;
                                                                    }
                                                                }
                                                                for (unsigned int k = 0; k <= possible_paths.at(color_to_int('k')).size(); ++k) {
                                                                    if (k == possible_paths.at(color_to_int('k')).size()) {
                                                                        set_of_paths.at(color_to_int('k')) = vector<vector<char>>(rows, vector<char>(cols, ' '));
                                                                    }
                                                                    else {
                                                                        set_of_paths.at(color_to_int('k')) = possible_paths.at(color_to_int('k')).at(k).first;
                                                                    }
                                                                    smaller_set_of_paths.clear();
                                                                    for (unsigned int i = 0; i < set_of_paths.size(); ++i) {
                                                                        bool empty_set = true;
                                                                        for (int row = 0; row < rows; ++row) {
                                                                            for (int col = 0; col < cols; ++col) {
                                                                                if (set_of_paths.at(i).at(row).at(col) != ' ') {
                                                                                    empty_set = false;
                                                                                }
                                                                            }
                                                                        }
                                                                        if (!empty_set) {
                                                                            smaller_set_of_paths.push_back(set_of_paths.at(i));
                                                                        }
                                                                    }
                                                                    if (paths_compatible(smaller_set_of_paths, color_count)) {
                                                                        write_solution(set_of_paths);
                                                                        solved = true;
                                                                        return;
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

void flow_board::solve_with_progress() {
    std::thread t0([this] {this->solve(); });
    std::thread t1([this] {this->print_solving_progress(); });
    t0.join();
    t1.join();
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
                    cout << color_string("⓿", tolower(nodes.at(row).at(col)));
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

void flow_board::print_solution(bool letters) {
    print_graph(solution, letters);
}

void flow_board::print_graph(vector<vector<char>> graph, bool letters) {
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
                cout << color_string(string(1, graph.at(row).at(col)), tolower(graph.at(row).at(col)));
            }
            else {
                if (graph.at(row).at(col) == ' ') {
                    cout << ' ';
                }
                else if (graph.at(row).at(col) == tolower(graph.at(row).at(col))) {
                    cout << color_string("+", tolower(graph.at(row).at(col)));
                }
                else {
                    cout << color_string("⓿", tolower(graph.at(row).at(col)));
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

void flow_board::print_solving_progress() {
    while (!solved) {
        print_graph(solve_cursor);
        std::this_thread::sleep_for(1s);
    }
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
                        ++color_count;
                    }
                break;
                case 'G':
                    if (pipe_starts.at(1).first == -1 && pipe_starts.at(1).second == -1) {
                        pipe_starts.at(1) = {row, col};
                    }
                    else {
                        pipe_ends.at(1) = {row, col};
                        ++color_count;
                    }
                break;
                case 'B':
                    if (pipe_starts.at(2).first == -1 && pipe_starts.at(2).second == -1) {
                        pipe_starts.at(2) = {row, col};
                    }
                    else {
                        pipe_ends.at(2) = {row, col};
                        ++color_count;
                    }
                break;
                case 'Y':
                    if (pipe_starts.at(3).first == -1 && pipe_starts.at(3).second == -1) {
                        pipe_starts.at(3) = {row, col};
                    }
                    else {
                        pipe_ends.at(3) = {row, col};
                        ++color_count;
                    }
                break;
                case 'O':
                    if (pipe_starts.at(4).first == -1 && pipe_starts.at(4).second == -1) {
                        pipe_starts.at(4) = {row, col};
                    }
                    else {
                        pipe_ends.at(4) = {row, col};
                        ++color_count;
                    }
                break;
                case 'C':
                    if (pipe_starts.at(5).first == -1 && pipe_starts.at(5).second == -1) {
                        pipe_starts.at(5) = {row, col};
                    }
                    else {
                        pipe_ends.at(5) = {row, col};
                        ++color_count;
                    }
                break;
                case 'M':
                    if (pipe_starts.at(6).first == -1 && pipe_starts.at(6).second == -1) {
                        pipe_starts.at(6) = {row, col};
                    }
                    else {
                        pipe_ends.at(6) = {row, col};
                        ++color_count;
                    }
                break;
                case 'W':
                    if (pipe_starts.at(7).first == -1 && pipe_starts.at(7).second == -1) {
                        pipe_starts.at(7) = {row, col};
                    }
                    else {
                        pipe_ends.at(7) = {row, col};
                        ++color_count;
                    }
                break;
                case 'P':
                    if (pipe_starts.at(8).first == -1 && pipe_starts.at(8).second == -1) {
                        pipe_starts.at(8) = {row, col};
                    }
                    else {
                        pipe_ends.at(8) = {row, col};
                        ++color_count;
                    }
                break;
                case 'H':
                    if (pipe_starts.at(9).first == -1 && pipe_starts.at(9).second == -1) {
                        pipe_starts.at(9) = {row, col};
                    }
                    else {
                        pipe_ends.at(9) = {row, col};
                        ++color_count;
                    }
                break;
                case 'A':
                    if (pipe_starts.at(10).first == -1 && pipe_starts.at(10).second == -1) {
                        pipe_starts.at(10) = {row, col};
                    }
                    else {
                        pipe_ends.at(10) = {row, col};
                        ++color_count;
                    }
                break;
                case 'L':
                    if (pipe_starts.at(11).first == -1 && pipe_starts.at(11).second == -1) {
                        pipe_starts.at(11) = {row, col};
                    }
                    else {
                        pipe_ends.at(11) = {row, col};
                        ++color_count;
                    }
                break;
                case 'E':
                    if (pipe_starts.at(12).first == -1 && pipe_starts.at(12).second == -1) {
                        pipe_starts.at(12) = {row, col};
                    }
                    else {
                        pipe_ends.at(12) = {row, col};
                        ++color_count;
                    }
                break;
                case 'N':
                    if (pipe_starts.at(13).first == -1 && pipe_starts.at(13).second == -1) {
                        pipe_starts.at(13) = {row, col};
                    }
                    else {
                        pipe_ends.at(13) = {row, col};
                        ++color_count;
                    }
                break;
                case 'T':
                    if (pipe_starts.at(14).first == -1 && pipe_starts.at(14).second == -1) {
                        pipe_starts.at(14) = {row, col};
                    }
                    else {
                        pipe_ends.at(14) = {row, col};
                        ++color_count;
                    }
                break;
                case 'K':
                    if (pipe_starts.at(15).first == -1 && pipe_starts.at(15).second == -1) {
                        pipe_starts.at(15) = {row, col};
                    }
                    else {
                        pipe_ends.at(15) = {row, col};
                        ++color_count;
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
            int count = 0;
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (cur.at(r).at(c) == color) {
                        ++count;
                    }
                }
            }
            possible_paths.at(color_to_int(color)).push_back({cur, count});
            return;
        }
    }
    else if (cur.at(row).at(col) != ' ') {
        return;
    }

    // If (row, col) is the pipe start
    if (row == pipe_starts.at(color_to_int(color)).first && col == pipe_starts.at(color_to_int(color)).second) {
        int line_size = 0;
        for (unsigned int i = 0; i < cur.size(); ++i) {
            for (unsigned int j = 0; j < cur.at(i).size(); ++j) {
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

    solve_cursor = cur;

    build_paths_at(row + 1, col, color, cur);
    build_paths_at(row, col - 1, color, cur);
    build_paths_at(row, col + 1, color, cur);
    build_paths_at(row - 1, col, color, cur);
}

void flow_board::find_possible_paths() {
    vector<vector<char>> cur0 = vector<vector<char>>(nodes);
    vector<vector<char>> cur1 = vector<vector<char>>(nodes);
    vector<vector<char>> cur2 = vector<vector<char>>(nodes);
    vector<vector<char>> cur3 = vector<vector<char>>(nodes);
    vector<vector<char>> cur4 = vector<vector<char>>(nodes);
    vector<vector<char>> cur5 = vector<vector<char>>(nodes);
    vector<vector<char>> cur6 = vector<vector<char>>(nodes);
    vector<vector<char>> cur7 = vector<vector<char>>(nodes);
    vector<vector<char>> cur8 = vector<vector<char>>(nodes);
    vector<vector<char>> cur9 = vector<vector<char>>(nodes);
    vector<vector<char>> cur10 = vector<vector<char>>(nodes);
    vector<vector<char>> cur11 = vector<vector<char>>(nodes);
    vector<vector<char>> cur12 = vector<vector<char>>(nodes);
    vector<vector<char>> cur13 = vector<vector<char>>(nodes);
    vector<vector<char>> cur14 = vector<vector<char>>(nodes);
    vector<vector<char>> cur15 = vector<vector<char>>(nodes);

    std::thread t0 ([this, cur0] {this->build_paths_at(pipe_starts.at(color_to_int('r')).first, pipe_starts.at(color_to_int('r')).second, 'r', cur0); });
    std::thread t1 ([this, cur1] {this->build_paths_at(pipe_starts.at(color_to_int('g')).first, pipe_starts.at(color_to_int('g')).second, 'g', cur1); });
    std::thread t2 ([this, cur2] {this->build_paths_at(pipe_starts.at(color_to_int('b')).first, pipe_starts.at(color_to_int('b')).second, 'b', cur2); });
    std::thread t3 ([this, cur3] {this->build_paths_at(pipe_starts.at(color_to_int('y')).first, pipe_starts.at(color_to_int('y')).second, 'y', cur3); });
    std::thread t4 ([this, cur4] {this->build_paths_at(pipe_starts.at(color_to_int('o')).first, pipe_starts.at(color_to_int('o')).second, 'o', cur4); });
    std::thread t5 ([this, cur5] {this->build_paths_at(pipe_starts.at(color_to_int('c')).first, pipe_starts.at(color_to_int('c')).second, 'c', cur5); });
    std::thread t6 ([this, cur6] {this->build_paths_at(pipe_starts.at(color_to_int('m')).first, pipe_starts.at(color_to_int('m')).second, 'm', cur6); });
    std::thread t7 ([this, cur7] {this->build_paths_at(pipe_starts.at(color_to_int('w')).first, pipe_starts.at(color_to_int('w')).second, 'w', cur7); });
    std::thread t8 ([this, cur8] {this->build_paths_at(pipe_starts.at(color_to_int('p')).first, pipe_starts.at(color_to_int('p')).second, 'p', cur8); });
    std::thread t9 ([this, cur9] {this->build_paths_at(pipe_starts.at(color_to_int('h')).first, pipe_starts.at(color_to_int('h')).second, 'h', cur9); });
    std::thread t10 ([this, cur10] {this->build_paths_at(pipe_starts.at(color_to_int('a')).first, pipe_starts.at(color_to_int('a')).second, 'a', cur10); });
    std::thread t11 ([this, cur11] {this->build_paths_at(pipe_starts.at(color_to_int('l')).first, pipe_starts.at(color_to_int('l')).second, 'l', cur11); });
    std::thread t12 ([this, cur12] {this->build_paths_at(pipe_starts.at(color_to_int('e')).first, pipe_starts.at(color_to_int('e')).second, 'e', cur12); });
    std::thread t13 ([this, cur13] {this->build_paths_at(pipe_starts.at(color_to_int('n')).first, pipe_starts.at(color_to_int('n')).second, 'n', cur13); });
    std::thread t14 ([this, cur14] {this->build_paths_at(pipe_starts.at(color_to_int('t')).first, pipe_starts.at(color_to_int('t')).second, 't', cur14); });
    std::thread t15 ([this, cur15] {this->build_paths_at(pipe_starts.at(color_to_int('k')).first, pipe_starts.at(color_to_int('k')).second, 'k', cur15); });

    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
}

void flow_board::sort_possible_paths() {
    for (unsigned int color = 0; color < possible_paths.size(); ++color) {
        if (possible_paths.at(color).size() > 1) {
            for (unsigned int i = 0; i < possible_paths.at(color).size() - 1; ++i) {
            unsigned int min_i = i;
            for (unsigned int j = i + 1; j < possible_paths.at(color).size(); ++j) {
                if (possible_paths.at(color).at(j).second < possible_paths.at(color).at(min_i).second) {
                    min_i = j;
                }
                if (min_i != i) {
                    std::swap(possible_paths.at(color).at(min_i), possible_paths.at(color).at(i));
                }
            }
        }
        }
    }
}

vector<vector<vector<char>>> flow_board::shrink_set_of_paths(vector<vector<vector<char>>> set_of_paths, int n) {
    vector<vector<vector<char>>> smaller_set_of_paths;
    for (int i = 0; i < n; ++i) {
        bool empty_set = true;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (set_of_paths.at(i).at(row).at(col) != ' ') {
                    empty_set = false;
                }
            }
        }
        if (!empty_set) {
            smaller_set_of_paths.push_back(set_of_paths.at(i));
        }
    }
    return smaller_set_of_paths;
}

bool flow_board::paths_compatible(vector<vector<vector<char>>> set_of_paths, unsigned int n) {
    if (set_of_paths.size() != n) {
        return false;
    }
    vector<vector<char>> rogue1(rows, vector<char>(cols, ' '));
    for (unsigned int i = 0; i < set_of_paths.size(); ++i) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (rogue1.at(row).at(col) == ' ') {
                    rogue1.at(row).at(col) = set_of_paths.at(i).at(row).at(col);
                }
                // If spot on rogue1 is not available
                else if (set_of_paths.at(i).at(row).at(col) != ' ') {
                    // And it's not a node place on itself
                    if (set_of_paths.at(i).at(row).at(col) != rogue1.at(row).at(col)) {
                        return false;
                    }
                }
                solve_cursor = rogue1;
            }
        }
    }
    return true;
}

void flow_board::write_solution(vector<vector<vector<char>>> set_of_paths) {
    for (unsigned int i = 0; i < set_of_paths.size(); ++i) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (set_of_paths.at(i).at(row).at(col) != ' ') {
                    solution.at(row).at(col) = set_of_paths.at(i).at(row).at(col);
                }
            }
        }
    }
}

string flow_board::color_string(string input, char color) {
    string result = "";
    string altered;
    switch (color) {
        // Red
        case 'r':
            result += "\x1b[38;2;255;0;0m";
            altered = "❶";
            break;
        // Green
        case 'g':
            result += "\x1b[38;2;0;175;0m";
            altered = "❷";
            break;
        // Blue
        case 'b':
            result += "\x1b[38;2;0;0;255m";
            altered = "❸";
            break;
        // Yellow
        case 'y':
            result += "\x1b[38;2;255;255;0m";
            altered = "❹";
            break;
        // Orange
        case 'o':
            result += "\x1b[38;2;255;175;0m";
            altered = "❺";
            break;
        // Cyan
        case 'c':
            result += "\x1b[38;2;0;215;255m";
            altered = "❻";
            break;
        // Magenta
        case 'm':
            result += "\x1b[38;2;215;0;175m";
            altered = "❼";
            break;
        // Brown
        case 'w':
            result += "\x1b[38;2;95;95;0m";
            altered = "❽";
            break;
        // Purple
        case 'p':
            result += "\x1b[38;2;175;0;255m";
            altered = "❾";
            break;
        // White
        case 'h':
            result += "\x1b[38;2;255;255;255m";
            altered = "❿";
            break;
        // Gray
        case 'a':
            result += "\x1b[38;2;128;128;128m";
            altered = "⓫";
            break;
        // Lime
        case 'l':
            result += "\x1b[38;2;0;255;0m";
            altered = "⓬";
            break;
        // Beige
        case 'e':
            result += "\x1b[38;2;215;215;175m";
            altered = "⓭";
            break;
        // Navy
        case 'n':
            result += "\x1b[38;2;0;0;175m";
            altered = "⓮";
            break;
        // Teal
        case 't':
            result += "\x1b[38;2;0;135;135m";
            altered = "⓯";
            break;
        // Pink
        case 'k':
            result += "\x1b[38;2;255;175;215m";
            altered = "⓰";
            break;
    }
    
    if (input == "⓿") {
        result += altered;
    }
    else {
        result += input;
    }
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
