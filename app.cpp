#include <iostream>
#include <vector>
#include <string>

#include "functions/loginPage.cpp"
#include "functions/helper.cpp"
#include "functions/menu.cpp"
#include "functions/rootfunctions.cpp"
#include "functions/functions.cpp"

using namespace std;

int main() {
    cls();
    LOGIN:
    // Varijabla u kojoj cemo pohraniti podatke o logovanoj osobi
    vector<string> loginData;
    // Varijabla u kojoj se smjesta izbor stranice odabran u menu funkciji
    int pageChoice;
    // Pokusaj logina
    do {
        show_login();
        loginData = try_login();
        if(loginData[0]=="IZLAZ") goto END;
        if(loginData.empty()) {
            cout << "Neispravan email ili password\n";
            cls();
        }
    } while(loginData.empty());
    // Kada login uspije idemo na menu i brisemo ekran
    cout << "Uspjesan login!\n";

    // Dok petlja radi stranica je pokrenuta tj. u up stanju
    while(true) {
    // Pohranjujemo odabir stranice
    pageChoice = menu(loginData);
    // Redirekcija na odgovarajucu stranu pomocu switch case
    switch(pageChoice) {
        case 1:
            // Ispisujemo informacije o korisniku
            my_info(loginData);
        case 2:
            int choice;
            if(loginData[PERSON_TYPE_INDEX]!=STUDENT_TYPE) {
                choice = announcement_menu();
                if(choice==2) {
                    add_announcement(loginData);
                } else if(choice==1) {
                    cls();
                    show(ANNOUNCEMENTDATA);
                }
            } else {
                cls();
                show(ANNOUNCEMENTDATA);
            }
            break;
        case 3:
            int exam_choice;
            // Stranica vezana za ispita
            // Ukoliko je rijec o profesoru dajemo mogucnost pokretanja i ocjene ispita
            if(loginData[PERSON_TYPE_INDEX]==PROFESSOR_TYPE) {
                exam_choice = exam_menu_professor();
                // Opcija 1 - pokretanje ispita
                if(exam_choice==1) {
                    cls();
                    start_exam(loginData);
                } else if(exam_choice==2) {
                    cls();
                    mark_exam(loginData);
                } else if(exam_choice==3) {
                    cls();
                    delete_exam(loginData);
                }
            } else if(loginData[PERSON_TYPE_INDEX]==STUDENT_TYPE) {
                exam_choice = exam_menu_student();
                // Opcija 1 - prijava ispita
                if(exam_choice==1) {
                    cls();
                    confirm_exam(loginData);
                } else if(exam_choice==2) {
                    cls();
                    cancel_exam(loginData);
                } else if(exam_choice==3) {
                    cls();
                    show_passed_exams(loginData);
                }
            } else {
                cout << "Stranicu ispiti administriraju iskljucivo profesori\n";
            }
            break;
        case 4:
            change_password(loginData);
            break;
        case 5:
            cout << "Odlogovali ste se iz accounta\n";
            cls();
            goto LOGIN;
        case 6:
            // Napustamo petlju preko labeli i zavrsavamo program
            goto END;
            break;
        case 7:
            // Odabir koju funkciju zelimo pozvati
            int functionChoice = root_menu();
            switch(functionChoice) {
                case 1:
                    edit_college_info();
                    break;
                case 2:
                    add_department();
                    break;
                case 3:
                    remove_department();
                    break;
                case 4:
                    add_semester();
                    break;
                case 5:
                    remove_semester();
                    break;
                case 6:
                    add_subject();
                    break;
                case 7:
                    remove_subject();
                    break;
                case 8:
                    add_person();
                    break;
                case 9:
                    remove_person();
                    break;
            }
            break;
    }
    }
    
    // Ispisujemo zadnju poruku prije zavrsetka
    END:
    cls();
    cout << "Zelimo vam ugodan dan.\n";

    return 0;
}