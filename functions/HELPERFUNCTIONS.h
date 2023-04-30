using namespace std;

#include <iostream>
#include <string>
#include <vector>

// Funkcija koja ucitava vrijednosti jednog reda iz filestreama input sa column_count
// kolona
vector<string> load_person(ifstream& input, int column_count);

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

