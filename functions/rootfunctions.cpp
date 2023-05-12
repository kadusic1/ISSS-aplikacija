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
    // Automatski postavljamo vrijednost indeksa koristeci funkciju next_index
    index = next_index(DEPARTMENTDATA, DEPARTMENT_COLUMNS, DEPARTMENT_INDEX_INDEX);
    // Ukoliko je vrijednost -1 doslo je do greske pa izlazimo iz funkcije
    if(index==-1) return;
    // Postavljamo index u vektor
    data.push_back(to_string(index));
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

// Funkcija koja uklanja odsjek iz tabele baze podataka
void remove_department() {
    int odsjek_za_ukloniti = show_index(DEPARTMENTDATA, DEPARTMENT_COLUMNS, 
    DEPARTMENT_NAME_INDEX, 0);
    deleteRow(DEPARTMENTDATA, odsjek_za_ukloniti);
}

// Funkcija za dodavanje odsjeka u tabelu baze podataka
void add_semester() {
    // Na pocetku funkcije brisemo ekran
    cls();
    cout << "Dodavanje semestra\n";
    line();
    // String help je pomoc za unos, a u vektor data pohranjujemo sve unose
    string help;
    vector<string> data;
    // Varijabla za primary kljuc u bazi podatak
    int index;
    // Unosime sve podatke za fakultet (naziv, trajanje studiranja, index se unosi
    // automatski)
    cout << "Unesite broj semestra: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Odabiranje odsjeka na kojem je semestar\n";
    int x = show_index(DEPARTMENTDATA, DEPARTMENT_COLUMNS, DEPARTMENT_NAME_INDEX, 0);
    data.push_back(load_nth_row(DEPARTMENTDATA, x, DEPARTMENT_COLUMNS)[DEPARTMENT_NAME_INDEX]); 
    // Automatski postavljamo vrijednost indeksa koristeci funkciju next_index
    index = next_index(SEMESTERDATA, SEMESTER_COLUMNS, SEMESTER_INDEX_INDEX);
    // Ukoliko je vrijednost -1 doslo je do greske pa izlazimo iz funkcije
    if(index==-1) return;
    // Postavljamo index u vektor
    data.push_back(to_string(index));
    // Iz vektora data dobijamo string pogodan za upis jednog reda u bazu podataka
    string row = format_for_database(data);
    // Otvaramo stream za upis podataka u append nacinu rada
    ofstream output(SEMESTERDATA, ios::app);
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

// Funkcija koja uklanja semestar iz tabele baze podataka
void remove_semester() {
    int semestar_za_ukloniti = show_index(SEMESTERDATA, SEMESTER_COLUMNS, 
    SEMESTER_NAME_INDEX, SEMESTER_FOREIGN_INDEX);
    deleteRow(SEMESTERDATA, semestar_za_ukloniti);
}