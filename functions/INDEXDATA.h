// Provjera da li je header ukljucen da ne bi doslo do duplikacije varijabli
#ifndef INDEXDATA_H
#define INDEXDATA_H

#include <string>
using namespace std;

// String varijable
// Varijabla lokacije direktorija sa text file-ovima
const string TEXTFILESPATH = "functions/textfiles/";
// Varijable lokacija fajlova za ispis logina i podacima o osobi
const string LOGINFILE = "functions/textfiles/showlogin.txt"; // Lokacija fajla sa tekstom za login
// stranicu
const string PERSONDATA = "database/Osobe.txt"; // lokacija tabele u bazi podataka za
// osobe
const string COLLEGEDATA = "database/Fakultet.txt"; // lokacija tabele sa informacijama
// o fakultetu
const string DEPARTMENTDATA = "database/Odsjeci.txt"; // lokacija tabele sa informacijama
// o odsjecima
const string SEMESTERDATA = "database/Semestri.txt"; // lokacija tabele sa informacijama
// o semestrima
const string SUBJECTDATA = "database/Predmeti.txt"; // Lokacija tabele sa informacijama
// o predmetima

// Varijable koje opisiju tabelu Osobe.txt
const int PERSON_NAME_INDEX = 0;
const int PERSON_SURNAME_INDEX = 1;
const int PERSON_INDEX_NUMBER = 2;
const int PERSON_GENDER_INDEX = 3;
const int PERSON_TYPE_INDEX = 4;
const int PERSON_DEPARTMENT_INDEX = 5;
const int PERSON_SEMESTERID_INDEX = 6;
const int PERSON_EMAIL_INDEX = 7;
const int PERSON_PASSWORD_INDEX = 8;
const int PERSON_COLUMNS = 9; // Broj kolona u tabeli Osobe.txt
// Razlicite vrijednosti za index tip pod brojem 14
const string ROOT_TYPE = "0";
const string PROFESSOR_TYPE = "1";
const string STUDENT_TYPE = "2";

// Varijable koje opisuju tabelu Fakulteti.txt
const int COLLEGE_NAME_INDEX = 0;
const int COLLEGE_ADDRESS_INDEX = 1;
const int COLLEGE_CITY_INDEX = 2;
const int COLLEGE_POST_NUMBER_INDEX = 3;
const int COLLEGE_COUNTRY_INDEX = 4;
const int COLLEGE_WEBSITE_INDEX = 5;
const int COLLEGE_COLUMNS = 6; // Broj kolona u tabeli Fakultet.txt

// Varijable koje opisuju tabelu Osjeci.txt
const int DEPARTMENT_NAME_INDEX = 0;
const int DEPARTMENT_STUDYTIME_INDEX = 1;
const int DEPARTMENT_INDEX_INDEX = 2;
const int DEPARTMENT_COLUMNS = 4; // Broj kolona u tabeli Odsjeci.txt

// Varijable koje opisuju tabelu Semestri.txt
const int SEMESTER_NAME_INDEX = 0;
const int SEMESTER_FOREIGN_INDEX = 1; // Opisuje kojem odjseku pripada semestar
const int SEMESTER_INDEX_INDEX = 2;
const int SEMESTER_COLUMNS = 3; // Broj kolona u tabeli Semestri.txt

// Varijable koje opisuju tabelu Predmeti.txt
const int SUBJECT_NAME_INDEX = 0;
const int SUBJECT_FOREIGN_INDEX = 1; // Opisuje kojem semestru pripada predmet
const int SUBJECT_DEPARTMENT_INDEX = 2; // Odsjek kojem predmet pripada 
const int SUBJECT_PROFESSOR_INDEX = 3; // Opisuje koji je profesor zaduzen za predmet
const int SUBJECT_INDEX_INDEX = 4;
const int SUBJECT_COLUMNS = 5; // Broj kolona u tabeli Predmeti.txt

// Kraj provjere
#endif