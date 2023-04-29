#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FUNCTIONS.h"

using namespace std;

const string LOGINFILE = "functions/showlogin.txt";


void show_login() {
    ifstream input(LOGINFILE);
    string line;
    if(input.is_open()) {
        while(getline(input, line)) {
            cout << line << "\n";
        }
    } else {
        cout << "Error: greska u otvaranju datoteke.\n";
    }
    input.close();
}

void try_login() {
    ifstream input("database/Osobe.txt");
    string email;
    string password;

    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    getline(cin, password);

    vector<string> helper;
    int lineCount = line_count("database/Osobe.txt");
    for(int i = 0; i < lineCount; i++) {
        for(int j = 0; j < i-1; j++) {
            string dummy;
            getline(input,dummy);
        }
        helper = load_person(input);
        if(helper[3] == email && helper[7] == password) {
            cout << "Uspjesno\n";
            break;
        }
    }
    input.close();
}

