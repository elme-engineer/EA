#include <iostream>
#include <vector>
#include <algorithm>

int maxMoves, minMoves, minRight;
int rows, cols, left = 0, right = 0, doubleRight = 0, initialLine, finalLine;

bool vaultDone(const std::vector<std::vector<int>>& grid){

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j){
            if (grid[i][j] != i+1){
                return false;
            }
        }
        if(i > 2 && rows - 1 - i == 2)
            initialLine = i + 1;


    }

    return true;
}

bool impossibleVault(const std::vector<std::vector<int>> &grid)
{
    int array[5] = {0};
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            if (grid[i][j] != i + 1)
            {
                array[grid[i][j] - 1] += abs(i+1 - grid[i][j]);
                if (array[grid[i][j] - 1] > maxMoves)
                    return true;
            }
        }
    }
    return false;
}

bool moreOcurrences(const std::vector<int> &numOcurrences){

    for (int m = 0; m < 5; m++){
            
            
            if(numOcurrences[m] > cols)
                return true;
    }

    return false;
}

void printVault(const std::vector<std::vector<int>>& grid){

    std::cout << "----------VERIFY-------------\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
           std::cout << grid[i][j] << " ";
        }

        std::cout << "\n";
    }
    std::cout << "-----------END-----VERIFY-------------\n";
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

void confirmFinalLine(const std::vector<std::vector<int>>& grid){

    //down to up
    for (int i = finalLine; i >= initialLine + 2; i--)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] != i + 1)
            {
                return;
            }
            
        }
        
        finalLine = i;
    }

}

int aztecVault(int moves, std::vector<std::vector<int>>& grid, int line, int col){

    if (moves >= minMoves)
        return 9999;
 
    if(vaultDone(grid)){

       if(moves < minMoves){

            minMoves = moves;     
        }
        
        return minMoves;         
    }

    confirmFinalLine(grid);

    for (int i = initialLine; i < finalLine; ++i) {

        //std::cout << "I: " << finalLine << "\n";
        for (int j = 0; j < cols - 1; ++j) {


            if(i == line && j == col){
                continue;
            }

                if(minMoves == moves + 1)
                    break;
                rotateRight(i, j, grid);
                right = aztecVault(moves + 1, grid, i, j);
                rotateLeft(i, j, grid);

                rotateLeft(i, j, grid);
                left = aztecVault(moves + 1, grid, i, j);
                rotateRight(i, j, grid);

                rotateRight(i, j, grid);
                rotateRight(i, j, grid);
                doubleRight = aztecVault(moves + 2, grid, i, j);
                rotateLeft(i, j, grid);
                rotateLeft(i, j, grid);
                
                minRight = std::min(right, doubleRight);
                minMoves = std::min(minMoves, std::min(left, minRight));
        }
    }

    return minMoves;
}

int main() {

    int tCases;
    int moves;

    std::cin >> tCases;

    for (int i = 0; i < tCases; ++i) {

        std::cin >> rows >> cols >> maxMoves;

        std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));


        std::vector<int> numOcurrences(5,0);

        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < cols; ++k) {

                std::cin >> grid[j][k];

                numOcurrences[grid[j][k] - 1] += 1;
                  
            }
        }
        

        if (moreOcurrences(numOcurrences)){
            std::cout << "the treasure is lost!" << "\n";
            continue;
        }
        
        
        if(impossibleVault(grid)){
            std::cout << "the treasure is lost!" << "\n";
            continue;
        }

        minMoves = maxMoves + 1;
        left = 0;
        right = 0;
        doubleRight = 0;
        initialLine = 0;
        finalLine = rows - 1;


        moves = aztecVault(0, grid, -10, -10);
        if(moves > maxMoves)
            std::cout << "the treasure is lost!" << "\n";
        else
            std::cout << moves << "\n";

        
    }

    
    return 0;
}