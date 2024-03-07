#include <iostream>
#include <vector>
#include <algorithm>

int maxMoves, minMoves;
int rows, cols, left, right;

bool vaultDone(std::vector<std::vector<int>>& grid){

    for (int i = 0; i < rows; ++i) {

        std::vector<int>& rowI = grid[i];
        if(std::adjacent_find( rowI.begin(), rowI.end(), std::not_equal_to<>() ) != rowI.end())
            return false;

    }

    return true;
}

void rotateRight(int l, int c, std::vector<std::vector<int>>& grid){

    std::swap(grid[l][c], grid[l][c+1]);
    std::swap(grid[l][c], grid[l+1][c+1]);
    std::swap(grid[l][c], grid[l+1][c]);

}

void rotateLeft(int l, int c, std::vector<std::vector<int>>& grid){

    std::swap(grid[l][c], grid[l+1][c]);
    std::swap(grid[l][c], grid[l+1][c+1]);
    std::swap(grid[l][c], grid[l][c+1]);

}

int aztecVault(int moves, std::vector<std::vector<int>>& grid){

    if (moves > maxMoves) // limit moves exceded
        return -1;

    if(vaultDone(grid))
        return minMoves;

    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < cols - 1; ++j) {

            rotateLeft(i,j, grid);

            left = aztecVault(moves + 1, grid);
            rotateRight(i,j,grid);

            right = aztecVault(moves + 1, grid);
            minMoves = std::min(minMoves, std::min(left,right));

        }
    }

    return minMoves;
}

int main() {

    int tCases;
    std::vector<std::vector<int>> grid;

    std::cin >> tCases;

    for (int i = 0; i < tCases; ++i) {

        std::cin >> rows >> cols >> maxMoves;

        grid.assign(rows, std::vector<int>(cols, 0));

        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < cols; ++k) {
                std::cin >> grid[j][k];
            }
        }

    }

    std::cout << aztecVault(0, grid);

    return 0;
}
