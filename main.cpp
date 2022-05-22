#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "header.h"

int main(){
    vector<Order> Ord;

    string Sizes[] = {"S", "M", "L"};
    string Providers[] = {"LP", "MR"};
    float Prices[size_of_Providers][size_of_Sizes] = {{1.5, 4.9, 6.9}, {2, 3, 4}}; // prices correspond to providers in order written in Providers[].
    string file_name = "input.txt";

    read_file(file_name, Ord, Sizes, Providers);
    set_prices(Ord, Sizes, Providers, Prices);
    print_results(Ord);

    return 0;
}

