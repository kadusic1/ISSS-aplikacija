#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

using namespace std;

// Funkcija koja prikazuje osnovne podatke za login stranu
void show_login() {
    show(LOGINFILE);
    ifstream input(COLLEGEDATA);
    if(input.is_open()) {
        vector<string> data = load_row(input, COLLEGE_COLUMNS);
        for(int i = 0; i < COLLEGE_COLUMNS; i++) {
            if(i == COLLEGE_POST_NUMBER_INDEX-1) {
                cout << data[i] << " ";
            } else {
                cout << data[i] << "\n";
            }
        }
        line();
        input.close();
    } else {
        error();
    }
}

// Funkcija za pokusaj logovanja ukoliko uspije vraca red tabele Osobe.txt, ukoliko ne
// uspije vraca prazan vektor
vector<string> try_login() {
    // Pomocne varijable za unos
    string email;
    string password;
    // Unos emaila i passworda
    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    getline(cin, password);
    // Vektor koji će sadržavati sve unose jednog reda (vrijednosti kolona)
    vector<string> helper;
    if(email==""&&password=="") {
        helper.push_back("IZLAZ");
        return helper;
    }
    // Inicijaliziramo varijablu lineCount u koju poharnjujemo broj redova u dokumentu
    // osobe.txt
    ifstream input(PERSONDATA);
    int lineCount = line_count(input);
    input.close();
    // Ponavljamo onoliko puta koliko ima redova
    for(int i = 0; i < lineCount; i++) {
        // Inicijaliziramo vektor sa sadržajima reda i odgovarajućim brojem kolona
        helper = load_nth_row(PERSONDATA, i+1, PERSON_COLUMNS);
        // Poredimo da li je kolona 3 jednaka emailu i kolona 7 jednako passwordu
        // Ukoliko jest vracamo potake o ulgovanoj osobi
        if(helper[PERSON_EMAIL_INDEX] == email && helper[PERSON_PASSWORD_INDEX] == password) {
            return helper;
        }
    }
    // Ukoliko nije uspio login cistimo vrijednost pomocnog vektora i
    // vracamo prazan vektor
    helper.clear();
    return helper;
}

