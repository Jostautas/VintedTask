#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

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

void read_file(vector<Order> &Ord, string Sizes[], string Providers[], int size_of_Sizes, int size_of_Providers);

void parse(vector<Order> &Ord, string line, int line_nr, string Sizes[], string Providers[], int size_of_Sizes, int size_of_Providers);

void set_prices(vector<Order> &Ord, string Sizes[], string Providers[], float Prices[size_of_Providers][size_of_Sizes], int size_of_Sizes, int size_of_Providers);

void print_results(vector<Order> Ord);

int main(){
    vector<Order> Ord;

    string Sizes[] = {"S", "M", "L"};
    string Providers[] = {"LP", "MR"};
    float Prices[size_of_Providers][size_of_Sizes] = {{1.5, 4.9, 6.9}, {2, 3, 4}}; // prices correspond to providers in order written in Providers[].

    read_file(Ord, Sizes, Providers, size_of_Sizes, size_of_Providers);
    set_prices(Ord, Sizes, Providers, Prices, size_of_Sizes, size_of_Providers);
    print_results(Ord);

    return 0;
}

void read_file(vector<Order> &Ord, string Sizes[], string Providers[], int size_of_Sizes, int size_of_Providers){
    string file_name = "input.txt";

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
                cout << "   getline line = " << line << endl;

                parse(Ord, line, line_nr, Sizes, Providers, size_of_Sizes, size_of_Providers);
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

void parse(vector<Order> &Ord, string line, int line_nr, string Sizes[], string Providers[], int size_of_Sizes, int size_of_Providers){
    char delim = '-';
    string temp;
    int year, month, day;
    string size;
    string provider;

    int parse_progress = 0;

    // parsing year:
    temp = line.substr(parse_progress, line.find(delim));

    //year = stoi(temp);

    stringstream stream(temp);
    if(!(stream >> year)){
        return;
    }

    if(year < 10000 && year > 999){ // must be 4 digit number
        cout << year << endl;
        parse_progress += 5;
    }
    else{
        cout << "incorrect line" << endl << endl;
        return;
    }

    // parsing month:
    temp = line.substr(parse_progress, line.find(delim));
    stringstream stream2(temp);
    if(!(stream2 >> month)){
        return;
    }
    if(month < 13 && month > 0){
        cout << month << endl;
        parse_progress += 3;
    }
    else{
        cout << "incorrect line" << endl;
        return;
    }

    // parsing day:
    temp = line.substr(parse_progress, line.find(delim));
    stringstream stream3(temp);
    if(!(stream3 >> day)){
        return;
    }
    if(day < 32 && day > 0){
        cout << day << endl;
        parse_progress += 3;
    }
    else{
        cout << "incorrect line" << endl;
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
            cout << size << endl;
            correct = true;
            break;
        }
    }
    if(!correct){
        cout << "incorrect line" << endl;
        return;
    }

    parse_progress++;

    // check space between size and provider:

    if(temp[parse_progress] != ' '){
        cout << "incorrect" << endl;
        return;
    }
    parse_progress++;

    // parsing provider:

    provider.append(temp.begin() + parse_progress, temp.end());
    cout << provider << endl;

    correct = false;
    for(int i = 0; i < size_of_Providers; i++){
        if(provider == Providers[i]){
            cout << provider << endl;
            correct = true;
            break;
        }
    }
    if(!correct){
        cout << "incorrect line" << endl;
        return;
    }

    // if line is correct:

    cout << " CORRECT" << endl << endl;

    Ord.at(line_nr).month = month;
    Ord.at(line_nr).provider = provider;
    Ord.at(line_nr).size = size;
}

void set_prices(vector<Order> &Ord, string Sizes[], string Providers[], float Prices[size_of_Providers][size_of_Sizes], int size_of_Sizes, int size_of_Providers){
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
    cout << "Lowest price " << lowest_S_price << endl;


    for(int i = 0; i < Ord.size(); i++){
        cout << "   " << i << endl;

        // reset accumulated discount counter if going to next month:
        if(i > 0){      
            if(Ord.at(i).month != Ord.at(i-1).month){
                accum_dic = 0;
                counter_L = 0;
            }
        }
        cout << "Accum = " << accum_dic << endl;

        if(!(Ord.at(i).size == "")){    // if line is the right format

            cout << Ord.at(i).line << endl;

            for(int s = 0; s < size_of_Sizes; s++){
                for(int p = 0; p < size_of_Providers; p++){
                    if((Ord.at(i).size == Sizes[s]) && (Ord.at(i).provider == Providers[p])){

                        if(Sizes[s] == "S"){        // must cost as much as the cheapest S option costs
                            if(accum_dic < limit){
                                if(Prices[p][s] == lowest_S_price){ // if the price is already the lowest:
                                    cout << "lowest already" << endl;
                                    Ord.at(i).disc = 0;
                                    Ord.at(i).price = Prices[p][s];

                                }
                                else{
                                    float temp = min((limit - accum_dic), (Prices[p][s] - lowest_S_price));
                                    cout << p << " " << s << endl;
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
                                if(counter_L % 3 == 0){
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
    for(int i = 0; i < Ord.size(); i++){
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
