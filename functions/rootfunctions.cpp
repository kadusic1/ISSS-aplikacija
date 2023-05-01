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

// Funkcija za dodavanje odsjeka u tabelu baze podataka
void add_department() {
    // Na pocetku funkcije brisemo ekran
    cls();
    cout << "Dodavanje odsjeka\n";
    line();
    // String help je pomoc za unos, a u vektor data pohranjujemo sve unose
    string help;
    vector<string> data;
    // Varijabla za primary kljuc u bazi podatak
    int index;
    // Unosime sve podatke za fakultet (naziv, trajanje studiranja, index se unosi
    // automatski)
    cout << "Unesite naziv odsjeka: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite trajanje studiranja: ";
    getline(cin, help);
    data.push_back(help); 

    // Inicijaliziramo filestream radi provjere da li je dokument prazan ili zadnjeg
    // indeksa
    ifstream input(DEPARTMENTDATA);

    // Ako je dokument prazan postavljamo indeks na 1
    if(line_count(input) == 0) {
        index = 1;
        data.push_back(to_string(index));
    } else {
        // Citamo zadnju liniju iz dokumenta
        vector<string> row = last_line(input, DEPARTMENT_COLUMNS);
        // Povecavamo zadnji indeks za 1 i upisujemo ga u red
        index = stoi(row[DEPARTMENT_INDEX_INDEX])+1;
        data.push_back(to_string(index));
    }
    // Zatvaramo input stream
    input.close();
    
    // Iz vektora data dobijamo string pogodan za upis jednog reda u bazu podataka
    string row = format_for_database(data);
    // Otvaramo stream za upis podataka u append nacinu rada
    ofstream output(DEPARTMENTDATA, ios::app);
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