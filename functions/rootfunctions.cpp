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
    DEPARTMENT_NAME_INDEX, 0, 0);
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
    int x = show_index(DEPARTMENTDATA, DEPARTMENT_COLUMNS, DEPARTMENT_NAME_INDEX, 0, 0);
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
    SEMESTER_NAME_INDEX, SEMESTER_FOREIGN_INDEX, 0);
    deleteRow(SEMESTERDATA, semestar_za_ukloniti);
}

// Funkcija za dodavanje predmeta u tabelu baze podataka
void add_subject() {
    // Na pocetku funkcije brisemo ekran
    cls();
    cout << "Dodavanje predmeta\n";
    line();
    // String help je pomoc za unos, a u vektor data pohranjujemo sve unose
    string help;
    vector<string> data;
    // Varijabla za primary kljuc u bazi podatak
    int index;
    // Unosime sve podatke za fakultet (naziv, odjsek, semestar, profesor, index se unosi
    // automatski)
    cout << "Unesite naziv predmeta: ";
    getline(cin, help);
    data.push_back(help); 
    // Odabir semestra
    cout << "Odabiranje semestra na kojem je predmet\n";
    int x = show_index(SEMESTERDATA, SEMESTER_COLUMNS, SEMESTER_NAME_INDEX, SEMESTER_FOREIGN_INDEX, 0);
    // Upisjemo broj semestra i odjsek kojem pripada u vektor data
    data.push_back(load_nth_row(SEMESTERDATA, x, SEMESTER_COLUMNS)[SEMESTER_NAME_INDEX]);
    data.push_back(load_nth_row(SEMESTERDATA, x, SEMESTER_COLUMNS)[SEMESTER_FOREIGN_INDEX]); 

    // Odabir profesora, opcija 1 znaci ucitati profesore, ucitanu vrijendost
    // pohranjujemo u x i smjestamo ime profesora u vector data
    vector<vector<string>> professors = load_people(1);
    cout << "Odabir profesora\n";
    for(int i = 0; i < professors.size(); i++) {
        cout << i+1 << " - " << professors[i][PERSON_NAME_INDEX] << "\n";
    } 
    number_cin(x, "Vas odabir: ");
    data.push_back(professors[x-1][PERSON_NAME_INDEX]);
    data.push_back(professors[x-1][PERSON_INDEX_NUMBER]);
    // Automatski postavljamo vrijednost indeksa koristeci funkciju next_index
    index = next_index(SUBJECTDATA, SUBJECT_COLUMNS, SUBJECT_INDEX_INDEX);
    // Ukoliko je vrijednost -1 doslo je do greske pa izlazimo iz funkcije
    if(index==-1) return;
    // Postavljamo index u vektor
    data.push_back(to_string(index));
    // Iz vektora data dobijamo string pogodan za upis jednog reda u bazu podataka
    string row = format_for_database(data);
    // Otvaramo stream za upis podataka u append nacinu rada
    ofstream output(SUBJECTDATA, ios::app);
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

// Funkcija koja uklanja predmet iz tabele baze podataka
void remove_subject() {
    int predmet_za_ukloniti = show_index(SUBJECTDATA, SUBJECT_COLUMNS, 
    SUBJECT_NAME_INDEX, SUBJECT_FOREIGN_INDEX, 0);
    deleteRow(SUBJECTDATA, predmet_za_ukloniti);
}

// Funkcija koja dodaje osobu u tabelu baze podataka
void add_person() {
    // Na pocetku funkcije brisemo ekran
    cls();
    cout << "Dodavanje osobe\n";
    line();
    // String help je pomoc za unos, a u vektor data pohranjujemo sve unose
    string help;
    vector<string> data;
    // Varijabla za primary kljuc u bazi podatak
    int index;
    // Unosime sve podatke za fakultet (ime, prezime, semestar, profesor, index se unosi
    // automatski)
    cout << "Unesite ime osobe: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite prezime osobe: ";
    getline(cin, help);
    data.push_back(help); 
    // Automatski postavljamo vrijednost indeksa koristeci funkciju next_index
    index = next_index(SUBJECTDATA, SUBJECT_COLUMNS, SUBJECT_INDEX_INDEX);
    // Ukoliko je vrijednost -1 doslo je do greske pa izlazimo iz funkcije
    if(index==-1) return;
    // Postavljamo index u vektor
    data.push_back(to_string(index));
    cout << "Unesite spol osobe (m ili z): ";
    do {
        cin >> help;
    } while(help!="m"&&help!="z");
    data.push_back(help);
    int pomoc;
    do {
        number_cin(pomoc, "Unesite tip osobe (1 - profesor ili 2 - student): ");
    } while(pomoc!=1&&pomoc!=2);
    if(pomoc==1) {
        help = PROFESSOR_TYPE;
    } else if(pomoc == 2) {
        help = STUDENT_TYPE;
    }
    data.push_back(help);
    // Ako je osoba profesor nema poente navoditi odsjek i semestar
    if(pomoc==1) {
        data.push_back("0");
        data.push_back("0");
    } else {
        cout << "Odabir odjseka na kojem je osoba\n";
        int x = show_index(DEPARTMENTDATA, DEPARTMENT_COLUMNS, DEPARTMENT_NAME_INDEX, 0, 0);
        data.push_back(load_nth_row(DEPARTMENTDATA, x, DEPARTMENT_COLUMNS)[DEPARTMENT_NAME_INDEX]);
        cout << "Odabiranje semestra na kojem je predmet\n";
        x = show_index(SEMESTERDATA, SEMESTER_COLUMNS, SEMESTER_NAME_INDEX, SEMESTER_FOREIGN_INDEX, 0);
        data.push_back(load_nth_row(SEMESTERDATA, x, SEMESTER_COLUMNS)[SEMESTER_NAME_INDEX]);
    }
    cout << "Unesite email osobe: ";
    getline(cin, help);
    data.push_back(help); 
    cout << "Unesite password osobe: ";
    getline(cin, help);
    data.push_back(help);
    // Iz vektora data dobijamo string pogodan za upis jednog reda u bazu podataka
    string row = format_for_database(data);
    // Otvaramo stream za upis podataka u append nacinu rada
    ofstream output(PERSONDATA, ios::app);
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

// Funkcija koja uklanja osobu iz tabele baze podataka
void remove_person() {
    int osoba_za_ukloniti = show_index(PERSONDATA, PERSON_COLUMNS, 
    PERSON_NAME_INDEX, PERSON_SURNAME_INDEX, 0);
    deleteRow(PERSONDATA, osoba_za_ukloniti);
}