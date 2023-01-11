#include "flow_board.h"

int main() {
    flow_board board1 = flow_board("input_files/Classic_Pack/Classic_Pack_5x5_1.txt");
    board1.print_graph();
    board1.solve();
    flow_board board2 = flow_board("input_files/Classic_Pack/Classic_Pack_5x5_2.txt");
    board2.print_graph();
    board2.solve();
}