#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "header.h"

using namespace std;

void read_file(string file_name, vector<Order> &Ord, string Sizes[], string Providers[]){
    ifstream file;
    file.open(file_name);

    string line;
    int line_nr = 0;

    if(file.is_open()){
        while(true){
            if(getline(file, line)){
                Order order;
                order.line = line;
                Ord.push_back(order);
                parse(Ord, line, line_nr, Sizes, Providers);
                line_nr++;
            }
            else{
                break;
            }
        }
        file.close();
    }
    else{
        cout << "ERROR - cannot open input.txt" << endl;
    }

}

void parse(vector<Order> &Ord, string line, int line_nr, string Sizes[], string Providers[]){
    char delim = '-';
    string temp;
    int year, month, day;
    string size;
    string provider;

    int parse_progress = 0;

    // parsing year:
    temp = line.substr(parse_progress, line.find(delim));

    stringstream stream(temp);
    if(!(stream >> year)){
        return;
    }

    if(year < 10000 && year > 999){ // must be 4 digit number
        parse_progress += 5;
    }
    else{
        return;
    }

    // parsing month:
    temp = line.substr(parse_progress, line.find(delim));
    stringstream stream2(temp);
    if(!(stream2 >> month)){
        return;
    }
    if(month < 13 && month > 0){
        parse_progress += 3;
    }
    else{
        return;
    }

    // parsing day:
    temp = line.substr(parse_progress, line.find(delim));
    stringstream stream3(temp);
    if(!(stream3 >> day)){
        return;
    }
    if(day < 32 && day > 0){
        parse_progress += 3;
    }
    else{
        return;
    }

    // parsing package size:

    delim = '\n';

    temp = line.substr(parse_progress, line.find(delim));

    parse_progress = 0;
    size = temp[parse_progress];

    bool correct = false;
    for(int i = 0; i < size_of_Sizes; i++){
        if(size == Sizes[i]){
            correct = true;
            break;
        }
    }
    if(!correct){
        return;
    }

    parse_progress++;

    // check space between size and provider:

    if(temp[parse_progress] != ' '){
        return;
    }
    parse_progress++;

    // parsing provider:

    provider.append(temp.begin() + parse_progress, temp.end());

    correct = false;
    for(int i = 0; i < size_of_Providers; i++){
        if(provider == Providers[i]){
            correct = true;
            break;
        }
    }
    if(!correct){
        return;
    }

    // if line is correct:
    Ord.at(line_nr).month = month;
    Ord.at(line_nr).size = size;
    Ord.at(line_nr).provider = provider;
}

void set_prices(vector<Order> &Ord, string Sizes[], string Providers[], float Prices[size_of_Providers][size_of_Sizes]){
    float limit = 10;   // Accumulated discounts must not exceed 10 in a single month
    float accum_dic = 0;
    int counter_L = 0;  // every third shipping is free

     // find lowest size "S" price:
    int s = 0;  // number of "S" price in array
    float lowest_S_price = Prices[0][s];
    for(int p = 1; p < size_of_Providers; p++){  
        if(lowest_S_price > Prices[p][s]){
            lowest_S_price = Prices[p][s];
        }
    }

    for(long unsigned int i = 0; i < Ord.size(); i++){
        // reset accumulated discount counter if going to next month:
        if(i > 0){      
            if(Ord.at(i).month != Ord.at(i-1).month){
                accum_dic = 0;
                counter_L = 1;
            }
        }

        if(!(Ord.at(i).size == "")){    // if line is the right format

            for(int s = 0; s < size_of_Sizes; s++){
                for(int p = 0; p < size_of_Providers; p++){
                    if((Ord.at(i).size == Sizes[s]) && (Ord.at(i).provider == Providers[p])){

                        if(Sizes[s] == "S"){        // must cost as much as the cheapest S option costs
                            if(accum_dic < limit){
                                if(Prices[p][s] == lowest_S_price){ // if the price is already the lowest:
                                    Ord.at(i).disc = 0;
                                    Ord.at(i).price = Prices[p][s];

                                }
                                else{
                                    float temp = min((limit - accum_dic), (Prices[p][s] - lowest_S_price));
                                    Ord.at(i).disc = temp;
                                    accum_dic += temp;
                                    Ord.at(i).price = Prices[p][s] - temp;
                                }
                            }
                            else{
                                Ord.at(i).disc = 0;
                                Ord.at(i).price = Prices[p][s];
                            }
                        }

                        else if(Sizes[s] == "M"){       // no discount
                            Ord.at(i).disc = 0;
                            Ord.at(i).price = Prices[p][s];
                        }

                        else if(Sizes[s] == "L"){        // every third shipping is free, but only once a month
                            if(accum_dic < limit){
                                if(counter_L % 3 == 0 && counter_L > 0){
                                    float temp = min((limit - accum_dic), Prices[p][s]);
                                    Ord.at(i).disc = temp;
                                    Ord.at(i).price = Prices[p][s] - temp;
                                    counter_L++;
                                }
                                else{
                                    Ord.at(i).disc = 0;
                                    Ord.at(i).price = Prices[p][s];
                                    counter_L++;
                                }
                            }
                            else{
                                Ord.at(i).disc = 0;
                                Ord.at(i).price = Prices[p][s];
                            }
                        }
                    }
                }
            }


        }
        else{
            cout << Ord.at(i).line << " Ignored" << endl;
        }
    }
}

void print_results(vector<Order> Ord){
    for(long unsigned int i = 0; i < Ord.size(); i++){
        if(Ord.at(i).month == 0){
            cout << Ord.at(i).line << " Ignored" << endl;
        }
        else{
            cout << Ord.at(i).line << " " << fixed << setprecision(2) << Ord.at(i).price << " ";
            if(Ord.at(i).disc == 0){
                cout << '-' << endl;
            }
            else{
                cout << Ord.at(i).disc << endl;
            }
        }
    }
}
