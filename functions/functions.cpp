#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HELPERFUNCTIONS.h"
#include "INDEXDATA.h"

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