#ifndef _FLOW_BOARD
#define _FLOW_BOARD

#include <string>
#include <vector>

class flow_board {
    public:
        flow_board();
        flow_board(std::string file_name);
        void solve();
        void print_graph(bool letters = false);
    private:
        int rows;
        int cols;
        std::vector<std::vector<char>> nodes;
        std::vector<std::vector<std::vector<char>>> possible_lines;     // red, green, blue, yellow, orange, cyan, magenta, brown, purple, white, gray, lime, beige, navy, teal, pink
        void map_nodes(std::vector<std::pair<int, int>>& pipe_starts, std::vector<std::pair<int, int>>& pipe_ends, std::vector<bool>& nodes_present);
        std::string color_string(std::string input, char color);
};

#endif