#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

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
    cout << "Najava ispita\n";
    line();
    // Koristimo vektor za pracenje odabira
    vector<int> tracker;
    // Smjestamo vrijednost svih predmeta u vektor subjects
    vector<vector<string>> subjects = load_subjects();
    // Inicijaliziramo vrijednost brojaca na 0
    int count = 0;
    int count2 = 0;
    for(auto a : subjects) {
        // Povecavamo brojac za svaku stavku u vektoru
        count++;
        // Ukoliko predmet pripada trazenom profesoru nudimo za pokretanje ispita
        if(a[SUBJECT_PROFESSOR_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]) {
            cout << a[SUBJECT_NAME_INDEX] << " - " << a[SUBJECT_DEPARTMENT_INDEX] <<
            " - " << a[SUBJECT_FOREIGN_INDEX] << " - " << count << "\n";
            tracker.push_back(count);
            count2++;
        }
    }
    if(count2==0) {
        cout << "Profesor nema evidentiranih predmeta\n";
        return;
    }
    cout << "ODUSTANI - 0\n";
    line();
    // Pomocna varijabla
    bool test = false;
    int x;
    while(!test) {
        number_cin(x, "Vas odabir: ");
        if(x==0) return;
        for(auto a : tracker) {
            if(x==a) test=true;
        }
        if(!test) {
            cout << "Error: nije unesen adekvatan broj.\n";
        }
    }
    if(x==0) return;
    // Ucitavamo izabrani predmet u vektor
    vector<string> subject = load_nth_row(SUBJECTDATA, x, SUBJECT_COLUMNS);
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
    line();
}

// Funkcija koja omogucava studentu da potvrdi ispit
void confirm_exam(const vector<string>& data) {
    cout << "Prijava ispita\n";
    line();
    // Koristimo vektor za pracenje odabira
    vector<int> tracker;
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
    // Ispisujemo listu ispita za prijavu
    // Za svaki unos u exams provjeravamo da li id studenta u data odgovra idu
    // stduenta u exams, te da li je ispit vec prijavljen
    int count = 0;
    int count2 = 0;
    for(auto a : exams) {
        count++;
        if(a[EXAM_STUDENT_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]&&a[EXAM_CONFIRM_INDEX]=="0"&&stoi(a[EXAM_GRADE_INDEX]) < 5) {
            cout << a[EXAM_PROFESSOR_INDEX] << " " << a[EXAM_PROFESSOR_SURNAME]
            << " - " << a[EXAM_SUBJECT_INDEX] << " - " << 
            a[EXAM_DATE_INDEX] << " - " << a[EXAM_INDEX_INDEX] << "\n";
            tracker.push_back(stoi(a[EXAM_INDEX_INDEX]));
            count2++;
        }
    }
    if(count2==0) {
        cout << "Nema ispita za prijavu\n";
        return;
    }
    cout << "ODUSTANI - 0\n";
    line();
    // Pomocna varijabla
    bool test = false;
    int x;
    while(!test) {
        number_cin(x, "Vas odabir: ");
        if(x==0) return;
        for(auto a : tracker) {
            if(x==a) test=true;
        }
        if(!test) {
            cout << "Error: nije unesen adekvatan broj.\n";
        }
    }
    // Vektor koji ce sadrzavati promijenjeni red
    vector<string> newData;
    // Broj reda
    int rowNumber = 0;
    // Trazimo odabranu stavku u tabeli
    for(int i = 0; i < exams.size(); i++) {
        // Provjeravamo kada je ID odabranog ispita isti kao ID u vektori i ID ucitanog
        // studenta isti kao ID u vektori
        if(exams[i][EXAM_INDEX_INDEX]==to_string(x)&&exams[i][EXAM_STUDENT_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]) {
            // Spremamo novi red
            newData = exams[i];
            // Spremamo broj reda
            rowNumber = i+1;
            break;
        }
    }
    // Mijenajmo status prijavljenog na 1 - prijavljen
    newData[EXAM_CONFIRM_INDEX] = "1";
    // Modifikujemo tabelu
    modifyRow(EXAMDATA, rowNumber, format_for_database(newData));
}

// Funkcija koja omogucava studentu da odgodi ispit
void cancel_exam(const vector<string>& data) {
    cout << "Odgoda ispita\n";
    line();
    // Koristimo vektor za pracenje odabira
    vector<int> tracker;
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
    // Ispisujemo listu ispita za prijavu
    // Za svaki unos u exams provjeravamo da li id studenta u data odgovra idu
    // stduenta u exams, te da li je ispit vec prijavljen
    int count = 0;
    int count2 = 0;
    for(auto a : exams) {
        if(a[EXAM_STUDENT_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]&&a[EXAM_CONFIRM_INDEX]=="1"&&stoi(a[EXAM_GRADE_INDEX]) < 5) {
            cout << a[EXAM_PROFESSOR_INDEX] << " " << a[EXAM_PROFESSOR_SURNAME]
            << " - " << a[EXAM_SUBJECT_INDEX] << " - " << 
            a[EXAM_DATE_INDEX] << " - " << a[EXAM_INDEX_INDEX] << "\n";
            tracker.push_back(stoi(a[EXAM_INDEX_INDEX]));
            count2++;
        }
    }
    if(count2 == 0) {
        cout << "Nema prijavljenih ispita\n";
        return;
    }
    cout << "ODUSTANI - 0\n";
    line();
    // Pomocna varijabla
    bool test = false;
    int x;
    while(!test) {
        number_cin(x, "Vas odabir: ");
        if(x==0) return;
        for(auto a : tracker) {
            if(x==a) test=true;
        }
        if(!test) {
            cout << "Error: nije unesen adekvatan broj.\n";
        }
    }
    // Vektor koji ce sadrzavati promijenjeni red
    vector<string> newData;
    // Broj reda
    int rowNumber = 0;
    // Trazimo odabranu stavku u tabeli
    for(int i = 0; i < exams.size(); i++) {
        // Provjeravamo kada je ID odabranog ispita isti kao ID u vektori i ID ucitanog
        // studenta isti kao ID u vektori
        if(exams[i][EXAM_INDEX_INDEX]==to_string(x)&&exams[i][EXAM_STUDENT_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]) {
            // Spremamo novi red
            newData = exams[i];
            // Spremamo broj reda
            rowNumber = i+1;
            break;
        }
    }
    // Mijenajmo status prijavljenog na 1 - prijavljen
    newData[EXAM_CONFIRM_INDEX] = "0";
    // Modifikujemo tabelu
    modifyRow(EXAMDATA, rowNumber, format_for_database(newData));
}

// Funkcija koja omogucava profesoru da ocjeni ispit
void mark_exam(const vector<string>& data) {
    cout << "Ocjenjivanje ispita\n";
    line();
    // Koristimo vektor za pracenje odabira
    vector<int> tracker;
    int count1 = 0;
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
    // Za svaki unos u exams provjeravamo da li id profesora u data odgovra idu
    // profesora u exams, te da li je to zadnji ispit sa tim indeksom

    for (int i = 0; i < exams.size(); i++) {
    if ((i==0||exams[i-1][EXAM_INDEX_INDEX]!=exams[i][EXAM_INDEX_INDEX]) && exams[i][EXAM_PROFESSOR_INDEX_INDEX] == data[PERSON_INDEX_NUMBER]) {
        cout << exams[i][EXAM_SUBJECT_INDEX] << " - " << exams[i][EXAM_DATE_INDEX]
        << " - " << exams[i][EXAM_INDEX_INDEX] << "\n";
        tracker.push_back(stoi(exams[i][EXAM_INDEX_INDEX]));
        count1++;
        }
    }
    if(count1==0) {
        cout << "Nema evidentiranih ispita\n";
        return;
    }
    cout << "ODUSTANI - 0\n";
    // Pomocna varijabla
    int x;
    bool test = false;
    while(!test) {
        number_cin(x, "Vas odabir: ");
        if(x==0) return;
        for(auto a : tracker) {
            if(x==a) test=true;
        }
        if(!test) {
            cout << "Error: nije unesen adekvatan broj.\n";
        }
    }
    // Ocjenjujemo svakog studenta u izabranom ispitu, brojimo redove pomocu varijable count
    int count = 0;
    // Bool varijabla za ispis prdmeta ispita i datuma
    bool written = false;
    tracker.clear();
    int count2 = 0;
    for(auto a : exams) {
        count++;
        // Provjera da li je to stavka izabranog ispita
        if(a[EXAM_INDEX_INDEX]==to_string(x)) {
            if(written==false) {
                line();
                // Ispis predmeta i datuma ispita
                cout << a[EXAM_SUBJECT_INDEX] << " - " << a[EXAM_PROFESSOR_INDEX] 
                << " " << a[EXAM_PROFESSOR_SURNAME] 
                << " - " << a[EXAM_DATE_INDEX] << "\n";

                written=true;
            }
            // Provjera da li je ispit prijavljen i da li je vec ocjenjen
            if(a[EXAM_CONFIRM_INDEX]=="1") {
                cout << "Student - " << a[EXAM_STUDENT_INDEX] << " " << a[EXAM_STUDENT_SURNAME_INDEX] << "\n";
                // Unos ocjene
                int ocjena;
                limited_number_cin(ocjena, "Unesite ocjenu: ", 5, 10);
                // Vektor za modifikaciju
                vector<string> newData;
                newData = a;
                // Modifikacija ocjene
                newData[EXAM_GRADE_INDEX] = to_string(ocjena);
                // Konacno upisujemo red
                modifyRow(EXAMDATA, count, format_for_database(newData));
                count2++;
            }
        }
    }
    if(count2==0) {
        cout << "Niko nije pristupio ispitu\n";
        return;
    }
}

// Funkcija koja omogucuje profesoru da izbrise podatke o ispitu
void delete_exam(const vector<string>& data) {
    cout << "Brisanje ispita\n";
    line();
    // Koristimo vektor za pracenje odabira
    vector<int> tracker;
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
    // Za svaki unos u exams provjeravamo da li id profesora u data odgovra idu
    // profesora u exams, te da li je to zadnji ispit sa tim indeksom
    int count = 0;
    for (int i = 0; i < exams.size(); i++) {
    if ((i==0||exams[i-1][EXAM_INDEX_INDEX]!=exams[i][EXAM_INDEX_INDEX]) && exams[i][EXAM_PROFESSOR_INDEX_INDEX] == data[PERSON_INDEX_NUMBER]) {
        cout << exams[i][EXAM_SUBJECT_INDEX] << " - " << exams[i][EXAM_DATE_INDEX]
        << " - " << exams[i][EXAM_INDEX_INDEX] << "\n";
        tracker.push_back(stoi(exams[i][EXAM_INDEX_INDEX]));
        count++;
        }
    }
    if(count==0) {
        cout << "Nema evidentiranih ispita\n";
        return;
    }
    cout << "ODUSTANI - 0\n";
    line();
    // Pomocna varijabla
    bool test = false;
    int x;
    while(!test) {
        number_cin(x, "Vas odabir: ");
        if(x==0) return;
        for(auto a : tracker) {
            if(x==a) test=true;
        }
        if(!test) {
            cout << "Error: nije unesen adekvatan broj.\n";
        }
    }
    // Otvaramo fajl brisuci sve iz njega
    ofstream out(EXAMDATA);
    if(out.fail()) {
        error();
        return;
    }
    for(auto a : exams) {
        if(a[EXAM_INDEX_INDEX]!=to_string(x)) {
            string help = format_for_database(a);
            out << help << "\n";
        }
    }
}

// Funkcija koja omogucava studentu da vidi polozene ispite, ocjenu i prosjek ocjena
void show_passed_exams(const vector<string>& data) {
    cout << "Polozeni ispiti\n";
    line();
    // Smjestamo vrijednost svih ispita u vektor exams
    vector<vector<string>> exams = load_exams();
    // Pomocne varijable za prosjek
    int count = 0;
    float sum = 0;
    // Za svaki unos u exams provjeravamo da li id studenta u data odgovra idu
    // studenta u exams, ako odgovara ispisujemo predmet, ime i prezime profesora,
    // ocjenu, a nakon toga prosjek
    for (int i = 0; i < exams.size(); i++) {
        if (exams[i][EXAM_STUDENT_INDEX_INDEX]==data[PERSON_INDEX_NUMBER]&&stoi(exams[i][EXAM_GRADE_INDEX])>=6) {
            cout << exams[i][EXAM_SUBJECT_INDEX] << " - " << exams[i][EXAM_DATE_INDEX] << " - "
            << exams[i][EXAM_PROFESSOR_INDEX] << " "
            << exams[i][EXAM_PROFESSOR_SURNAME] << " - " << exams[i][EXAM_GRADE_INDEX] << "\n";
            count++;
            sum+=stoi(exams[i][EXAM_GRADE_INDEX]);
        }
    }
    if(count==0) {cout << "Neme polozenih ispita\n";return;}
    line();
    cout << fixed << setprecision(2) << "PROSJEK: " << sum/count << "\n";
}

// Fukcija koja postavlja oglaas
void add_announcement(const vector<string>& data) {
    string help;
    ofstream out(ANNOUNCEMENTDATA, ios::app);
    if(out.fail()) {
        error();
        return;
    }
    cls();
    if(data[PERSON_NAME_INDEX]=="root") {
        out << "Administrator - ";
    } else {
        out << data[PERSON_NAME_INDEX] << " " << data[PERSON_SURNAME_INDEX] << " - ";
    }
    cout << "Postavljanje obavijesti (Za odustajanje unesi X u prvom unosu)\n";
    cout << "Unesi datum postavljanja: ";
    notemptycin(help);
    out << help << " - ";
    cout << "Unesite ime obavijesti: ";
    notemptycin(help);
    out << help << "\n";
    line();
    help.clear();
    cout << "Unosenje teksta:\n\n";
    out << "------------------------------------------------------\n";
    do {
        getline(cin, help);
        if(!help.empty()) {
            out << help << "\n";
        }
    } while(!help.empty());
    out << "------------------------------------------------------\n";
    out << "\n";
    out.close();
}

// Funkcija koja mijenja password korisnika
void change_password(const vector<string>& data) {
    string help;
    int rowNumber = 0;
    ifstream in(PERSONDATA);
    if(in.fail()) {
        error();
        return;
    }
    vector<string> row;
    while(true) {
        rowNumber++;
        row = load_row(in, PERSON_COLUMNS);
        if(row[PERSON_INDEX_NUMBER]==data[PERSON_INDEX_NUMBER]) {
            break;
        }
    }
    if(rowNumber==line_count(in)) {
        cout << "Trazena osoba ne postoji\n";
        in.close();
        return;
    }
    in.close();
    row.clear();
    row = load_nth_row(PERSONDATA, rowNumber, PERSON_COLUMNS);
    cls();
    cout << "Promjena passworda (Za odustajanje unesi X u prvom unosu)\n";
    line();
    cout << "Korisnik: " << row[PERSON_NAME_INDEX] << " " <<
    row[PERSON_SURNAME_INDEX] << "\n";
    help.clear();
    cout << "Unesite stari password: ";
    notemptycin(help);   
    if(help.empty()) return;
    if(help!=row[PERSON_PASSWORD_INDEX]) {
        cout << "Neispravan password\n";
        return;
    }
    cout << "Unesite novi password: ";
    notemptycin(help);   
    if(help.empty()) return;
    row[PERSON_PASSWORD_INDEX] = help;
    modifyRow(PERSONDATA, rowNumber, format_for_database(row));
    cout << "Password uspjesno promijenjen\n";
}