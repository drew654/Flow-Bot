#include <iostream>
#include <filesystem>
#include "flow_board.h"

namespace fs = std::filesystem;
using std::cin, std::cout, std::endl, std::string;

int main() {
    cout << "Imported Flow boards:" << endl;
    string path = "input_files";
    int count = 0;
    for (const auto& folder : fs::directory_iterator(path)) {
        for (const auto& file : fs::directory_iterator(folder)) {
            cout << ++count << ". " << file.path() << endl;
            flow_board board = flow_board(file.path());
            board.print_graph();
        }
    }
    
    cout << "Which would you like to solve?" << endl;
    int input = 0;
    while (input < 1 || input > count) {
        cin >> input;
        if (input < 1 || input > count) {
            cout << "Which would you like to solve?" << endl;
        }
    }

    count = 0;
    for (const auto& folder : fs::directory_iterator(path)) {
        for (const auto& file : fs::directory_iterator(folder)) {
            if (++count == input) {
                flow_board board = flow_board(file.path());
                board.print_graph();
                board.solve();
                board.print_solution();
            }
        }
    }
}
