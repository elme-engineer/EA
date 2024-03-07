#include <iostream>
#include <vector>
#include <algorithm>

int path(std::vector<std::vector<int>>& matrix,int n){

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < i + 1; ++j) {
            matrix[i][j] = matrix[i][j] + std::max( matrix[i - 1][j], matrix[i-1][j-1]);
        }
    }

    std::vector<int> lastRow = matrix.back();
    auto maxElementInLastRow = std::max_element(lastRow.begin(), lastRow.end());

    return *maxElementInLastRow;
}


int main() {

    int tCases, rows, i, maxValue;
    std::vector<std::vector<int>> matrix;

    std::cin >> tCases;
    for (i = 0; i < tCases; ++i) {

        std::cin >> rows;
        rows++;
        matrix.assign(rows, std::vector<int>(rows, 0));

        for (int j = 1; j < rows; ++j) {
            for (int k = 1; k < j + 1; ++k) {
                std::cin >> matrix[j][k];
            }
        }

        maxValue = path(matrix, rows);

        std::cout << maxValue << std::endl;
    }



    return 0;
}
