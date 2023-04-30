#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Funkcija koja ucitava red odredjene tabele i vraca vrijedonsti kolona tog reda 
vector<string> load_person(ifstream& input, int columnt_count) {
    // Pomocni string koji ce nam omoguciti inicijalizaciju vektora
    string helper;
    // Vektor pomocu kojeg izdvajamo vrijednosti kolona zasebno
    vector<string> help;
    // Izdvajamo svako vrijednost kolone i postavljamo je u vektor
    for(int i = 0; i < columnt_count; i++) {
        getline(input, helper, '+');
        help.push_back(helper);
    }
    // Vracamo vrijednost vektora
    return help;
}

// Funkcija koja vraca broj linija u txt dokumentu na osnovu otvorenog dokumenta tj.
// fstreama
int line_count(ifstream& input) {
    // Vracamo citanje streama na pocetak
    input.clear();
    input.seekg(0, ios::beg);
    // Pocetni broj linija inicijaliziran na 0
    int count = 0;
    // Pomocna varijabla za ucitavanje dummy linija
    string line;
    // Petlja ce se vrtiti dok ima linija u dokumentu i povecavati brojac
    while(getline(input, line)) {
        count++;
    } 
    // Vracamo citanje streama na pocetak
    input.clear();
    input.seekg(0, ios::beg);
    // Vraca se broj linija
    return count;
}

// Funkcija za prikaz NAME txt fajla
void show(const string& NAME) {
    // Deklaracija input file streama asociranog sa datotekom NAME
    ifstream input(NAME);
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

// Funkcija koja ispisuje liniju texta
void line() {
    cout << "------------------------------------------------------\n";
}

// Funkcija koja ispisuje liniju teksta
void cls() {
    system("pause");
    system("cls");
}