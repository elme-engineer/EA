#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

int nr, nc, r, c;
int totalSkulls;

std::vector<int> cardRows;
std::vector<int> cardCols;
std::unordered_map<std::string, unsigned long> *hashMap =  new std::unordered_map<std::string, unsigned long>[25];

bool isSolved(int row, int col){
    
    if((cardCols[col - 1] > c && col >= 1)  || (cardCols[nc - 1] > c))
        return true;

    if( (cardRows[row] > r && row < nr) || (row >= 1 && cardRows[row - 1] > r))
        return true;

    
    return false;
}



unsigned long cardAssign(int row, int col, int totalSkulls) {


    if(isSolved(row, col))
        return 0;
    

    if (totalSkulls == 0)
        return 1;
    

    if (row == nr) 
        return 0;


    std::string hash = "AAAAAAAAAA";
    if (col == 0) {

        for(int i = 0; i < nc; i++)
            hash[cardCols[i]]++;

        hash[8]+= r;
        hash[9]+= c;
        
        if(hashMap[nr-row].find(hash) != hashMap[nr-row].end())
            return hashMap[nr-row][hash];
    }

    // add card
    cardRows[row]++;
    cardCols[col]++;


    //Next available position
    int nextR = row;
    int nextC = col + 1;

    if (nextC == nc) {
        nextC = 0;
        nextR++;
    }

    
    unsigned long result = cardAssign(nextR, nextC, totalSkulls - 1);
    
    cardRows[row]--;
    cardCols[col]--;
    
    unsigned long result2 = cardAssign(nextR, nextC, totalSkulls);
    
    if (col == 0) {

        if(hashMap[nr - row].find(hash) == hashMap[nr - row].end())
            hashMap[nr - row][hash] = result + result2;
    }


    return result + result2;
}


int main() {
    int tCases;
    unsigned long assignments = 0;

    std::cin >> tCases;

    for (int i = 0; i < tCases; ++i) {

        std::cin >> nc >> nr;

        std::cin >> c >> r;

        totalSkulls = nr * r;
        cardRows = std::vector<int>(nr, 0);
        cardCols = std::vector<int>(nc, 0);
        
        
        assignments = cardAssign(0, 0, totalSkulls);
        
        std::cout << assignments << "\n";

        cardRows.clear();
        cardCols.clear();
    }

    
    return 0;
}