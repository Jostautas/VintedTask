#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Order{
    string line; // used to first read the line from input txt, which then will be parsed.
    string size;  // string is used instead of char for future developement (eg. size XL). change value in func "parse"
    string provider;

};

void read_file(vector<Order> &Ord, string Sizes[], string Providers[]);

void parse(vector<Order> &Ord, string line, int line_nr, string Sizes[], string Providers[]);



int main(){
    vector<Order> Ord;

    string Sizes[] = {"S", "M", "L"};
    string Providers[] = {"LP", "MR"};

    read_file(Ord, Sizes, Providers);


    cout << " Ord size = " << Ord.size() << endl;
    cout << " Ord.line = " << Ord.at(0).line << endl;
    cout << " Ord.line = " << Ord.at(1).line << endl;

    cout << " Ord.at(0): " << Ord.at(0).size << endl;

    return 0;
}

void read_file(vector<Order> &Ord, string Sizes[], string Providers[]){
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

    int size_of_Sizes = 3;
    int size_of_Providers = 2;

    int parse_progress = 0;

    // parsing year:
    temp = line.substr(parse_progress, line.find(delim));

    year = stoi(temp);
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
    month = stoi(temp);
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
    day = stoi(temp);
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

    Ord.at(line_nr).provider = provider;
    Ord.at(line_nr).size = size;
}