#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

using namespace std;

const string MENUFILE = "functions/textfiles/showmenu.txt";
const string ROOTMENUFILE = "functions/textfiles/showrootmenu.txt";

// Funkcija za ispis osnovnih podataka o ulogovanom korisniku, a zatim ispis menija
// i izbor opcija
int menu(const vector<string>& rowData) {
    // Brisemo ekran
    cls();
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
    // Ispisi txt datoteku showmenu.txt
    show(MENUFILE);
    // Provjeravamo da li je korisnik root jer onda ima dodatne opcije, te inicijaliziramo
    // upperLimit varijablu radi provjere u do while pelji ako jest
    int upperLimit = 7;
    if(rowData[PERSON_TYPE_INDEX] == ROOT_TYPE) {
        cout << "    8 - Root funkcije\n";
        upperLimit = 8;
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

// Funkcija za odabir root funkcija
int root_menu() {
    // Brisemo ekran
    cls();
    // Ispisi datoteku showrootfile.txt
    show(ROOTMENUFILE);
    // Gornja granica je 5 jer imamo pet opcija
    int upperLimit = 5;
    // Variabjla u koju smjestamo izbor
    int unos;
    // Unosimo sve dok ne unesemo vrijednost od 1 do 5
    do {
        // Sigurni unos broja pomocu funkcije number_cin()
        number_cin(unos, "Vas unos: ");
        if(unos < 1 || unos > upperLimit) cout << "[GRESKA] Neispravan unos\n";
    } while(unos < 1 || unos > upperLimit);
    // Vracamo odabranu vrijednost
    return unos;
}