#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FUNCTIONS.h"

using namespace std;

// Deklaracija varijabli koje cemo koristiti
const string LOGINFILE = "functions/showlogin.txt"; // Lokacija fajla sa tekstom za login
// stranicu
const string PERSONDATA = "database/Osobe.txt"; // lokacija tabele u bazi podataka za
// osobe
int EMAIL_INDEX = 3; // index kolone na kojem se nalazi email u tabeli Osobe.txt
int PASSWORD_INDEX = 7; // index kolone na kojem se nalazi password u tabeli Osobe.txt
int COLUMN_PERSONS = 8; // Broj kolona tabele Osobe.txt

// Funkcija koja prikazuje osnovne podatke za login stranu
void show_login() {
    // Deklaracija input file streama asociranog sa datotekom showlogin.txt
    ifstream input(LOGINFILE);
    // Pomocni string
    string line;
    // Provjera da li je stream dobro otvoren
    if(input.is_open()) {
        // Petlja se ponavlja sve do kraja datoteke i upisuje liniju datoteke u string line
        while(getline(input, line)) {
            // Ispisujemo spremljenu liniju
            cout << line << "\n";
        }
    } 
    else {
        // Else statement ukoliko se dokument nije ispravo otvorio
        cout << "Error: greska u otvaranju datoteke.\n";
    }
    // Zatvaranje dokumenta
    input.close();
}

// Funkcija za pokusaj logovanja
void try_login() {
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
        helper = load_person(input, COLUMN_PERSONS);
        // Poredimo da li je kolona 3 jednaka emailu i kolona 7 jednako passwordu
        // Ukoliko jest trebamo ucitati odgovarajuci meni
        if(helper[EMAIL_INDEX] == email && helper[PASSWORD_INDEX] == password) {
            cout << "Uspjesno\n";
            // meni()
            break;
        }
    }
    // Zatvaramo file stream
    input.close();
}

