#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Funkcija koja ispisuje poruku o gresci pri otvaranju datoteke
void error() {
    cout << "Error: greska u otvaranju datoteke.\n";
}

// Funkcija koja učitava red određene tabele i vraća vrijednosti kolona tog reda 
vector<string> load_row(ifstream& input, int columnt_count) {
    // Učitavanje cijelog reda iz datoteke u string varijablu
    string line;
    getline(input, line);
    // Kreiranje stringstream objekta koji će nam omogućiti čitanje pojedinačnih kolona iz reda
    stringstream ss(line);
    // Vektor koji sadrži vrijednosti pojedinačnih kolona iz reda
    vector<string> help;
    // Učitavanje vrijednosti svake kolone iz stringstreama i dodavanje u vektor
    string column;
    for(int i = 0; i < columnt_count; i++) {
        getline(ss, column, '+');
        help.push_back(column);
    }
    // Vraćanje vektora sa vrijednostima kolona
    return help;
}

// Funkcija za citanje ntog reda
vector<string> load_nth_row(const string& NAME, int row_index, int column_count) {
    // Stream za citanje podataka iz originalnog fajla
    ifstream input(NAME);
    if(input.fail()) {
        error();
        return vector<string>();
    }
    // Brojac trenutnog reda
    int currentRow = 1;
    // Pomocna varijabla u koju cemo upisivati redove
    string row;
    // Ucitavamo vrijednosti redova u vektor help i ispisujemo naziv i indeks za svaki red
    vector<string> helper;
    // Petlja se ponavlja do kraja fajla ili do pronalaska trazenog reda
    while(!input.eof()) {
        helper = load_row(input, column_count);
        if(helper[0].empty()) break;
        if(currentRow == row_index) {
            // Ako smo pronasli trazeni red, vracamo vrijednosti kolona tog reda
            return helper;
        }
        currentRow++;
    }
    // Ako nismo pronasli trazeni red, vracamo prazan vektor
    return vector<string>();
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
        error();
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

// Funkcija za siguran unos brojeva
template <typename T>
void number_cin(T& x, const string& message) {
    cout << message;
    cin >> x;
    while(cin.fail()) {
        cout << "Error: nije unesen broj.\n";
        cin.clear();
        cin.ignore(256, '\n');
        cout << message;
        cin >> x;
    }
    cin.ignore();
}

// Funkcija koja formatira vektor stringova i vraca format pogodan za upis jednog
// reda u bazu podataka;
string format_for_database(const vector<string>& data) {
    string line = "";
    for(auto a : data) {
        line+=a+"+";
    }
    return line;
}

// Funkcija koja vraca (u vektor obliku) zadnji red iz tabele baze podataka
vector<string> last_line(ifstream& input, int column_count) {
    // Vektor koji ce sadrzavati red
    vector<string> helper;
    // Provjera da li je stream otvoren
    if(input.is_open()) {
        // Ukoliko se fajl otvorio inicijalziramo pomocnu varijablu dummy
        string dummy;
        // Varijabla o broju linija
        int lineCount = line_count(input);
        // Preskacemo sve redove osim zanjeg sa for petljom
        for(int i = 0; i < lineCount-1; i++) {
            getline(input, dummy);
        }
        // Ucitavamo zadnji red
        helper = load_row(input, column_count);
        // Zatvaramo stream
        input.close();
    } else {
        error();
    }
    return helper;
}

// Funkcija koja automatski određuje vrijednost sljedeceg indexa za tabelu
int next_index(string NAME, int column_count, int index_position) {
    ifstream input(NAME);
    // Ukoliko se fajl ne otvori ispravno ispisujemo gresku i vracamo -1
    if(!input.is_open()) {
        error();
        return -1;
    }
    // Ako je dokument prazan postavljamo indeks na 1 i vracamo ga
    if(line_count(input) == 0) {
        return 1;
    } else {
        // Citamo zadnju liniju iz dokumenta
        vector<string> row = last_line(input, column_count);
        // Zatvaramo stream
        input.close();
        // Povecavamo zadnji indeks za 1 i vracamo ga
        return stoi(row[index_position])+1;
    }
}

// Funkcija koja kopira source u destination
void copyFile(const string& source, const string& destination) {
  ifstream input(source);
  ofstream output(destination);
  output << input.rdbuf();
  input.close();
  output.close();
}


// Funkcija koja brise odredjeni red iz tabele baze podataka
void deleteRow(const string& NAME, int rowNumber) {
    const string PATH = "functions/textfiles/";
    // Stream za citanje podataka iz originalnog fajla
    ifstream input(NAME);
    // String za odredjivanje temporary fajla temp.txt
    string help = PATH+"temp.txt";
    // String za upis podataka u temporary file
    ofstream tempFile(help);
    // Brojac trenutnog reda
    int currentRow = 1;
    // Pomocna varijabla u koju cemo upisivati redove
    string row;
    // Petlja se ponavlja do kraja fajla
    while (getline(input, row)) {
        // Jedino se preskace linija za brisanje
        if (currentRow != rowNumber) {
            // Upisujemo red u temp dokument
            tempFile << row << endl;
        }
        // Uvecavamo vrijednost trenutnog reda
        currentRow++;
    }
    // Zatvaramo oba fajla
    input.close();
    tempFile.close();
    // Kopiramo uredjene podatke (sa izbrisanim redom) u originalni fajl
    copyFile(help, NAME);
}

// Funkcija koja prikazuje nazive svih elemenata iz baze podataka sa odgovarajucim
// indeksom i nudi odabir odredjenog indeksa
int show_index(const string& NAME, int column_count, int name_index, int foreign_index) {
    // Deklaracija input file streama asociranog sa datotekom NAME
    ifstream input(NAME);
    // Provjera da li je stream dobro otvoren ako nije ispisujemo gresku
    if(input.fail()) {
        error();
        return -1;
    }
    // Ucitavamo vrijednosti redova u vektor help i ispisujemo naziv i indeks za svaki red
    vector<string> help;
    int count = 1;
    while(!input.eof()) {
        help=load_row(input, column_count);
        if(help[name_index].empty()) break;
        if(foreign_index<=0) {
            cout << help[name_index] << " - " << count++ << "\n";
        } else {
            cout << help[name_index] << " - " << help[foreign_index] << " - " << count++ << "\n";
        }
    }
    // Deklaracija varijable koju cemo vratiti
    int x;
    // Sigurni unos broja
    number_cin(x, "Vas odabir: ");
    return x;
}
