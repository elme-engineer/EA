#include <iostream>

int board[400][400] = {0};

int movKnight ( int x, int y, int m){

    if (m < 0)
        return 0;

    int visited = 0;

    if(board[x + 200][y + 200] == 0){

        board[x + 200][y + 200] = 1;
        visited = 1;
    }



    return visited + movKnight( x - 2, y - 1, m - 1)
        + movKnight(x - 1, y - 2, m - 1)
        + movKnight( x + 1, y - 2, m - 1)
        + movKnight( x + 2, y - 1, m - 1)
        + movKnight( x - 2, y + 1, m - 1)
        + movKnight( x - 1, y + 2, m - 1)
        + movKnight( x + 2, y + 1, m - 1)
        + movKnight( x + 1, y + 2, m - 1);

}


int main() {

    int n, x, y, m, nVisitedCells = 0;

    std::cin >> n; // get number of knights

    for (int i = 0; i < n; ++i) {

        std::cin >> x >> y >> m;

       nVisitedCells += movKnight( x, y, m);
    }


    std::cout << nVisitedCells << std::endl;

    return 0;
}
