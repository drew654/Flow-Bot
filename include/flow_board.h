#ifndef _FLOW_BOARD
#define _FLOW_BOARD

#include <string>
#include <vector>

class flow_board {
    public:
        flow_board();
        flow_board(std::string file_name);
        void solve();
        void solve_with_progress();
        void print_graph(bool letters = false);
        void print_solution(bool letters = false);
    private:
        int rows;
        int cols;
        unsigned int color_count;
        bool solved;
        std::vector<std::vector<char>> nodes;
        std::vector<std::vector<char>> solution;
        std::vector<std::vector<char>> solve_cursor;
        std::vector<std::pair<int, int>> pipe_starts;
        std::vector<std::pair<int, int>> pipe_ends;
        std::vector<std::vector<std::pair<std::vector<std::vector<char>>, int>>> possible_paths;     // red, green, blue, yellow, orange, cyan, magenta, brown, purple, white, gray, lime, beige, navy, teal, pink
        void map_nodes();
        void build_paths_at(int row, int col, char color, std::vector<std::vector<char>> cur);
        void sort_possible_paths();
        std::vector<std::vector<std::vector<char>>> shrink_set_of_paths(std::vector<std::vector<std::vector<char>>>, int n);
        bool paths_compatible(std::vector<std::vector<std::vector<char>>> set_of_paths, unsigned int n);
        void write_solution(std::vector<std::vector<std::vector<char>>> set_of_paths);
        void print_graph(std::vector<std::vector<char>> graph, bool letters = false);
        void print_solving_progress();
        std::string color_string(std::string input, char color);
        int color_to_int(char color);
        char int_to_color(int color);
};

#endif