#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

using namespace std;

// Funkcija za promjenu informacija o fakultetu (informacije su smjestene u fakulteti.txt)
void edit_college_info() {
    // Na pocetku funkcije brisemo ekran
    cls();
    cout << "Uredjivanje podataka o fakultetu\n";
    line();
    // String help je pomoc za unos, a u vektor data pohranjujemo sve unose
    string help;
    vector<string> data;
    // Unosime sve podatke za fakultet (ime, adresa, grad, postanski broj, drzava,
    // web stranica)
    cout << "Unesite ime fakulteta: ";
    getline(cin, help);
    data.push_back(help);
    cout << "Unesite adresu fakulteta: ";
    getline(cin, help);
    data.push_back(help);
    cout << "Unesite naziv grada iz kojeg je fakultet: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite postanski broj grada iz kojeg je fakultet: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite naziv drzave iz koje je fakultet: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite web stranicu fakulteta: ";
    getline(cin, help);
    data.push_back(help);

    // Iz vektora data dobijamo string pogodan za upis jednog reda u bazu podataka
    string row = format_for_database(data);
    // Otvaramo stream za upis podataka
    ofstream output(COLLEGEDATA);
    // Ukoliko se fajl ispravno otvorio upisujemo odgovarajuci red u tabelu
    if(output.is_open()) {
        // Upisujemo red i ispisujemo odgovarajucu poruku
        output << row << "\n";
        cout << "Informacija uspjesno upisana\n";
    } else {
        // Ukoliko se fajl nije ispravno otvorio ispisujemo gresku
        error();
    }
}
