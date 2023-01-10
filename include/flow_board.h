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
        std::vector<std::pair<int, int>> pipe_starts;
        std::vector<std::pair<int, int>> pipe_ends;
        std::vector<std::vector<std::vector<std::vector<char>>>> possible_paths;     // red, green, blue, yellow, orange, cyan, magenta, brown, purple, white, gray, lime, beige, navy, teal, pink
        void map_nodes();
        void build_paths_at(int row, int col, char color, std::vector<std::vector<char>> cur);
        std::string color_string(std::string input, char color);
        int color_to_int(char color);
        char int_to_color(int color);
};

#endif