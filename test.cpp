#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cassert>

#include "header.h"

void test_parse(vector<Order> Ord, string Sizes[], string Providers[]){
    assert(Ord.at(0).month == 1);
    assert(Ord.at(0).size == Sizes[0]);
    assert(Ord.at(0).provider == Providers[1]);

    assert(Ord.at(1).month == 1);
    assert(Ord.at(1).size == Sizes[0]);
    assert(Ord.at(1).provider == Providers[1]);

    assert(Ord.at(20).month == 1);
    assert(Ord.at(20).size == Sizes[0]);
    assert(Ord.at(20).provider == Providers[1]);

    assert(Ord.at(24).month == 2);
    assert(Ord.at(24).size == Sizes[2]);
    assert(Ord.at(24).provider == Providers[1]);

    assert(Ord.at(25).month == 2);
    assert(Ord.at(25).size == Sizes[2]);
    assert(Ord.at(25).provider == Providers[0]);
}

void test_prices(vector<Order> Ord, float Prices[size_of_Providers][size_of_Sizes]){
    float lowest_S = 1.5;
    float disc_S_for_MR = 0.5;
    float default_MR_S = Prices[1][0];
    float default_LP_L = Prices[0][2];

    assert(Ord.at(0).price == lowest_S);
    assert(Ord.at(0).disc == disc_S_for_MR);

    assert(Ord.at(10).price == lowest_S);
    assert(Ord.at(10).disc == disc_S_for_MR);

    assert(Ord.at(21).price == default_MR_S);
    assert(Ord.at(21).disc == 0);

    assert(Ord.at(22).price == lowest_S);
    assert(Ord.at(22).disc == disc_S_for_MR);

    assert(Ord.at(23).price == default_LP_L);
    assert(Ord.at(23).disc == 0);
}

int main(){
    vector<Order> Ord;

    string Sizes[] = {"S", "M", "L"};
    string Providers[] = {"LP", "MR"};
    float Prices[size_of_Providers][size_of_Sizes] = {{1.5, 4.9, 6.9}, {2, 3, 4}}; // prices correspond to providers in order written in Providers[].
    string file_name = "test.txt";

    read_file(file_name, Ord, Sizes, Providers);

    test_parse(Ord, Sizes, Providers);
    cout << "parsed successfully" << endl;

    set_prices(Ord, Sizes, Providers, Prices);
    test_prices(Ord, Prices);
    cout << "prices set successfully" << endl;


    cout << "   All tests passed successfully" << endl;

    return 0;
}