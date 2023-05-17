#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

// Funkcija koja ispisuje informacije o trenutnoj osobi
void my_info(const vector<string>& data) {
    cls();
    cout << "Vase informacije\n";
    line();
    cout << "Ime i prezime: " << data[PERSON_NAME_INDEX] << " " 
    << data[PERSON_SURNAME_INDEX] << "\n";
    cout << "Tip: ";
    if(data[PERSON_TYPE_INDEX]==ROOT_TYPE) {
        cout << " root\n";
    } else if(data[PERSON_TYPE_INDEX]==PROFESSOR_TYPE) {
        cout << " profesor\n";
        cout << "Spol: ";
    if(data[PERSON_GENDER_INDEX]=="m") {
        cout << " muski\n";
    } else {
        cout << " zenski\n";
    }
    } else {
        cout << " student\n";
        cout << "Spol: ";
        if(data[PERSON_GENDER_INDEX]=="m") {
            cout << " muski\n";
        } else {
            cout << " zenski\n";
        }
        cout << "Broj indeksa: " << data[PERSON_INDEX_NUMBER] << "\n";
        cout << "Odsjek: " << data[PERSON_DEPARTMENT_INDEX] << "\n";
        cout << "Semestar: " << data[PERSON_SEMESTERID_INDEX] << "\n";
    }
    line();
}

// Funkcija koja pokrece ispit, analizira profesora i pita iz kojeg predmeta zeli
// pokrenuti ispit, nakog togase u datotetku Ispiti.txt sprema ime profesora, ime studenta,
// ime predmeta, datum i ocjena (ocjena je na pocetku 0)
void start_exam(const vector<string>& data) {
    // Smjestamo vrijednost svih predmeta u vektor subjects
    vector<vector<string>> subjects = load_subjects();
    // Inicijaliziramo vrijednost brojaca na 0
    int count = 0;
    for(auto a : subjects) {
        // Povecavamo brojac za svaku stavku u vektoru
        count++;
        // Ukoliko predmet pripada trazenom profesoru nudimo za pokretanje ispita
        if(a[SUBJECT_PROFESSOR_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]) {
            cout << a[SUBJECT_NAME_INDEX] << " - " << count << "\n";
        }
    }
    // Deklarisemo varijablu za odabir i unosimo ju
    int choice;
    number_cin(choice, "Vas odabir: ");
    // Ucitavamo izabrani predmet u vektor
    vector<string> subject = load_nth_row(SUBJECTDATA, choice, SUBJECT_COLUMNS);
    // Trazimo upit za datum ispita
    string date;
    cout << "Unesite datum ispita: ";
    getline(cin, date);
    // Deklarisemo vektor cije cemo stavke upisati u tabelu Ispiti.txt
    vector<string> exam;
    // Ucitavamo sve studente u vektor
    vector<vector<string>> students = load_people(2);
    // Odredjujemo ID ispita
    int ID = next_index(EXAMDATA, EXAM_COLUMNS, EXAM_INDEX_INDEX);
    // File stream za upis podataka u tabelu Ispiti.txt
    ofstream out(EXAMDATA, ios::app);
    // Provjeravamo da li je filestream ispravno otvoren ako nije prekidamo program
    if(out.fail()) {
        error();
        return;
    }
    // Za svaku stavku u students vektoru provjeravamo da li je student na odgovarajucem
    // odjseku i semestru, ako jest u vektor exam upisujemo ime profesora, ime studenta,
    // ime predmeta, datum i ocjenu(0)
    for(auto a : students) {
        if(a[PERSON_DEPARTMENT_INDEX]==subject[SUBJECT_DEPARTMENT_INDEX]&&a[PERSON_SEMESTERID_INDEX]==subject[SUBJECT_FOREIGN_INDEX]) {
            // Upis imena profesora
            exam.push_back(data[PERSON_NAME_INDEX]);
            // Upis prezimena profesora
            exam.push_back(data[PERSON_SURNAME_INDEX]);
            // Upis ID profesora
            exam.push_back(data[PERSON_INDEX_NUMBER]);
            // Upis imena studenta
            exam.push_back(a[PERSON_NAME_INDEX]);
            // Upis prezimena studenta
            exam.push_back(a[PERSON_SURNAME_INDEX]);
            // Upis ID studenta
            exam.push_back(a[PERSON_INDEX_NUMBER]);
            // Upis imena predmeta
            exam.push_back(subject[SUBJECT_NAME_INDEX]);
            // Upis ID predmeta
            exam.push_back(subject[SUBJECT_INDEX_INDEX]);
            // Upis datuma
            exam.push_back(date);
            // Upis ocjene default je 0
            exam.push_back("0");
            // Upis prijave ispita - default je 0, ako je 1 onda je ispit prijavljen 1
            exam.push_back("0");
            // Upis indeksa
            exam.push_back(to_string(ID));
            // String za upis u tabelu
            string row = format_for_database(exam);
            // Brisemo sadrzaj vektora exam
            exam.clear();
            // Upisjemo red
            out << row << "\n";
        }
    }
    // Zatvaramo filestream
    out.close();
    cout << "Ispit uspjesno postavljen\n";
}

// Funkcija koja omogucava studentu da potvrdi ispit
void confirm_exam(const vector<string>& data) {
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
}