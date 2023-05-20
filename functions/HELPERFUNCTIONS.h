#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

using namespace std;

#include <iostream>
#include <string>
#include <vector>

// Funkcija koja ispisuje poruku o gresci pri otvaranju datoteke
void error();

// Funkcija koja ucitava vrijednosti jednog reda iz filestreama input sa column_count
// kolona
vector<string> load_row(ifstream& input, int column_count);

// Funkcija za citanje ntog reda
vector<string> load_nth_row(const string& NAME, int row_index, int column_count);

// Funkcija koja pretvara string u vector
vector<string> vector_to_string(string input);

// Funkcija koja vraca broj linija file streama input
int line_count(ifstream& input);

// Funkcija koja prikazuje tekstualni dokument na lokaciji NAME
void show(const string& NAME);

// Funkcija koja ispisuje liniju teksta
void line();

// Funkcija koja pauzira, a zatim i birse konzolu
void cls();

// Funkcija za siguran unos brojeva
template <typename T>
void number_cin(T& x, const string& message);

// Funkcija koja formatira vektor stringova i vraca format pogodan za upis jednog
// reda u bazu podataka;
string format_for_database(const vector<string>& data);

// Funkcija koja vraca (u vektor obliku) zadnji red iz tabele baze podataka
vector<string> last_line(ifstream& input, int column_count);

// Funkcija koja automatski određuje vrijednost sljedeceg indexa za tabelu
int next_index(string NAME, int column_count, int index_position);

// Funkcija koja kopira source u destination
void copyFile(const string& source, const string& destination);

// Funkcija koja brise odredjeni red iz tabele baze podataka
void deleteRow(const string& NAME, int rowNumber);

// Funkcija koja mijenja vrijednost odredjenog reda u tabeli baze podataka
void modifyRow(const string& NAME, int rowNumber, const string& newRowData);

// Funkcija koja prikazuje nazive svih elemenata iz baze podataka sa odgovarajucim
// indeksom i nudi odabir odredjenog indeksa, ukoliko je foreign index1 
// ili foreign index2 manji ili jednak nuli on se ne koristi
int show_index(const string& NAME, int column_count, int name_index, int foreign_index1, int foreign_index2);

// Funkcija koja vraca vektor sa ucitanim osoboma, parametar option nam omogucava odabir
// svih - 0, odabir profesora - 1 ili odabir studenata - 2;
vector<vector<string>> load_people(int option);

// Funkcija koja ucitava 2D vektor svih predmeta u tabeli baze podataka
vector<vector<string>> load_subjects();

// Funkcija koja ucitava 2D vektor svih ispita u tabeli baze podataka
vector<vector<string>> load_exams();

// Funkcija koja omogucava unos broja samo izmedju odredjenih granica
template <typename T>
void limited_number_cin(T& x, const string& message, int lowerLimit, int upperLimit);

// Funkcija koja provjerava prazan unos
// Funkcija koja provjerava prazan unos
string notemptycin(string& help);

#endif