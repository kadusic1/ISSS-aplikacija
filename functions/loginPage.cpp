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
    // Deklaracija input file streama asociranog sa datotekom Osobe.txt jer poredimo
    // email i password
    ifstream input(PERSONDATA);
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
    // Inicijaliziramo varijablu lineCount u koju poharnjujemo broj redova u dokumentu
    // osobe.txt
    int lineCount = line_count(input);
    // Ponavljamo onoliko puta koliko ima redova
    for(int i = 0; i < lineCount; i++) {
        // Ova for petlja sluzi da ukoliko smo npr. na drugom redu da ispisemo jedan
        // dummy red
        for(int j = 0; j < i-1; j++) {
            string dummy;
            getline(input,dummy);
        }
        // Inicijaliziramo vektor sa sadržajima reda i odgovarajućim brojem kolona
        helper = load_row(input, PERSON_COLUMNS);
        // Poredimo da li je kolona 3 jednaka emailu i kolona 7 jednako passwordu
        // Ukoliko jest vracamo potake o ulgovanoj osobi
        if(helper[PERSON_EMAIL_INDEX] == email && helper[PERSON_PASSWORD_INDEX] == password) {
            return helper;
        }
    }
    // Zatvaramo file stream
    input.close();
    // Ukoliko nije uspio login cistimo vrijednost pomocnog vektora i
    // vracamo prazan vektor
    helper.clear();
    return helper;
}

