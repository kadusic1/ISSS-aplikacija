// Provjera da li je header ukljucen da ne bi doslo do duplikacije varijabli
#ifndef INDEXDATA_H
#define INDEXDATA_H

#include <string>
using namespace std;
// Varijable koje opisiju tabelu Osobe.txt
const int PERSON_NAME_INDEX = 0;
const int PERSON_SURNAME_INDEX = 1;
const int PERSON_INDEX_NUMBER = 2;
const int PERSON_JMBG_INDEX = 3;
const int PERSON_GENDER_INDEX = 4;
const int PERSON_FATHERNAME_INDEX = 5;
const int PERSON_MOTHERNAME_INDEX = 6;
const int PERSON_DATEOFBIRTH_INDEX = 7;
const int PERSON_MUNICIPALITY_INDEX = 8;
const int PERSON_NATIONALITY_INDEX = 9;
const int PERSON_ADRESS_INDEX = 10;
const int PERSON_HIGHSCHOOL_INDEX = 11;
const int PERSON_PHONE_INDEX = 12;
const int PERSON_EMAIL_INDEX = 13;
const int PERSON_TYPE_INDEX = 14;
const int PERSON_STUDENTID_INDEX = 15;
const int PERSON_PROFESSORID_INDEX = 16;
const int PERSON_SEMESTERID_INDEX = 17;
const int PERSON_PASSWORD_INDEX = 18;
const int PERSON_COLUMNS = 19; // Broj kolona u tabeli Osobe.txt
// Razlicite vrijednosti za index tip pod brojem 14
const string ROOT_TYPE = "0";
const string PROFESSOR_TYPE = "1";
const string STUDENT_TYPE = "2";

// Kraj provjere
#endif