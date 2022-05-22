#ifndef FUNC_H
#define FUNC_H

#include <vector>

using namespace std;

struct Order{
    string line; // used to first read the line from input txt, which then will be parsed.
    int month;
    string size;  // string is used instead of char for future developement (eg. size XL)
    string provider;
    float price, disc; // price, discount
};

const int size_of_Sizes = 3;
const int size_of_Providers = 2;

void read_file(string file_name, vector<Order> &Ord, string Sizes[], string Providers[]);

void parse(vector<Order> &Ord, string line, int line_nr, string Sizes[], string Providers[]);

void set_prices(vector<Order> &Ord, string Sizes[], string Providers[], float Prices[size_of_Providers][size_of_Sizes]);

void print_results(vector<Order> Ord);

#endif