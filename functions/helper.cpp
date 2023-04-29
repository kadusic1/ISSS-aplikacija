#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> load_person(ifstream& input) {
    string helper;
    vector<string> help;
    if(input.is_open()) {
        for(int i = 0; i < 8; i++) {
            getline(input, helper, '+');
            help.push_back(helper);
        }
    } else {
        cout << "Error: greska u otvaranju datoteke\n";
    }
    return help;
}

int line_count(const string& file) {
    int count = 0;
    string line;
    ifstream input(file);
    if(input.is_open()) {
            while(getline(input, line)) {
            count++;
        } 
    } else {
        cout << "Error: greska u otvaranju datoteke\n";
        return;
    }
    input.close();
    return count;
}