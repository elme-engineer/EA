#include <iostream>
#include <set>

bool checkGroups(std::set<int> &guests){

    if( *guests.begin() > 0) //no men case
        return false;

    if( *guests.rbegin() < 0) // no women case
        return false;



    //2 man 1 woman
    for(auto itr = guests.begin(); itr != guests.lower_bound(0) ; ++itr){

        for (auto secondItr  = std::next(itr, 1); secondItr != guests.upper_bound(0) ; ++secondItr) {

            auto value = guests.find( -(*itr + *secondItr));

            if(value != guests.end()) // pair found
                return true;
        }

    }

    //2 woman 1 man
    for(auto itr = guests.upper_bound(0); itr != std::prev(guests.end()) ;++itr){ //starts at the 1st positive number
        for (auto secondItr  = std::next(itr, 1); secondItr != guests.end(); ++secondItr) {

            auto value = guests.find( -(*itr + *secondItr));

            if(value != guests.end()) // pair found
                return true;

        }
    }

    //no women nor men cases

    return false;

}


int main() {

    int input;
    std::set<int> guests;

    while(std::cin >> input){

        if(input == 0) {

            if(checkGroups(guests))
                std::cout << "Fair" << std::endl;
            else
                std::cout << "Rigged" << std::endl;

            guests.clear();
            continue;
        }

        guests.insert(input);

    }


    return 0;
}
