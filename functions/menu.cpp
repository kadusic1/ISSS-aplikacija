#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

using namespace std;

const string MENUFILE = "functions/textfiles/showmenu.txt";

// Funkcija za ispis osnovnih podataka o ulogovanom korisniku, a zatim ispis menija
// i izbor opcija
int menu(const vector<string>& rowData) {
    // Ispis imena i prezimena ulogovanog korisnika
    cout << "Ime i prezime korisnika: " << rowData[PERSON_NAME_INDEX]
    << " " << rowData[PERSON_SURNAME_INDEX] << "\n";
    // Ispis Tipa korisnika 0 - root, 1 - profesor, 2 - student
    cout << "Tip korisnika: ";
    if(rowData[PERSON_TYPE_INDEX] == ROOT_TYPE) {
        cout << "root\n";
    } else if(rowData[PERSON_TYPE_INDEX] == PROFESSOR_TYPE) {
        cout << "profesor\n";
    } else {
        cout << "student\n";
    }
    // Ispisi txt dokument showmenu.txt
    show(MENUFILE);
    // Provjeravamo da li je korisnik root jer onda ima dodatne opcije, te inicijaliziramo
    // upperLimit varijablu radi provjere u do while pelji ako jest
    int upperLimit = 6;
    if(rowData[PERSON_TYPE_INDEX] == ROOT_TYPE) {
        cout << "    7 - Root funkcije\n";
        upperLimit = 7;
    }
    // Ispisujemo liniju i unos korisnika radi ljepseg formatiranja
    line();
    // Unosimo sve dok ne unesemo vrijednosti od 1 do 6 ili od 1 do 7
    int unos;
    do {
        // Sigurni unos broja pomocu funkcije number_cin()
        number_cin(unos, "Vas unos: ");
        if(unos < 1 || unos > upperLimit) cout << "[GREKSA] Neispravan unos\n";
    } while(unos < 1 || unos > upperLimit);
    // Vracamo odabranu vrijednost
    return unos;
}
