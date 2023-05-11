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

// Funkcija koja prikazuje nazive svih elemenata iz baze podataka sa odgovarajucim
// indeksom i nudi odabir odredjenog indeksa
int show_index(const string& NAME, int column_count, int name_index);

#endif