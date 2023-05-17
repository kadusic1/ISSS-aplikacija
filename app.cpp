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

    LOGIN:
    // Varijabla u kojoj cemo pohraniti podatke o logovanoj osobi
    vector<string> loginData;
    // Varijabla u kojoj se smjesta izbor stranice odabran u menu funkciji
    int pageChoice;
    // Pokusaj logina
    do {
        show_login();
        loginData = try_login();
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
            break;
        case 3:
            break;
        case 4:
            int exam_choice;
            // Stranica vezana za ispita
            // Ukoliko je rijec o profesoru dajemo mogucnost pokretanja i ocjene ispita
            if(loginData[PERSON_TYPE_INDEX]==PROFESSOR_TYPE) {
                exam_choice = exam_menu_professor();
                // Opcija 1 - pokretanje ispita
                if(exam_choice==1) {
                    start_exam(loginData);
                }   
            } else {
                exam_choice = exam_menu_student();
                // Opcija 1 - prijava ispita
                if(exam_choice==1) {
                    confirm_exam(loginData);
                } else {
                    cancel_exam(loginData);
                }
            }
            break;
        case 5:
            break;
        case 6:
            cout << "Odlogovali ste se iz accounta\n";
            cls();
            goto LOGIN;
        case 7:
            // Napustamo petlju preko labeli i zavrsavamo program
            goto END;
            break;
        case 8:
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